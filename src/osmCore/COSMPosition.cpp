#include "COSMPosition.h"

namespace osmMachine
{

COSMPosition::COSMPosition()
: m_ptrWay()
, m_waySegmentIdex(0)
, m_distanceOnSegment(0.0)
, m_rawGeoPoint()
, m_snappedToMap()
{

}

COSMPosition::COSMPosition( const tWayShPtr ptrWay, 
                            const int waySegmentIdex, 
                            const double distanceOnSegment, 
                            const double rawFromProjectionDistance, 
                            const GeoBase::CGeoPoint& rawGeoPoint, const GeoBase::CGeoPoint& snappedToMap)
: m_ptrWay(ptrWay)
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