#include "CShapePoint.h"

namespace osmMachine
{

CShapePoint::CShapePoint( tViaPointType type, tOSMNodeShPtr rawPosition, tOSMNodeShPtr snappedPosition, const double length, const double heading )
: m_type(type)
, m_osmNodeId( snappedPosition->getId() )
, m_osmWayId(0)
, m_rawPosition(*rawPosition)
, m_snappedPosition(*snappedPosition)
, m_length (length)
, m_heading(heading)
{
}

CShapePoint::CShapePoint( tViaPointType type, const GeoBase::CGeoPoint& rawPosition, const GeoBase::CGeoPoint& snappedPosition, const double length, const double heading )
: m_type(type)
, m_osmNodeId( -1 )
, m_osmWayId(-1)
, m_rawPosition(rawPosition)
, m_snappedPosition(snappedPosition)
, m_length (length)
, m_heading(heading)
{

}

const int64_t CShapePoint::GetOsmNodeId() const
{
  return m_osmNodeId;
}

const GeoBase::CGeoPoint& CShapePoint::getOSMPosition() const
{
  return m_snappedPosition;
}

const CShapePoint::tViaPointType CShapePoint::GetType() const
{
  return m_type;
}


}