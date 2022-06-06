#pragma once
#include <string>
#include "IOSMModelBuilder.h"

namespace osmMachine
{

class COSMParser
{
public:
  COSMParser(IOSMModelBuilder& osmModelBuilder);
  virtual ~COSMParser();

  bool ReadFile( const std::string& filename );

private:

  IOSMModelBuilder& m_osmModelBuilder;
};
}