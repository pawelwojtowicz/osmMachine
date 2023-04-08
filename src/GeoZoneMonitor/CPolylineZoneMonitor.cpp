#include "CPolylineZoneMonitor.h"

namespace GeoZoneMonitor
{
CPolylineZoneMonitor::CPolylineZoneMonitor(const std::vector<GeoBase::CGeoPoint>& definition)
: m_boundingBox()
{

}

CPolylineZoneMonitor::~CPolylineZoneMonitor()
{

}

void CPolylineZoneMonitor::PreprocessGeoZoneDefinition( const std::vector<GeoBase::CGeoPoint>& definition)
{
  auto polylineSize = definition.size();
  if ( polylineSize > 2 )
  {
    m_boundingBox.IncludeGeoPoint( definition[0] );

    for( int pLineIdx = 0; pLineIdx < polylineSize ; ++pLineIdx )
    {
      // buildSegment evaluator
      //definition[pLineIdx], definition[pLineIdx%polylineSize]
    }

  }
}

bool CPolylineZoneMonitor::IsInsideArea( const GeoBase::CGeoPoint& point )
{
  if ( m_boundingBox.IsInsideBBox( point ) )
  {

  }
  return false;
}

}