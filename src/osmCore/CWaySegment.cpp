#include "CWaySegment.h"
#include <GeoBase/GeoUtils.h>

namespace osmMachine
{
CWaySegment::CWaySegment( tOSMNodeShPtr beginNode, tOSMNodeShPtr endNode )
: m_length( 0 )
, m_heading( 0 )
, m_beginNode(beginNode)
, m_endNode( endNode)
{
  m_length = GeoBase::GeoUtils::Point2PointDistance(*m_beginNode, *m_endNode);
}
CWaySegment::~CWaySegment()
{

}

void CWaySegment::UpdateGeometry()
{
  m_length = GeoBase::GeoUtils::Point2PointDistance(*m_beginNode, *m_endNode);
  m_heading = GeoBase::GeoUtils::BearingDEG( *m_beginNode, *m_endNode );
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