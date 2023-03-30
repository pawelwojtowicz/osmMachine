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

bool COSMPosition::IsValid() const
{
  return ( m_rawGeoPoint.isValid() && m_snappedToMap.isValid() );
}

}