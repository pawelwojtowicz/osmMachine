add_library( osmParser SHARED 
    COSMParser.cpp 
    COSMParser.h
)

target_link_libraries( osmParser PUBLIC tinyxml )