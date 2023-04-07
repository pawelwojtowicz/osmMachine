#include <gtest/gtest.h>
#include <GeoBase/CBoundingBox.h>

TEST( CBoundingBox, Boundaries1)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_TRUE( box.IsInsideBBox( GeoBase::CGeoPoint(5,10) ) );
}

TEST( CBoundingBox, Boundaries2)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_TRUE( box.IsInsideBBox( GeoBase::CGeoPoint(1,1) ) );
}

TEST( CBoundingBox, Boundaries3)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_TRUE( box.IsInsideBBox( GeoBase::CGeoPoint(1,10) ) );
}

TEST( CBoundingBox, Boundaries4)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_TRUE( box.IsInsideBBox( GeoBase::CGeoPoint(5,1) ) );
}

TEST( CBoundingBox, Middle)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_TRUE( box.IsInsideBBox( GeoBase::CGeoPoint(3,5) ) );
}

TEST( CBoundingBox, Outside)
{
  GeoBase::CBoundingBox box;

  box.IncludeGeoPoint(GeoBase::CGeoPoint(1,1));
  box.IncludeGeoPoint(GeoBase::CGeoPoint(5,10));


  ASSERT_FALSE( box.IsInsideBBox( GeoBase::CGeoPoint(10,5) ) );
}
