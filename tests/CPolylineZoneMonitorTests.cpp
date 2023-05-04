#include <gtest/gtest.h>
#include <GeoBase/GeoDefs.h>
#include <GeoBase/CGeoPoint.h>
#include <GeoZoneMonitor/CPolylineZoneMonitor.h>

std::vector<GeoBase::CGeoPoint> geoZoneDefinition = {
  GeoBase::CGeoPoint(DEG2RAD(51.1497334937856), DEG2RAD(17.03222834471153)),
  GeoBase::CGeoPoint(DEG2RAD(51.14954666823577), DEG2RAD(17.03670407222367)),
  GeoBase::CGeoPoint(DEG2RAD(51.1488253069317), DEG2RAD(17.037399009582302)),
  GeoBase::CGeoPoint(DEG2RAD(51.14855025252997), DEG2RAD(17.034619260147778)),
  GeoBase::CGeoPoint(DEG2RAD(51.147564194976354), DEG2RAD(17.034412433552948)),
  GeoBase::CGeoPoint(DEG2RAD(51.14737217079148), DEG2RAD(17.037423828773683)),
  GeoBase::CGeoPoint(DEG2RAD(51.14711267738047), DEG2RAD(17.036728891415052)),
  GeoBase::CGeoPoint(DEG2RAD(51.14728394319542), DEG2RAD(17.032592359518432)),
  GeoBase::CGeoPoint(DEG2RAD(51.1497334937856), DEG2RAD(17.03222834471153))
};

TEST( CPolylineZoneMonitor, P1_NotInTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1470), DEG2RAD(17.0340));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CPolylineZoneMonitor, P2_InTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1475 ), DEG2RAD(17.0345));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , true );
}

TEST( CPolylineZoneMonitor, P3_NotInTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1478 ), DEG2RAD(17.0350));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CPolylineZoneMonitor, P4_InTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0370));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , true );
}

TEST( CPolylineZoneMonitor, P5_InTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1490 ), DEG2RAD(17.0325));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , true );
}

TEST( CPolylineZoneMonitor, P6_NotInTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1480 ), DEG2RAD(17.0315));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CPolylineZoneMonitor, P7_NotInTheArea ) 
{
  GeoZoneMonitor::CPolylineZoneMonitor monitor( geoZoneDefinition );

  GeoBase::CGeoPoint examinedPoint(DEG2RAD(51.1500 ), DEG2RAD(17.0350));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}
