#include "CGeoPoint.h"

namespace osmMachine
{

CGeoPoint::CGeoPoint()
: m_valid(false)
, m_lon(0)
, m_lat(0)
{
}

CGeoPoint::CGeoPoint(const double& lon, const double& lat)
: m_valid(true)
, m_lon(lon)
, m_lat(lat)
{
}

CGeoPoint::~CGeoPoint()
{  
}
  
}