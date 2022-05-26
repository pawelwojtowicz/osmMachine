#include <gtest/gtest.h>
#include <GeoUtils.h>

TEST( GeoUtils, Point2PointDistance_classic ) 
{
    osmMachine::CGeoPoint p1(DEG2RAD(51.1550319553372), DEG2RAD(16.900309450461428) );
    osmMachine::CGeoPoint p2(DEG2RAD(51.11419090729167), DEG2RAD(16.846014389863328));
    double distance = osmMachine::GeoUtils::Point2PointDistance( p1, p2);
    ASSERT_EQ( distance , 5920);
}