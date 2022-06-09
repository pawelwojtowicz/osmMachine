#include "COSMMapFileReader.h"

namespace osmMachine
{

COSMMapFileReader::COSMMapFileReader()
{

}

COSMMapFileReader::~COSMMapFileReader()
{

}

void COSMMapFileReader::ConfigureWayFilter( const tFilterSettings& properties )
{
  m_wayFilterSettings = properties;  
}


bool COSMMapFileReader::EvaluteWayProperty( const std::string& key, const std::string& value )
{
  bool toBeAdded(false);

  for( auto iter = m_wayFilterSettings.begin() ; ( m_wayFilterSettings.end() != iter) && (!toBeAdded);  ++iter   )
  {
    toBeAdded = ( key == iter->first ) && ( iter->second.empty() || value == iter->second );
  }

  return toBeAdded;

}


}