#pragma once
#include <string>

namespace osmMachine
{
enum tOSMPrimitiveType
{
  eNodes = 0x01,
  eWays = 0x02,
  eRelations = 0x04,
  eAll = eNodes | eWays | eRelations
};

class IOSMMapFileReader
{
public:
  IOSMMapFileReader() = default;
  virtual ~IOSMMapFileReader() = default;

  virtual bool ReadMapFile( const std::string& fileName , const tOSMPrimitiveType primitivesToRead ) = 0;

  
  IOSMMapFileReader(const IOSMMapFileReader&) = delete;
  IOSMMapFileReader& operator=(const IOSMMapFileReader&) = delete;
};
}