#include <gtest/gtest.h>
#include <GeoZoneMonitor/CLineIntersectionDetector.h>


TEST( CLineIntersectionDetector, LineType_Other_NotIntersecting_Blue ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1497), DEG2RAD(17.0322)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499), DEG2RAD(17.0307)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Other_NotIntersecting_Green ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0322)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499), DEG2RAD(17.0307)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Other_NotIntersecting_Purple ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1499 ), DEG2RAD(17.0362)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1497), DEG2RAD(17.0382)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Other_Intersecting_Yellow ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1493 ), DEG2RAD(17.0372)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499 ), DEG2RAD(17.0407)));

  ASSERT_TRUE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Vertical_NotIntersecting_Blue ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0307)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499 ), DEG2RAD(17.0307)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Vertical_NotIntersecting_Green ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1497 ), DEG2RAD(17.0332)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1500 ), DEG2RAD(17.0332)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Vertical_Intersecting_Yellow ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1493 ), DEG2RAD(17.0372)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499 ), DEG2RAD(17.0372)));

  ASSERT_TRUE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Horizontal_Intersecting_Yellow ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0350)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0380)));

  ASSERT_TRUE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Horizontal_NotIntersecting_Purple ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0300)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0320)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Horizontal_NotIntersecting_Green ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1499 ), DEG2RAD(17.0380)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1499  ), DEG2RAD(17.0410)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}

TEST( CLineIntersectionDetector, LineType_Horizontal_NotIntersecting_Blue ) 
{
  GeoZoneMonitor::CLineIntersectionDetector detector( GeoBase::CGeoPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0410)),
                                                      GeoBase::CGeoPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0450)));

  ASSERT_FALSE( detector.Intersects(GeoBase::CGeoPoint(DEG2RAD(51.1496 ), DEG2RAD(17.0322) ) ) );
}