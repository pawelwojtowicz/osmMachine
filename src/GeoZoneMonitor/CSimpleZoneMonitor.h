#pragma once
#include "IGeoZoneMonitor.h"
#include <GeoBase/CGeoPoint.h>

namespace GeoZoneMonitor
{
class CSimpleZoneMonitor : public IGeoZoneMonitor
{
public:
  CSimpleZoneMonitor( const double lat, const double lon, const double radius );
  virtual ~CSimpleZoneMonitor();

  virtual bool IsInsideArea( const GeoBase::CGeoPoint& point ) override;

private:
  GeoBase::CGeoPoint m_geoZoneCenter;

  double m_zoneRadius;
};
}