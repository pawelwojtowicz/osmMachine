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

    projection = CGeoPoint( projectionLon, projectionLat  );
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

}
