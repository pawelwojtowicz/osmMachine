#include "COSMParser.h"
#include <tinyxml.h>

 namespace osmMachine
 {

COSMParser::COSMParser()
{

}

COSMParser::~COSMParser()
{

}

bool ReadOSMFile( const std::string& filename )
{
    TiXmlDocument doc( filename.c_str() );
    TiXmlHandle hDoc(&doc);
    return true;
}

}

