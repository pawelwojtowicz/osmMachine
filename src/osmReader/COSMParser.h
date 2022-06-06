#pragma once
#include <string>

namespace osmMachine
{

class COSMParser
{
public:
  COSMParser();
  virtual ~COSMParser();

  bool ReadOSMFile( const std::string& filename );

  private:
};
}