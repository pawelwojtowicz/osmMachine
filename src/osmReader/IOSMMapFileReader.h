#pragma once
#include <string>
#include <vector>

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
  using tFilterSettings = std::vector<std::pair<std::string, std::string>>;
  IOSMMapFileReader() = default;
  virtual ~IOSMMapFileReader() = default;

  virtual void ConfigureWayFilter( const tFilterSettings& properties ) = 0;

  virtual bool OpenFile( const std::string& filename ) = 0;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) = 0;

private:  
  IOSMMapFileReader(const IOSMMapFileReader&) = delete;
  IOSMMapFileReader& operator=(const IOSMMapFileReader&) = delete;
};
}