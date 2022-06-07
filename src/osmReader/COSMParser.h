#pragma once
#include "IOSMMapFileReader.h"
#include "IOSMModelBuilder.h"

namespace osmMachine
{

class COSMParser : public IOSMMapFileReader
{
public:
  COSMParser(IOSMModelBuilder& osmModelBuilder);
  virtual ~COSMParser();

  bool ReadMapFile( const std::string& fileName , const tOSMPrimitiveType primitivesToRead ) override;

private:

  IOSMModelBuilder& m_osmModelBuilder;
};
}