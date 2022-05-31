#include "CPBFReader.h"

#include <arpa/inet.h>
#include "osmFormat.pb.h"
#include "fileFormat.pb.h"
#include <iostream>
#include <fstream>
#include <zlib.h>

static const std::string sBlobType_OSMHeader = "OSMHeader";
static const std::string sBlobType_OSMData = "OSMData";
//https://www.cplusplus.com/doc/tutorial/files/



//https://allegro.pl/oferta/etui-do-oppo-a53-2020-a53s-wzory-krowa-obudowa-10664109040?utm_feed=aa34192d-eee2-4419-9a9a-de66b9dfae24&utm_term=desc-yes&utm_source=google&utm_medium=cpc&utm_campaign=_elktrk_telefony_akcesoria_pla_ss&ev_adgr=akcesoria&ev_campaign_id=14376671485&gclid=EAIaIQobChMIn8zyiv2H-AIVmuh3Ch2X1QPiEAQYASABEgJmqvD_BwE
//https://chaosinmotion.com/2011/11/21/parsing-the-new-openstreetmaps-pbf-file-format/



using namespace std;

namespace osmMachine
{
CPBFReader::CPBFReader()
{
    
}

CPBFReader::~CPBFReader()
{

}

bool CPBFReader::ReadFile( const std::string& fileName )
{
    bool retVal(true);
    std::cout << fileName.c_str()<< std::endl;

    std::ifstream myfile (fileName.c_str(), std::ios::binary);
    if ( myfile.is_open() )
    {
        int headerSize(0);
        char* buffer = new char[512000]; 

        int i(0);
        while ( myfile.read((char *)&headerSize, sizeof(headerSize) ) )
        {
            i++;
            headerSize = ntohl(headerSize);
            //cout << "Header size "<< headerSize;

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


                    size_t uncopressedDataSize( dataBlob.raw_size() );
                    char* outputBuffer = new char[uncopressedDataSize];

                    if ( Z_OK  == uncompress( (Bytef*) outputBuffer, &uncopressedDataSize, (Bytef*)dataBlob.zlib_data().c_str() , dataBlob.zlib_data().size() ) )
                    {
                        if (sBlobType_OSMHeader == dataType )
                        {
                            HeaderBlock headerBlock;
                            if (headerBlock.ParseFromArray( outputBuffer, uncopressedDataSize) )
                            {
                                cout << "Header Parsed" << endl;
                                cout << " left " << headerBlock.bbox().left() << endl;
                                cout << " right " << headerBlock.bbox().right() << endl;

                                size_t at = headerBlock.required_features_size();
                                cout << "tuka" << at;
                                for (i = 0 ; i < at ; ++i )
                                {
                                    cout << headerBlock.required_features(i) << endl;
                                }
                            }

                        } else if ( sBlobType_OSMData == dataType )
                        {
                            PrimitiveBlock osmData;
                            if ( osmData.ParseFromArray( outputBuffer, uncopressedDataSize) )
                            {
                                cout << "changesets  " << osmData.primitivegroup(0).ways_size() << endl;
                             //  cout << "something new " << osmData.primitivegroup(0).relations_size() << endl;
//                                cout << "hasWays " << osmData.primitivegroup(0).ways_size() << endl;
//                                cout << "hasRelations " << osmData.primitivegroup(0).relations_size() << endl;
                            }
                        }

                    }

                    delete[] outputBuffer;
                } else //if ( dataBlob.has_raw() )
                {
                    cout << " zstd "  << dataBlob.has_zstd_data() << endl;
                    cout << " raw data " << endl;
                }
            }

        }

        cout << i << endl;
    }




    return retVal;
}


}