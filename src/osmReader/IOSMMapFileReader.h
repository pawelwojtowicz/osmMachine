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

  virtual bool OpenFile( const std::string& filename ) = 0;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) = 0;

private:  
  IOSMMapFileReader(const IOSMMapFileReader&) = delete;
  IOSMMapFileReader& operator=(const IOSMMapFileReader&) = delete;
};
}