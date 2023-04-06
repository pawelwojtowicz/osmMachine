#pragma once
#include <GeoBase/CGeoPoint.h>

namespace GeoZoneMonitor
{
class IGeoZoneMonitor
{
public:
  virtual bool IsInsideArea( const osmMachine::CGeoPoint& point ) = 0;
};
}