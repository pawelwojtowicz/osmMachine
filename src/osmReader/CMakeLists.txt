find_package(Protobuf REQUIRED)
find_package(ZLIB REQUIRED )

add_library( osmReader SHARED
    CPBFReader.cpp
    CPBFReader.h
    COSMParser.cpp 
    COSMParser.h
    COSMModelBuilder.cpp
    COSMModelBuilder.h
    COSMMapFileReader.cpp
    COSMMapFileReader.h
    COSMNetworkValidator.cpp
    COSMNetworkValidator.h
    osmFormat.pb.cc 
    osmFormat.pb.h
    fileFormat.pb.cc
    fileFormat.pb.h
)

target_link_libraries( osmReader PUBLIC tinyxml ${PROTOBUF_LIBRARY} ${ZLIB_LIBRARY} osmCore )