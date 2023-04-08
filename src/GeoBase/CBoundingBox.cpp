#include "CBoundingBox.h"
#include <limits>

namespace GeoBase
{
CBoundingBox::CBoundingBox()
: m_latMin( std::numeric_limits<double>::max() )
, m_lonMin( std::numeric_limits<double>::max() )
, m_latMax( std::numeric_limits<double>::min() )
, m_lonMax( std::numeric_limits<double>::min() )
{

}

CBoundingBox::~CBoundingBox()
{

}

void CBoundingBox::IncludeGeoPoint( const CGeoPoint& point)
{
  m_latMin = std::min( m_latMin, point.getLat() );
  m_lonMin = std::min( m_lonMin, point.getLon() );
  m_latMax = std::max( m_latMax, point.getLat() );
  m_lonMax = std::max( m_lonMax, point.getLon() );  
}

bool CBoundingBox::IsInsideBBox( const CGeoPoint& point )
{
  return  ( ( point.getLat() >= m_latMin ) && 
            ( point.getLat() <= m_latMax ) && 
            ( point.getLon() >= m_lonMin ) &&
            ( point.getLon() <= m_lonMax ) ); 
}

}