#include "CPBFReader.h"
#include <arpa/inet.h>
#include "osmFormat.pb.h"
#include "fileFormat.pb.h"
#include <iostream>
#include <fstream>
#include <zlib.h>

#include <COSMNode.h>

using namespace std;

namespace osmMachine
{

static const std::string sBlobType_OSMHeader = "OSMHeader";
static const std::string sBlobType_OSMData = "OSMData";
static constexpr size_t maxBlobSize( 32 * 1024 * 1024);
static constexpr double sNanoDegreeScale( 0.000000001 );
static constexpr int64_t sDflt_LatOffset = 0;
static constexpr int64_t sDflt_LonOffset = 0;
static constexpr int64_t sDflt_Granularity = 100;


CPBFReader::CPBFReader( IOSMModelBuilder& osmModelBuilder)
: m_pbfFilestreamPtr()
, m_fileBuffer( nullptr )
, m_zlibBuffer( nullptr )
, m_osmModelBuilder( osmModelBuilder )
{
    
}

CPBFReader::~CPBFReader()
{
    delete[] m_zlibBuffer;
    delete[] m_fileBuffer;
}

bool CPBFReader::OpenFile( const std::string& filename )
{
  m_pbfFilestreamPtr = std::make_unique<std::ifstream>(filename, std::ios::binary);
  if ( m_pbfFilestreamPtr && m_pbfFilestreamPtr->is_open() )
  {
    m_fileBuffer = new char[maxBlobSize]; 
    m_zlibBuffer = new char[maxBlobSize]; 
    return true;
  }

  return false;
}

bool CPBFReader::ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead )
{
  bool retVal(true);

  if ( m_pbfFilestreamPtr && m_pbfFilestreamPtr->is_open() )
  {
    m_pbfFilestreamPtr->seekg(0,m_pbfFilestreamPtr->beg);
    int headerSize(0);

    while ( m_pbfFilestreamPtr->read((char *)&headerSize, sizeof(headerSize) ) )
    {
      headerSize = ntohl(headerSize);

      m_pbfFilestreamPtr->read((char*)m_fileBuffer, headerSize) ;
      BlobHeader blobHeader;
      blobHeader.ParseFromArray(m_fileBuffer, headerSize);

      std::string dataType = blobHeader.type();
      if ( m_pbfFilestreamPtr->read((char*)m_fileBuffer, blobHeader.datasize() ) )
      {
        Blob dataBlob; 
        dataBlob.ParseFromArray(m_fileBuffer, blobHeader.datasize());

        if ( dataBlob.has_zlib_data() )
        {
          size_t uncopressedDataSize( maxBlobSize );

          if ( Z_OK  == uncompress( (Bytef*) m_zlibBuffer, &uncopressedDataSize, (Bytef*)dataBlob.zlib_data().c_str() , dataBlob.zlib_data().size() ) )
          {
            if (sBlobType_OSMHeader == dataType )
            {
              HeaderBlock headerBlock;
              if (headerBlock.ParseFromArray( m_zlibBuffer, uncopressedDataSize) )
              {
                m_osmModelBuilder.NotifyBoundingBox( sNanoDegreeScale * headerBlock.bbox().left(),
                sNanoDegreeScale * headerBlock.bbox().top(),
                sNanoDegreeScale * headerBlock.bbox().right(),
                sNanoDegreeScale * headerBlock.bbox().bottom() );

              }
            } else if ( sBlobType_OSMData == dataType )
            {
              PrimitiveBlock osmData;
              if ( osmData.ParseFromArray( m_zlibBuffer, uncopressedDataSize) )
              {   
                int64_t latOffset(osmData.has_lat_offset() ? osmData.lat_offset() : sDflt_LatOffset);
                int64_t lonOffset(osmData.has_lon_offset() ? osmData.lon_offset() : sDflt_LonOffset);
                int64_t granularity( osmData.has_granularity() ? osmData.granularity() : sDflt_Granularity);

                size_t primitiveGroupCount(osmData.primitivegroup_size());
                for(size_t i = 0 ; i < primitiveGroupCount; ++i)
                {
                  const auto& primitiveGroup = osmData.primitivegroup(i);

                  if ( eNodes & primitivesToRead)
                  {
                    // extracting nodes
                    int nodeCount(primitiveGroup.nodes_size());
                    for ( int nodeIdx = 0 ; nodeIdx < nodeCount ; ++nodeIdx )
                    {
                      const auto& node = primitiveGroup.nodes(nodeIdx);

                      double lat = sNanoDegreeScale * ( latOffset + ( granularity * node.lat() ) );
                      double lon = sNanoDegreeScale * ( lonOffset + ( granularity * node.lon() ) );

                      tOSMNodeShPtr nodePtr = std::make_shared<COSMNode>( node.id(), DEG2RAD( lat), DEG2RAD(lon) );

                      int keyCount(node.keys_size());
                      for (int kIdx = 0 ; kIdx < keyCount ; ++kIdx )
                      {
                        nodePtr->addOSMNodeProperty( osmData.stringtable().s(node.keys(kIdx)), osmData.stringtable().s(node.vals(kIdx)) );
                      }

                      m_osmModelBuilder.AddNode(nodePtr);
                    }

                    // extracting dense nodes
                    if ( primitiveGroup.has_dense() )
                    {
                      const auto& denseNodes( primitiveGroup.dense() );

                      int kvIdx(0);
                      int kvCount(denseNodes.keys_vals_size());
                      int nodesCount(denseNodes.id_size() );
                      int64_t nodeId(0);
                      int64_t nodeLat(0);
                      int64_t nodeLon(0);

                      for ( int nIdx = 0 ; nIdx < nodesCount ; ++nIdx )
                      {
                        nodeId += denseNodes.id(nIdx);
                        nodeLat += denseNodes.lat(nIdx);
                        nodeLon += denseNodes.lon(nIdx);

                        double lat = sNanoDegreeScale * ( latOffset + ( granularity * nodeLat ) );
                        double lon = sNanoDegreeScale * ( lonOffset + ( granularity * nodeLon ) );

                        tOSMNodeShPtr nodePtr = std::make_shared<COSMNode>( nodeId, 
                        DEG2RAD( lat ), 
                        DEG2RAD( lon ) );

                        int keyStringId( 0);
                        do
                        {
                          keyStringId =  denseNodes.keys_vals(kvIdx) ;
                          ++kvIdx;
                          if ( 0 != keyStringId )
                          {
                            int valueStringId( denseNodes.keys_vals(kvIdx) );
                            ++kvIdx;
                            nodePtr->addOSMNodeProperty( osmData.stringtable().s(keyStringId), osmData.stringtable().s(valueStringId) );
                          }
                        } while ( (0 != keyStringId) && ( kvIdx < kvCount) );

                        m_osmModelBuilder.AddNode(nodePtr);
                      }
                    }
                  }

                  if ( eWays & primitivesToRead )
                  {
                    //extracting ways
                    int wayCount(primitiveGroup.ways_size() );
                    for( size_t i = 0 ; i < wayCount ; ++i )
                    {
                      bool addToModel(false);
                      const auto& pbfWay( primitiveGroup.ways(i));

                      tWayShPtr ptrWay = std::make_shared<COSMWay>( pbfWay.id() );

                      size_t tagCount( pbfWay.keys_size() );
                      for ( size_t tagI = 0 ; tagI < tagCount ; ++tagI )
                      {
                        if ( !addToModel && ("highway" == osmData.stringtable().s( pbfWay.keys(tagI)) ) )
                        {
                          addToModel = true;
                        }
                        ptrWay->AddProperty( osmData.stringtable().s( pbfWay.keys(tagI)) , osmData.stringtable().s(pbfWay.vals(tagI)));
                      }

                      if (addToModel)
                      {
                        m_osmModelBuilder.AddWay(ptrWay); 
                        size_t waypointCount( pbfWay.refs_size() );
                        int64_t wayPointRef(0);
                        for ( size_t wI = 0 ; wI < waypointCount ; ++ wI )
                        {
                          wayPointRef += pbfWay.refs(wI);

                          m_osmModelBuilder.AddWaypoint( pbfWay.id(), wayPointRef );
                        }   
                      }
                    }
                  }
                }
              }
              else
              {
                cout << "Parse failed" << endl;
              }
            }
            else
            {
              cout << "Other option" << endl;
            }
          }
        } else //if ( dataBlob.has_raw() )
        {
          cout << " raw data " << endl;
        }
      }
      else 
      {
        cout << "finishing" << endl;
      }
    }
  }
  return retVal;
}

}