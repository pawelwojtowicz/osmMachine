#include "CWaySegment.h"
#include <GeoUtils.h>

namespace osmMachine
{
CWaySegment::CWaySegment( tOSMNodeShPtr beginNode, tOSMNodeShPtr endNode )
: m_length( 0 )
, m_beginNode(beginNode)
, m_endNode( endNode)
{
  m_length = GeoUtils::Point2PointDistance(*m_beginNode, *m_endNode);
}
CWaySegment::~CWaySegment()
{

}

tOSMNodeShPtr CWaySegment::getBeginNode() const
{
  return m_beginNode;
}

tOSMNodeShPtr CWaySegment::getEndNode() const
{
  return m_endNode;
}

}