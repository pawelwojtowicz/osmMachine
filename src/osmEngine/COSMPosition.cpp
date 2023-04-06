#include "COSMPosition.h"

namespace osmMachine
{

COSMPosition::COSMPosition()
: m_wayId(0)
, m_waySegmentIdex(0)
, m_distanceOnSegment(0.0)
, m_rawGeoPoint()
, m_snappedToMap()
{

}

COSMPosition::COSMPosition( const int64_t wayId, const int waySegmentIdex, const double distanceOnSegment, const double rawFromProjectionDistance, const CGeoPoint& rawGeoPoint, const CGeoPoint& snappedToMap)
: m_wayId(wayId)
, m_waySegmentIdex(waySegmentIdex)
, m_distanceOnSegment(distanceOnSegment)
, m_rawFromProjectionDistance(rawFromProjectionDistance)
, m_rawGeoPoint(rawGeoPoint)
, m_snappedToMap(snappedToMap)
{

}


bool COSMPosition::IsValid() const
{
  return ( m_rawGeoPoint.isValid() && m_snappedToMap.isValid() );
}

}