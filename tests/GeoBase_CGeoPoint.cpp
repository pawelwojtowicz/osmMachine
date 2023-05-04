#include <gtest/gtest.h>
#include <GeoBase/CGeoPoint.h>

TEST( CGeoPoint, DefaultConstructor)
{
  GeoBase::CGeoPoint p1;
  ASSERT_EQ( p1.isValid(), false);
}

TEST( CGeoPoint, Construction ) 
{
  GeoBase::CGeoPoint p1( 150, 100 );
  ASSERT_EQ( p1.isValid(), true);
  ASSERT_EQ( p1.getLon(), 100);
  ASSERT_EQ( p1.getLat(), 150);
}

TEST( CGeoPoint, ComparisonOperator ) 
{
  GeoBase::CGeoPoint p1( 5,5);
  GeoBase::CGeoPoint p2( 6,6);
  GeoBase::CGeoPoint p3( 5,5);
  ASSERT_EQ( p1==p2, false);
  ASSERT_EQ( p1==p3, true);
}

TEST( CGeoPoint, CopyContstructor )
{
  GeoBase::CGeoPoint p1(5,5);
  GeoBase::CGeoPoint p2(p1);
  ASSERT_EQ( p2.isValid(), true);
  ASSERT_EQ( p1.getLon(), p2.getLon() );
  ASSERT_EQ( p1.getLat(), p2.getLat() );
}

TEST( CGeoPoint, Assignment )
{
  GeoBase::CGeoPoint p1(5,5);
  GeoBase::CGeoPoint p2(6,6);
  p1 = p2;
  ASSERT_EQ( p2.isValid(), true);
  ASSERT_EQ( p1.getLon(), p2.getLon() );
  ASSERT_EQ( p1.getLat(), p2.getLat() );
}
