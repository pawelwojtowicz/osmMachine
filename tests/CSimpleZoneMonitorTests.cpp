#include <gtest/gtest.h>
#include <GeoBase/CGeoPoint.h>
#include <GeoBase/GeoUtils.h>
#include <GeoZoneMonitor/CSimpleZoneMonitor.h>

TEST( CSimpleZoneMonitor, NotInTheArea1 ) 
{
  GeoZoneMonitor::CSimpleZoneMonitor monitor( 37.82629555739167, -122.42212869678943, 0.01 );
  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));
  //expected distance 0.018174

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CSimpleZoneMonitor, NotInTheArea2 ) 
{
  GeoZoneMonitor::CSimpleZoneMonitor monitor( 37.82629555739167, -122.42212869678943, 0.016 );
  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CSimpleZoneMonitor, InTheArea1 ) 
{
  GeoZoneMonitor::CSimpleZoneMonitor monitor( 37.82629555739167, -122.42212869678943, 0.018 );
  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , false );
}

TEST( CSimpleZoneMonitor, InTheArea2 ) 
{
  GeoZoneMonitor::CSimpleZoneMonitor monitor( 37.82629555739167, -122.42212869678943, 0.02 );
  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , true );
}

TEST( CSimpleZoneMonitor, InTheArea3 ) 
{
  GeoZoneMonitor::CSimpleZoneMonitor monitor( 37.82629555739167, -122.42212869678943, 0.05 );
  GeoBase::CGeoPoint examinedPoint(DEG2RAD(37.82618962700794), DEG2RAD(-122.42228627656388));

  ASSERT_EQ( monitor.IsInsideArea( examinedPoint ) , true );
}
