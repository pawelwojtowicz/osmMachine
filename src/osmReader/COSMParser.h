#pragma once
#include <tinyxml.h>
#include "COSMMapFileReader.h"
#include "IOSMModelBuilder.h"

namespace osmMachine
{

class COSMParser : public COSMMapFileReader
{
public:
  COSMParser(IOSMModelBuilder& osmModelBuilder);
  virtual ~COSMParser();

  virtual bool OpenFile( const std::string& filename ) override;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) override;

private:
  TiXmlDocument m_xmlDocument;

  TiXmlElement* m_rootElement;

  IOSMModelBuilder& m_osmModelBuilder;
};
}