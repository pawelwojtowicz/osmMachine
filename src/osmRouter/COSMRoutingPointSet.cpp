#include "COSMRoutingPointSet.h"
#include <algorithm>

namespace osmMachine
{
COSMRoutingPointSet::COSMRoutingPointSet()
{

}
COSMRoutingPointSet::~COSMRoutingPointSet()
{

}

bool COSMRoutingPointSet::NotEmpty()
{
  return !m_routingPoints.empty();
}

void COSMRoutingPointSet::AddRoutingPoint( tPtrRoutingPoint osmRoutingPoint )
{
  m_routingPoints.insert(tNodeId2RoutingPointMap::value_type( osmRoutingPoint->GetId(), osmRoutingPoint ) );
}

bool COSMRoutingPointSet::Contains( const int64_t routingPointId )
{
  return ( m_routingPoints.end() != m_routingPoints.find(routingPointId) );
}

tPtrRoutingPoint COSMRoutingPointSet::GetBestRoutingPoint()
{
  auto minElementIter = std::min_element(m_routingPoints.begin(), m_routingPoints.end(), []( auto rP1, auto rP2) { return (rP1.second->GetFinalScoreHeuristics() < rP2.second->GetFinalScoreHeuristics());});

  if ( m_routingPoints.end() != minElementIter )
  {
    return minElementIter->second;
  }

  return {};
}

tPtrRoutingPoint COSMRoutingPointSet::GetRoutingPointById( const int64_t routingPointId)
{
  auto routingPointIter = m_routingPoints.find(routingPointId);
  if ( routingPointIter != m_routingPoints.end() )
  {
    return routingPointIter->second;
  }
  return {};
}

void COSMRoutingPointSet::RemoveRoutingPoint( const int64_t routingPointId )
{
  m_routingPoints.erase(routingPointId);
}

}
