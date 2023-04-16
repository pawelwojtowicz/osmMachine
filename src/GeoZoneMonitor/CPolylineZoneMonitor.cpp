#include "CPolylineZoneMonitor.h"
#include <algorithm>

namespace GeoZoneMonitor
{
CPolylineZoneMonitor::CPolylineZoneMonitor(const std::vector<GeoBase::CGeoPoint>& definition)
: m_boundingBox()
{
  PreprocessGeoZoneDefinition(definition);
}

CPolylineZoneMonitor::~CPolylineZoneMonitor()
{

}

void CPolylineZoneMonitor::PreprocessGeoZoneDefinition( const std::vector<GeoBase::CGeoPoint>& definition)
{
  int polylineSize = definition.size();
  if ( polylineSize > 2 )
  {
    m_boundingBox.IncludeGeoPoint( definition[0] );

    for( int pLineIdx = 0; pLineIdx < polylineSize ; ++pLineIdx )
    {
      m_boundingBox.IncludeGeoPoint( definition[pLineIdx%polylineSize] );
      m_lineGuards.push_back(CLineIntersectionDetector(definition[pLineIdx], definition[(pLineIdx+1)%polylineSize]));
    }
  }
}

bool CPolylineZoneMonitor::IsInsideArea( const GeoBase::CGeoPoint& point )
{
  if ( !m_boundingBox.IsInsideBBox( point ) )
  {
    return false;
  }
  return ( std::count_if(m_lineGuards.begin(), m_lineGuards.end() , [point]( const auto& detector) { return detector.Intersects( point );})%2);
}

}