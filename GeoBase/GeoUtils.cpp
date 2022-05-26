#include "GeoUtils.h"
#include "CGeoPoint.h"

namespace osmMachine
{

double GeoUtils::Point2PointDistance( const CGeoPoint& p1, const CGeoPoint& p2)
{
  double dlon = p2.getLon() - p1.getLon();
  double dlat = p2.getLat() - p2.getLat();
  double latCos = cos( ( p1.getLat() + p2.getLat() ) / 2.0 );
  return sqrt( dlon * dlon * latCos * latCos + dlat * dlat );  
}
  
}
