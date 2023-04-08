#include <gtest/gtest.h>
#include <GeoBase/CGeoPoint.h>
#include <GeoZoneMonitor/CPolylineZoneMonitor.h>

std::vector<GeoBase::CGeoPoint> geoZoneDefinition;

TEST( CPolylineZoneMonitor, NotInTheArea1 ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}
