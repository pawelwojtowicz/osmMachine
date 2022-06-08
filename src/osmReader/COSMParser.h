#pragma once
#include <tinyxml.h>
#include "IOSMMapFileReader.h"
#include "IOSMModelBuilder.h"

namespace osmMachine
{

class COSMParser : public IOSMMapFileReader
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