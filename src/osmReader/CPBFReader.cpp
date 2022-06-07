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
: m_osmModelBuilder( osmModelBuilder )
{
    
}

CPBFReader::~CPBFReader()
{

}

bool CPBFReader::ReadMapFile( const std::string& fileName , const tOSMPrimitiveType primitivesToRead )
{
  bool retVal(true);

  std::ifstream myfile (fileName.c_str(), std::ios::binary);
  if ( myfile.is_open() )
  {
    int headerSize(0);
    char* buffer = new char[maxBlobSize];
    char* outputBuffer = new char[maxBlobSize];

    while ( myfile.read((char *)&headerSize, sizeof(headerSize) ) )
    {
      headerSize = ntohl(headerSize);

      myfile.read((char*)buffer, headerSize) ;
      BlobHeader blobHeader;
      blobHeader.ParseFromArray(buffer, headerSize);

      std::string dataType = blobHeader.type();
      if ( myfile.read((char*)buffer, blobHeader.datasize() ) )
      {
        Blob dataBlob; 
        dataBlob.ParseFromArray(buffer, blobHeader.datasize());

        if ( dataBlob.has_zlib_data() )
        {
          size_t uncopressedDataSize( maxBlobSize );

          if ( Z_OK  == uncompress( (Bytef*) outputBuffer, &uncopressedDataSize, (Bytef*)dataBlob.zlib_data().c_str() , dataBlob.zlib_data().size() ) )
          {
            if (sBlobType_OSMHeader == dataType )
            {
              HeaderBlock headerBlock;
              if (headerBlock.ParseFromArray( outputBuffer, uncopressedDataSize) )
              {
                m_osmModelBuilder.NotifyBoundingBox( sNanoDegreeScale * headerBlock.bbox().left(),
                sNanoDegreeScale * headerBlock.bbox().top(),
                sNanoDegreeScale * headerBlock.bbox().right(),
                sNanoDegreeScale * headerBlock.bbox().bottom() );

              }
            } else if ( sBlobType_OSMData == dataType )
            {
              PrimitiveBlock osmData;
              if ( osmData.ParseFromArray( outputBuffer, uncopressedDataSize) )
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
    delete[] outputBuffer;
    delete[] buffer;
    myfile.close();
  }
  return retVal;
}

}