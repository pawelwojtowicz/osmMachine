#include "CSimpleZoneMonitor.h"
#include <GeoBase/GeoUtils.h>
#include <iostream>
namespace GeoZoneMonitor
{

CSimpleZoneMonitor::CSimpleZoneMonitor( const double lat, const double lon, const double radius)
: m_geoZoneCenter( DEG2RAD(lat), DEG2RAD(lon) )
, m_zoneRadius( radius )
{

}

CSimpleZoneMonitor::~CSimpleZoneMonitor()
{

}

bool CSimpleZoneMonitor::IsInsideArea( const osmMachine::CGeoPoint& point )
{
  std::cout << " --- " << osmMachine::GeoUtils::Point2PointDistance( point, m_geoZoneCenter) << std::endl;
  return ( osmMachine::GeoUtils::Point2PointDistance( point, m_geoZoneCenter) <= m_zoneRadius );
}

}