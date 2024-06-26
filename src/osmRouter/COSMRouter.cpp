#include "COSMRouter.h"
#include <GeoBase/GeoUtils.h>
#include "COSMRoutingPointSet.h"
#include <set>
#include "CSimpleDistanceUtilityFunction.h"
#include "CSimpleDistanceHeuristics.h"
#include <iostream>
#include "CRoutePathBuilder.h"

namespace osmMachine
{
COSMRouter::COSMRouter( const OSMRoutingNetwork& routingNetwork)
: m_routingNetwork( routingNetwork)
{

}

COSMRouter::~COSMRouter()
{
  
}

tOSMShapePath COSMRouter::FindOptimalPath( const std::list<COSMPosition>& viaPoints )
{
  tOSMShapePath path = {} ;
  auto origin = viaPoints.begin();
  auto destination = origin;
  ++destination;

  int64_t originNodeId = { 0 };

  while( viaPoints.end() != destination )
  {
    tOSMShapePath intermediatePath = FindOptimalPath( originNodeId, *origin, *destination);

    auto pathEnd = --intermediatePath.end();
    auto pathBegin = intermediatePath.begin();

    if ( pathBegin->GetOsmNodeId() == origin->GetWay()->GetBeginNode()->getId() )
    {
      CRoutePathBuilder::ConvertEntryToBegin( *origin, intermediatePath );
    } 
    else if ( pathBegin->GetOsmNodeId() == origin->GetWay()->GetEndNode()->getId() )
    {
      CRoutePathBuilder::ConvertEntryToEnd( *origin, intermediatePath);
    } 
    else 
    {
      std::cout << "Fck fck fck" << std::endl;
    }

    originNodeId = pathEnd->GetOsmNodeId();
    intermediatePath.erase(pathEnd);

    if (originNodeId == destination->GetWay()->GetBeginNode()->getId() )
    {
      CRoutePathBuilder::ConvertExitFromBegin(*destination, intermediatePath );
    } 
    else if ( originNodeId == destination->GetWay()->GetEndNode()->getId() )
    {
      CRoutePathBuilder::ConvertExitFromEnd(*destination, intermediatePath);
    } 
    else
    {
      std::cout << "Fck fck fck" << std::endl;
    }

    path.insert(path.end(), intermediatePath.begin(), intermediatePath.end());

    origin = destination;
    ++destination;
  }

  path.push_back(  CShapePoint( CShapePoint::tViaPointType::ePOI,
                origin->GetRawPosition(), 
                origin->GetPositionSnapped2OSM() ,
                origin->GetWay()->GetId(), 
                0, 
                0));

  return path;
}


tOSMShapePath COSMRouter::FindOptimalPath( const int64_t originNodeId, const COSMPosition& start, const COSMPosition& destination)
{
  std::unique_ptr<IRoutingUtilityFunction> utility = std::make_unique<CSimpleDistanceUtilityFunction>();
  std::unique_ptr<IExpectedScoreHeuristics> heuristics = std::make_unique<CSimpleDistanceHeuristics>();

  COSMRoutingPointSet openedNodesSet;
  std::set<int64_t> closedNodesSet;
  int64_t originWayId( start.GetWay()->GetId());


  if ( !start.GetWay()->IsOneWay() && ( originNodeId != start.GetWay()->GetBeginNode()->getId()  ) )
  {
    double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(start.GetWay()->GetBeginNode()), destination.GetPositionSnapped2OSM() ) };
    double score = start.GetDistanceOnSegment();
    tPtrRoutingPoint beginRoutingPoint( new COSMRoutePoint({},{},start.GetWay()->GetBeginNode(),score,toGoHeuristics) );

    openedNodesSet.AddRoutingPoint( beginRoutingPoint);
  }

  if ( ( originNodeId != start.GetWay()->GetEndNode()->getId()  ) )
  {
    double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(start.GetWay()->GetEndNode()), destination.GetPositionSnapped2OSM() ) };
    double score = start.GetWay()->GetLength() - start.GetDistanceOnSegment();
    tPtrRoutingPoint endRoutingPoint( new COSMRoutePoint({},{},start.GetWay()->GetEndNode(),score,toGoHeuristics) );

    openedNodesSet.AddRoutingPoint(endRoutingPoint);
  }

  while( openedNodesSet.NotEmpty() )
  {
    tPtrRoutingPoint routingPoint = openedNodesSet.GetBestRoutingPoint();

    if ( routingPoint->GetId() == destination.GetWay()->GetBeginNode()->getId() || ( !destination.GetWay()->IsOneWay() && (routingPoint->GetId() == destination.GetWay()->GetEndNode()->getId()) ))
    {
      return CRoutePathBuilder::BuildSolutionPath(routingPoint, destination ) ;
    }

    openedNodesSet.RemoveRoutingPoint(routingPoint->GetId() );

    closedNodesSet.insert( routingPoint->GetId() );

    tWayList waysFromNode = GetRoutingPointNeighbours( routingPoint->GetId() );

    for( auto& nextHopWay : waysFromNode )
    {
      originWayId = routingPoint->GetOriginWay() ? routingPoint->GetOriginWay()->GetId() : originWayId; 

      if ( nextHopWay->GetId() != originWayId )
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


  return {};
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

}