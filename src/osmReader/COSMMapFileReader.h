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

class COSMMapFileReader
{
public:
  using tFilterSettings = std::vector<std::pair<std::string, std::string>>;

  COSMMapFileReader();
  virtual ~COSMMapFileReader() ;

  virtual void ConfigureWayFilter( const tFilterSettings& properties );

  virtual bool OpenFile( const std::string& filename ) = 0;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) = 0;

protected:
    bool EvaluteWayProperty( const std::string& key, const std::string& value );

private:  
  COSMMapFileReader(const COSMMapFileReader&) = delete;
  COSMMapFileReader& operator=(const COSMMapFileReader&) = delete;

  tFilterSettings m_wayFilterSettings;

};
}