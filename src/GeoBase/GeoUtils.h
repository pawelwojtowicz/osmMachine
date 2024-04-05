#pragma once
#include <cmath>
#include "CGeoPoint.h"

namespace GeoBase
{

class GeoUtils
{
private:
  GeoUtils();
  
public:
  static double Point2PointDistance( const CGeoPoint& p1, const CGeoPoint& p2);

  static bool ProjectPoint2Shape( const CGeoPoint& point, const CGeoPoint& shapeBegin, const CGeoPoint& shapeEnd, CGeoPoint& projectedPoint, double& distance );
 
  static double BearingRAD( const CGeoPoint& begin, const CGeoPoint& end);
  static int BearingDEG( const CGeoPoint& begin, const CGeoPoint& end);

  static int OpositeDirection( const int heading);

};

}
