#include "COSMWay.h"
#include <iostream>

namespace osmMachine
{


COSMWay::COSMWay( const int64_t wayId)
: m_wayId(wayId)
, m_isOneWay(false)
, m_length(0)
{
}

COSMWay::~COSMWay()
{
}


void COSMWay::AddWaySegment( const CWaySegment& waySegment )
{
  // there is already begin node
  bool beginAdded( !m_waySegments.empty() );

  // add the way segment
  m_waySegments.push_back(waySegment);
  
  //way length inreases with new the length of new way segment
  m_length += waySegment.getLength();

  // there's new way end
  m_wayEnd = waySegment.getEndNode();

  if ( beginAdded )
  {
    return;
  } 
  
  // this is added only once, when the vector with segments is empty
  m_wayBegin = waySegment.getBeginNode();
}

void COSMWay::AddProperty( const std::string& key, const std::string& value )
{
  if ( 0 == key.compare("oneway") && 0 == value.compare("yes") )
  {
    m_isOneWay = true;
  }
  m_wayProperties.insert( tPropertyMap::value_type( key,value));
}


void COSMWay::Print()
{
  std::cout << m_wayId << "== Properties: [";
  for (auto property : m_wayProperties)
  {
    std::cout << property.first << "=" << property.second << "|";
  }
  std::cout << std::endl;
}

}