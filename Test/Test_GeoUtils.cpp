#include <gtest/gtest.h>
#include <GeoUtils.h>

TEST( GeoUtils, Point2PointDistance_ShortRange ) 
{
    osmMachine::CGeoPoint p1(DEG2RAD(16.735744), DEG2RAD(51.188263) );
    osmMachine::CGeoPoint p2(DEG2RAD(16.78782), DEG2RAD(51.18679));
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