#include "COSMRouter.h"
#include <GeoBase/GeoUtils.h>
#include "COSMRoutingPointSet.h"
#include <set>
#include "CSimpleDistanceUtilityFunction.h"
#include "CSimpleDistanceHeuristics.h"

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
  std::unique_ptr<IRoutingUtilityFunction> utility = std::make_unique<CSimpleDistanceUtilityFunction>();
  std::unique_ptr<IExpectedScoreHeuristics> heuristics = std::make_unique<CSimpleDistanceHeuristics>();

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

    for( auto& nextHopWay : waysFromNode )
    {
      if ( nextHopWay->GetId() != routingPoint->GetOriginWay()->GetId() )
      {
        auto nextOSMNode = routingPoint->GetId() != nextHopWay->GetBeginNode()->getId() ? nextHopWay->GetBeginNode() : nextHopWay->GetEndNode();

        if ( closedNodesSet.end() == closedNodesSet.find( nextOSMNode->getId() )  )
        {
          double nextHopScore = utility->CalculateScore(routingPoint , nextHopWay );

          if ( !openedNodesSet.Contains( nextOSMNode->getId() ) )
          {
            double toGoHeuristics = heuristics->CalcuateExpectedScoreThroughPoint(nextOSMNode, destination );
            tPtrRoutingPoint endRoutingPoint( new COSMRoutePoint(routingPoint,nextHopWay,nextOSMNode,nextHopScore,toGoHeuristics) );
            openedNodesSet.AddRoutingPoint(endRoutingPoint);
          }
          else
          {
            auto nodeToUpdate = openedNodesSet.GetRoutingPointById( nextOSMNode->getId() );
            if ( nodeToUpdate->GetScore() > nextHopScore )
            {
              nodeToUpdate->UpdateScore( routingPoint, nextHopWay, nextHopScore);
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
  tPtrRoutingPoint iterajszn(routingPoint);

  tOSMPath path;

  while ( iterajszn )
  {
    path.push_front( iterajszn->GetOriginWay() );
    iterajszn = iterajszn->GetPreviousRoutingPoint();
  }

  for ( auto way : path)
  {
    way->Print();
  }
  destination.GetWay()->Print();

  return {};
}

}