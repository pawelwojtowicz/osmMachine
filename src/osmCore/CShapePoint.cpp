#include "CShapePoint.h"

namespace osmMachine
{

CShapePoint::  CShapePoint( tViaPointType type, tOSMNodeShPtr rawPosition, tOSMNodeShPtr snappedPosition, const double& length, const double& heading )
: m_type(type)
, m_rawPosition(rawPosition)
, m_snappedPosition(snappedPosition)
, m_length (length)
, m_heading(heading)
{
}
}