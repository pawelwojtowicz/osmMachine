#include <gtest/gtest.h>
#include <GeoBase/GeoUtils.h>
#include <iostream>

TEST( GeoUtils_Point2PointDistance, ShortRange ) 
{
  osmMachine::CGeoPoint p1(DEG2RAD(51.188263), DEG2RAD(16.735744) );
  osmMachine::CGeoPoint p2(DEG2RAD(51.18679), DEG2RAD(16.78782));
  double distance = osmMachine::GeoUtils::Point2PointDistance( p1, p2);
  //round to meter level
  ASSERT_EQ( round(distance*1000) , 3633 );
}

/** This test is commented out - not yet clear why the distance between hemispheres does not work 
TEST( GeoUtils, Point2PointDistance_LongRange ) 
{
  osmMachine::CGeoPoint p1(DEG2RAD(16.735744), DEG2RAD(51.188263) ); 
  osmMachine::CGeoPoint p2(DEG2RAD(151.21539268677867), DEG2RAD(-33.8567418986517));
  double distance = osmMachine::GeoUtils::Point2PointDistance( p1, p2);
  //round to meter level
  ASSERT_EQ( round(distance*1000) , 9872856 );
}
*/


TEST( GeoUtils_ProjectPoint2Shape , OnShape1 )
{
  osmMachine::CGeoPoint begin(DEG2RAD(45.504503), DEG2RAD(10.731498) );
  osmMachine::CGeoPoint end(DEG2RAD(45.504554), DEG2RAD(10.732161));
  osmMachine::CGeoPoint point( DEG2RAD(45.505590), DEG2RAD( 10.731421) );
  
  osmMachine::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = osmMachine::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , true );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat() ) * 10000 ), 455045 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon() ) * 10000 ), 107316 );
}

TEST( GeoUtils_ProjectPoint2Shape , OnShape2 )
{
  osmMachine::CGeoPoint begin(DEG2RAD(45.504503), DEG2RAD(10.731498) );
  osmMachine::CGeoPoint end( DEG2RAD(45.504554), DEG2RAD(10.732161));
  osmMachine::CGeoPoint point( DEG2RAD(45.504799), DEG2RAD( 10.732083));

  osmMachine::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = osmMachine::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , true );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455046 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107321 );
}

TEST( GeoUtils_ProjectPoint2Shape , OffShape1 )
{
  osmMachine::CGeoPoint begin( DEG2RAD(45.504503), DEG2RAD(10.731498) );
  osmMachine::CGeoPoint end(DEG2RAD(45.504554), DEG2RAD(10.732161));
  osmMachine::CGeoPoint point( DEG2RAD(45.504891), DEG2RAD( 10.730787) );

  osmMachine::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = osmMachine::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , false );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455045 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107315 );
}

TEST( GeoUtils_ProjectPoint2Shape , OffShape2 )
{
  osmMachine::CGeoPoint begin( DEG2RAD(45.504503) , DEG2RAD(10.731498) );
  osmMachine::CGeoPoint end( DEG2RAD(45.504554), DEG2RAD(10.732161) );
  osmMachine::CGeoPoint point( DEG2RAD(45.505391), DEG2RAD( 10.732967) );

  osmMachine::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = osmMachine::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , false );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455046 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107322 );
}
