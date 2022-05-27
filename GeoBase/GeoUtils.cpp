#include "GeoUtils.h"
#include "CGeoPoint.h"

namespace osmMachine
{

double GeoUtils::Point2PointDistance( const CGeoPoint& p1, const CGeoPoint& p2)
{
  double dlon = p2.getLon() - p1.getLon();
  double dlat = p2.getLat() - p2.getLat();

  double a = pow( sin(dlat/2) , 2 ) + cos(p1.getLat()) * cos(p2.getLat()) * pow( sin(dlon/2) , 2);
  double c = 2 * atan2( sqrt(a) , sqrt( 1- a) );

  return s_earthRadiusKM * c;  
}
  
}
