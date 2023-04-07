#pragma once
#include <GeoBase/CGeoPoint.h>

namespace GeoZoneMonitor
{
class IGeoZoneMonitor
{
public:
  virtual bool IsInsideArea( const GeoBase::CGeoPoint& point ) = 0;
};
}