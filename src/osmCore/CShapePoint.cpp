#include "CShapePoint.h"
#include <iostream>
namespace osmMachine
{

CShapePoint::CShapePoint( tViaPointType type, tOSMNodeShPtr rawPosition, tOSMNodeShPtr snappedPosition, const double& length, const double& heading )
: m_type(type)
, m_osmNodeId( snappedPosition->getId() )
, m_osmWayId(0)
, m_rawPosition(*rawPosition)
, m_snappedPosition(*snappedPosition)
, m_length (length)
, m_heading(heading)
{
  std::cout << "ciu ciu = " << snappedPosition->getId() << std::endl;
}

const int64_t CShapePoint::GetOsmNodeId() const
{
  return m_osmNodeId;
}

const GeoBase::CGeoPoint& CShapePoint::getOSMPosition() const
{
  return m_snappedPosition;
}

}