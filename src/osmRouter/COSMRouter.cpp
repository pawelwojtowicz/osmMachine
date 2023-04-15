#include "COSMRouter.h"
#include <GeoBase/GeoUtils.h>
#include "COSMRoutingPointSet.h"
#include <set>

namespace osmMachine
{
COSMRouter::COSMRouter( const OSMRoutingNetwork& routingNetwork)
: m_routingNetwork( routingNetwork)
{

}

COSMRouter::~COSMRouter()
{
  
}

tOSMPath COSMRouter::FindOptimalPath( const COSMPosition& start, const COSMPosition& destination)
{
  COSMRoutingPointSet openedNodesSet;
  std::set<int64_t> closedNodesSet;


  if ( !start.GetWay()->IsOneWay() )
  {
    double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(start.GetWay()->GetBeginNode()), destination.GetPositionSnapped2OSM() ) };
    double score = start.GetDistanceOnSegment();
    tPtrRoutingPoint beginRoutingPoint( new COSMRoutePoint({},start.GetWay(),start.GetWay()->GetBeginNode(),score,toGoHeuristics) );

    openedNodesSet.AddRoutingPoint( beginRoutingPoint);
  }

  {
    double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(start.GetWay()->GetEndNode()), destination.GetPositionSnapped2OSM() ) };
    double score = start.GetWay()->GetLength() - start.GetDistanceOnSegment();
    tPtrRoutingPoint endRoutingPoint( new COSMRoutePoint({},start.GetWay(),start.GetWay()->GetEndNode(),score,toGoHeuristics) );

    openedNodesSet.AddRoutingPoint(endRoutingPoint);
  }

  while( openedNodesSet.NotEmpty() )
  {
    tPtrRoutingPoint routingPoint = openedNodesSet.GetBestRoutingPoint();

    if ( routingPoint->GetId() == destination.GetWay()->GetBeginNode()->getId() || ( !destination.GetWay()->IsOneWay() && (routingPoint->GetId() == destination.GetWay()->GetEndNode()->getId()) ))
    {
      return BuildSolutionPath(routingPoint, destination );
    }

    openedNodesSet.RemoveRoutingPoint(routingPoint->GetId() );

    closedNodesSet.insert( routingPoint->GetId() );

    tWayList waysFromNode = GetRoutingPointNeighbours( routingPoint->GetId() );

    for( auto& way : waysFromNode )
    {
      if ( way->GetId() != routingPoint->GetOriginWay()->GetId() )
      {
        auto nextOSMNode = routingPoint->GetId() != way->GetBeginNode()->getId() ? way->GetBeginNode() : way->GetEndNode();

        if ( closedNodesSet.end() == closedNodesSet.find( nextOSMNode->getId() )  )
        {
          double nextHopScore = routingPoint->GetScore() + way->GetLength();

          if ( !openedNodesSet.Contains( nextOSMNode->getId() ) )
          {
            double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(nextOSMNode), destination.GetPositionSnapped2OSM() ) };
            tPtrRoutingPoint endRoutingPoint( new COSMRoutePoint(routingPoint,way,start.GetWay()->GetEndNode(),nextHopScore,toGoHeuristics) );
            openedNodesSet.AddRoutingPoint(endRoutingPoint);
          }
          else
          {
            auto nodeToUpdate = openedNodesSet.GetRoutingPointById( nextOSMNode->getId() );
            if ( nodeToUpdate->GetScore() > nextHopScore )
            {
              nodeToUpdate->UpdateScore( routingPoint, way, nextHopScore);
            }
          }
        } 
      }
    }


  }


  return tOSMPath();
}

tWayList COSMRouter::GetRoutingPointNeighbours( const int64_t osmNodeId )
{
  auto osmWaysFromNodeIter = m_routingNetwork.nodeId2Ways.find( osmNodeId );
  if ( m_routingNetwork.nodeId2Ways.end() != osmWaysFromNodeIter)
  {
    return osmWaysFromNodeIter->second;
  }

  return {};
}

tOSMPath COSMRouter::BuildSolutionPath( tPtrRoutingPoint routingPoint, const COSMPosition& destination )
{
  return {};
}

}