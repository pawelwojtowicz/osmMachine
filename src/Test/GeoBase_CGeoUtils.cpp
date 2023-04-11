#include <gtest/gtest.h>
#include <GeoBase/GeoUtils.h>
#include <iostream>

TEST( GeoUtils_Point2PointDistance, ShortRange ) 
{
  GeoBase::CGeoPoint p1(DEG2RAD(51.188263), DEG2RAD(16.735744) );
  GeoBase::CGeoPoint p2(DEG2RAD(51.18679), DEG2RAD(16.78782));
  double distance = GeoBase::GeoUtils::Point2PointDistance( p1, p2);
  //round to meter level
  ASSERT_EQ( round(distance*1000) , 3633 );
}

/** This test is commented out - not yet clear why the distance between hemispheres does not work 
TEST( GeoUtils, Point2PointDistance_LongRange ) 
{
  GeoBase::CGeoPoint p1(DEG2RAD(16.735744), DEG2RAD(51.188263) ); 
  GeoBase::CGeoPoint p2(DEG2RAD(151.21539268677867), DEG2RAD(-33.8567418986517));
  double distance = GeoBase::GeoUtils::Point2PointDistance( p1, p2);
  //round to meter level
  ASSERT_EQ( round(distance*1000) , 9872856 );
}
*/


TEST( GeoUtils_ProjectPoint2Shape , OnShape1 )
{
  GeoBase::CGeoPoint begin(DEG2RAD(45.504503), DEG2RAD(10.731498) );
  GeoBase::CGeoPoint end(DEG2RAD(45.504554), DEG2RAD(10.732161));
  GeoBase::CGeoPoint point( DEG2RAD(45.505590), DEG2RAD( 10.731421) );
  
  GeoBase::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = GeoBase::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , true );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat() ) * 10000 ), 455045 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon() ) * 10000 ), 107316 );
}

TEST( GeoUtils_ProjectPoint2Shape , OnShape2 )
{
  GeoBase::CGeoPoint begin(DEG2RAD(45.504503), DEG2RAD(10.731498) );
  GeoBase::CGeoPoint end( DEG2RAD(45.504554), DEG2RAD(10.732161));
  GeoBase::CGeoPoint point( DEG2RAD(45.504799), DEG2RAD( 10.732083));

  GeoBase::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = GeoBase::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , true );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455046 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107321 );
}

TEST( GeoUtils_ProjectPoint2Shape , OffShape1 )
{
  GeoBase::CGeoPoint begin( DEG2RAD(45.504503), DEG2RAD(10.731498) );
  GeoBase::CGeoPoint end(DEG2RAD(45.504554), DEG2RAD(10.732161));
  GeoBase::CGeoPoint point( DEG2RAD(45.504891), DEG2RAD( 10.730787) );

  GeoBase::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = GeoBase::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , false );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455045 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107315 );
}

TEST( GeoUtils_ProjectPoint2Shape , OffShape2 )
{
  GeoBase::CGeoPoint begin( DEG2RAD(45.504503) , DEG2RAD(10.731498) );
  GeoBase::CGeoPoint end( DEG2RAD(45.504554), DEG2RAD(10.732161) );
  GeoBase::CGeoPoint point( DEG2RAD(45.505391), DEG2RAD( 10.732967) );

  GeoBase::CGeoPoint projection;
  double distance(0);
  bool projectedOnTheShape = GeoBase::GeoUtils::ProjectPoint2Shape( point, begin,end,projection,distance );

  ASSERT_EQ( projectedOnTheShape , false );
  ASSERT_EQ( projection.isValid() , true);
  ASSERT_EQ( round(RAD2DEG(projection.getLat()) * 10000 ), 455046 );
  ASSERT_EQ( round(RAD2DEG(projection.getLon()) * 10000 ), 107322 );
}


TEST( GeoUtils_BearingDEG , North )
{
  GeoBase::CGeoPoint begin( DEG2RAD(0) , DEG2RAD(0) );
  GeoBase::CGeoPoint end( DEG2RAD(15.0), DEG2RAD(0) );

  ASSERT_EQ( GeoBase::GeoUtils::BearingDEG(begin, end ) , 0 );
}

TEST( GeoUtils_BearingDEG , West )
{
  GeoBase::CGeoPoint begin( DEG2RAD(0) , DEG2RAD(0) );
  GeoBase::CGeoPoint end( DEG2RAD(0), DEG2RAD(15.0) );

  ASSERT_EQ( GeoBase::GeoUtils::BearingDEG(begin, end ) , 90 );
}

TEST( GeoUtils_BearingDEG , South )
{
  GeoBase::CGeoPoint begin( DEG2RAD(0) , DEG2RAD(0) );
  GeoBase::CGeoPoint end( DEG2RAD(-15.0), DEG2RAD(0.0) );

  ASSERT_EQ( GeoBase::GeoUtils::BearingDEG(begin, end ) , 180 );
}

TEST( GeoUtils_BearingDEG , East )
{
  GeoBase::CGeoPoint begin( DEG2RAD(0) , DEG2RAD(0) );
  GeoBase::CGeoPoint end( DEG2RAD(0.0), DEG2RAD(-15.0) );

  ASSERT_EQ( GeoBase::GeoUtils::BearingDEG(begin, end ) , -90 );
}
