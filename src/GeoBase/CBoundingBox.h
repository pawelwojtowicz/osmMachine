#pragma once
#include "CGeoPoint.h"

namespace GeoBase
{
class CBoundingBox
{
public:
  CBoundingBox();
  virtual ~CBoundingBox();

  void IncludeGeoPoint( const CGeoPoint& point);

  bool IsInsideBBox( const CGeoPoint& point );

private:
  double m_latMin;
  double m_lonMin;
  double m_latMax;
  double m_lonMax;
};
}