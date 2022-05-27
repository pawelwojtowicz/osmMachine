#pragma once
#include <cmath>
#include "CGeoPoint.h"

namespace osmMachine
{

class GeoUtils
{
private:
  GeoUtils();
  
public:
  static double Point2PointDistance( const CGeoPoint& p1, const CGeoPoint& p2);

  
};

}
