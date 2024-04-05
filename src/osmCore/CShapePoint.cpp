#include "CShapePoint.h"

namespace osmMachine
{

CShapePoint::CShapePoint( tViaPointType type, 
                          tOSMNodeShPtr rawPosition, 
                          tOSMNodeShPtr snappedPosition, 
                          const int64_t osmWayId,
                          const double length, 
                          const int heading )
: m_type(type)
, m_osmNodeId( snappedPosition->getId() )
, m_osmWayId(osmWayId)
, m_rawPosition(*rawPosition)
, m_snappedPosition(*snappedPosition)
, m_length (length)
, m_heading(heading)
{
}

CShapePoint::CShapePoint(  tViaPointType type, 
                const GeoBase::CGeoPoint& rawPosition, 
                const GeoBase::CGeoPoint& snappedPosition, 
                const int64_t osmWayId,
                const double length, 
                const int heading )
: m_type(type)
, m_osmNodeId( -1 )
, m_osmWayId(osmWayId)
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

const double CShapePoint::GetLength() const
{
  return m_length;
}

const int CShapePoint::GetHeading() const
{
  return m_heading;
}



}