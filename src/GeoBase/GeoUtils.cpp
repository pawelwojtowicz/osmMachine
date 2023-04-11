#include "GeoUtils.h"
#include "CGeoPoint.h"
#include <numbers>
#include <fpu_control.h>

namespace GeoBase
{

double GeoUtils::Point2PointDistance( const CGeoPoint& p1, const CGeoPoint& p2)
{
  // interesting part - for setting up the floating point control register
  // on the WSL ( damn - this is crazy)
  // unsigned short Cw = 0x37f;
  // _FPU_SETCW(Cw);


  // distance between latitudes
  // and longitudes
  double dLat = (p2.getLat() - p1.getLat());              
  double dLon = (p2.getLon() - p1.getLon());
 
  // apply formulae
  double a = pow(sin(dLat / 2), 2) +
              pow(sin(dLon / 2), 2) *
              cos(p1.getLat()) * cos(p2.getLat());

  double c = 2 * asin(sqrt(a));
  return s_earthRadiusKM * c;
}
  
bool GeoUtils::ProjectPoint2Shape( const CGeoPoint& point, const CGeoPoint& shapeBegin, const CGeoPoint& shapeEnd, CGeoPoint& projection, double& distance )
{
  bool projectedOnTheLine(false);
  distance = -1;

  double dCosSquare(pow(cos( point.getLat()),2));

  double u0 = dCosSquare * ( point.getLon() - shapeBegin.getLon() ) * (  shapeEnd.getLon() - shapeBegin.getLon() ) + 
                            ( point.getLat() - shapeBegin.getLat() ) * (shapeEnd.getLat() - shapeBegin.getLat() );
  
  double u1 = dCosSquare * pow( shapeEnd.getLon() - shapeBegin.getLon() ,2 ) + pow( shapeEnd.getLat() - shapeBegin.getLat(), 2 );

  double u( u1 != 0 ? u0/u1 : 0);

  if ( u >= 0 && u <= 1 )
  {
    projectedOnTheLine = true;
    double projectionLon( shapeBegin.getLon() + u * ( shapeEnd.getLon() - shapeBegin.getLon() ) );
    double projectionLat( shapeBegin.getLat() + u * ( shapeEnd.getLat() - shapeBegin.getLat() ) );

    projection = CGeoPoint( projectionLat, projectionLon  );
    distance = Point2PointDistance( point , projection );
  }
  else
  {
    double dist2Begin = Point2PointDistance( point , shapeBegin );
    double dist2End = Point2PointDistance( point , shapeEnd );

    if ( dist2Begin < dist2End )
    {
      distance = dist2Begin;
      projection = shapeBegin;
    }
    else
    {
      distance = dist2End;
      projection = shapeEnd;
    }
  }

  return projectedOnTheLine;
}

double GeoUtils::BearingRAD( const CGeoPoint& begin, const CGeoPoint& end)
{
  const double y = sin(end.getLon() -begin.getLon() ) * cos( end.getLat() );
  const double x = cos(begin.getLat() )* sin(end.getLat() ) - sin(begin.getLat() )* cos(end.getLat() )* cos(end.getLon()-begin.getLon() );
  return atan2(y, x);
}

int GeoUtils::BearingDEG( const CGeoPoint& begin, const CGeoPoint& end )
{
  return static_cast<int>(BearingRAD( begin, end )* 180/M_PI) % 360 ;
}

}
