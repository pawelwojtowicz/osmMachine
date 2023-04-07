#pragma once
#include <GeoBase/CGeoPoint.h>

namespace osmMachine
{
class CGPSPosition : public GeoBase::CGeoPoint
{
  CGPSPosition();
  CGPSPosition(double latDeg,double longDeg);
  
  virtual ~CGPSPosition();

  double GetAltitude() const { return m_altitude;};
  double GetHeading() const { return m_heading;};
  double GetSpeed() const { return m_speed;};

private:
  double m_altitude;
  double m_heading;
  double m_speed;
};
}