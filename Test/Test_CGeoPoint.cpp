#include <gtest/gtest.h>
#include <CGeoPoint.h>

TEST( CGeoPoint, Construction ) 
{
    osmMachine::CGeoPoint p1( 100,150);
    ASSERT_EQ( p1.getLon(), 100);
    ASSERT_EQ( p1.getLat(), 150);
}

TEST( CGeoPoint, ComparisonOperator ) 
{
    osmMachine::CGeoPoint p1( 5,5);
    osmMachine::CGeoPoint p2( 6,6);
    osmMachine::CGeoPoint p3( 5,5);
    ASSERT_EQ( p1==p2, false);
    ASSERT_EQ( p1==p3, true);
}

TEST( CGeoPoint, CopyContstructor )
{
    osmMachine::CGeoPoint p1(5,5);
    osmMachine::CGeoPoint p2(p1);
    ASSERT_EQ( p1.getLon(), p2.getLon() );
    ASSERT_EQ( p1.getLat(), p2.getLat() );
}

TEST( CGeoPoint, Assignment )
{
    osmMachine::CGeoPoint p1(5,5);
    osmMachine::CGeoPoint p2(6,6);
    p1 = p2;
    ASSERT_EQ( p1.getLon(), p2.getLon() );
    ASSERT_EQ( p1.getLat(), p2.getLat() );
}
