#include "CGeoPoint.h"

namespace GeoBase
{

CGeoPoint::CGeoPoint()
: m_valid(false)
, m_lon(0)
, m_lat(0)
{
}

CGeoPoint::CGeoPoint( const double& lat, const double& lon )
: m_valid(true)
, m_lon(lon)
, m_lat(lat)
{
}

CGeoPoint::~CGeoPoint()
{  
}
  
}