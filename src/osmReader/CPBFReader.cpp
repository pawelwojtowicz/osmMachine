#include "CPBFReader.h"
#include <arpa/inet.h>
#include "osmFormat.pb.h"
#include "fileFormat.pb.h"
#include <iostream>
#include <fstream>
#include <zlib.h>

#include <COSMNode.h>

using namespace std;

static const std::string sBlobType_OSMHeader = "OSMHeader";
static const std::string sBlobType_OSMData = "OSMData";
constexpr size_t maxBlobSize( 32 * 1024 * 1024);
constexpr double sNanoDegreeScale( 0.000000001);
constexpr int64_t sDflt_LatOffset = 0;
constexpr int64_t sDflt_LonOffset = 0;
constexpr int64_t sDflt_Granularity = 100;

//https://allegro.pl/oferta/etui-do-oppo-a53-2020-a53s-wzory-krowa-obudowa-10664109040?utm_feed=aa34192d-eee2-4419-9a9a-de66b9dfae24&utm_term=desc-yes&utm_source=google&utm_medium=cpc&utm_campaign=_elktrk_telefony_akcesoria_pla_ss&ev_adgr=akcesoria&ev_campaign_id=14376671485&gclid=EAIaIQobChMIn8zyiv2H-AIVmuh3Ch2X1QPiEAQYASABEgJmqvD_BwE
//https://chaosinmotion.com/2011/11/21/parsing-the-new-openstreetmaps-pbf-file-format/

namespace osmMachine
{
CPBFReader::CPBFReader( IOSMModelBuilder& osmModelBuilder)
: m_osmModelBuilder( osmModelBuilder )
{
    
}

CPBFReader::~CPBFReader()
{

}

bool CPBFReader::ReadFile( const std::string& fileName )
{
    bool retVal(true);

    std::ifstream myfile (fileName.c_str(), std::ios::binary);
    if ( myfile.is_open() )
    {
        int headerSize(0);
        char* buffer = new char[maxBlobSize]; 

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
                    char* outputBuffer = new char[uncopressedDataSize];



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
                                int64_t latOffset(sDflt_LatOffset);
                                int64_t lonOffset(sDflt_LonOffset);
                                int64_t granularity( sDflt_Granularity);
                                if ( osmData.has_lat_offset() )
                                {
                                    latOffset = osmData.lat_offset();
                                }
                                if ( osmData.has_lon_offset() )
                                {
                                    lonOffset = osmData.lon_offset();
                                }
                                if ( osmData.has_granularity() )
                                {
                                    granularity = osmData.granularity();
                                }

                                size_t primitiveGroupCount(osmData.primitivegroup_size());
                                for(size_t i = 0 ; i < primitiveGroupCount; ++i)
                                {
                                    const auto& primitiveGroup = osmData.primitivegroup(i);

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
                                                int keyStringId( denseNodes.keys_vals(kvIdx));
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
                    delete[] outputBuffer;
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

void CPBFReader::ExtractNodes( const Nodes& nodes, const int64_t& latOffset, const int64_t& lonOffset, const int64_t&granularity )
{

}


}