#include "COSMRouter.h"
#include <GeoBase/GeoUtils.h>
#include "COSMRoutingPointSet.h"
#include <set>
#include "CSimpleDistanceUtilityFunction.h"
#include "CSimpleDistanceHeuristics.h"
#include <iostream>

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

    auto pathEnd = intermediatePath.rbegin();
    auto pathBegin = intermediatePath.begin();

    if ( pathBegin->GetOsmNodeId() == origin->GetWay()->GetBeginNode()->getId() )
    {
      const auto& entrySegments = origin->GetWay()->GetWaySegments();

      for ( int i = 0 ; i < origin->GetWaySegmentIndex() ; ++i )
      {
        intermediatePath.push_front( CShapePoint( CShapePoint::tViaPointType::eEntry,
                                                  entrySegments[i].getEndNode(),
                                                  entrySegments[i].getEndNode(),
                                                  entrySegments[i].getLength(),
                                                  entrySegments[i].getHeading() ) );
      }

      double heading = GeoBase::GeoUtils::BearingDEG( origin->GetPositionSnapped2OSM(), *(entrySegments[origin->GetWaySegmentIndex()].getBeginNode()) );
      double length = GeoBase::GeoUtils::Point2PointDistance( origin->GetPositionSnapped2OSM(), *entrySegments[origin->GetWaySegmentIndex()].getBeginNode() );
      intermediatePath.push_front( CShapePoint( CShapePoint::tViaPointType::ePOI,
                                    origin->GetRawPosition(),
                                    origin->GetPositionSnapped2OSM(),
                                    length,
                                    heading));
    } 
    else if ( pathBegin->GetOsmNodeId() == origin->GetWay()->GetEndNode()->getId() )
    {
      const auto& entrySegments = origin->GetWay()->GetWaySegments();
      int lastWaySegment = entrySegments.size() -1;

      for ( int i = lastWaySegment ; i >  origin->GetWaySegmentIndex() ; --i)
      {
        intermediatePath.push_front( CShapePoint( CShapePoint::tViaPointType::eEntry,
                                                  entrySegments[i].getBeginNode(),
                                                  entrySegments[i].getBeginNode(),
                                                  entrySegments[i].getLength(),
                                                  entrySegments[i].getHeading() ) );

      }

      double heading = GeoBase::GeoUtils::BearingDEG( origin->GetPositionSnapped2OSM(), *(entrySegments[origin->GetWaySegmentIndex()].getEndNode()) );
      double length = GeoBase::GeoUtils::Point2PointDistance( origin->GetPositionSnapped2OSM(), *entrySegments[origin->GetWaySegmentIndex()].getEndNode() );
      intermediatePath.push_front( CShapePoint( CShapePoint::tViaPointType::ePOI,
                                    origin->GetRawPosition(),
                                    origin->GetPositionSnapped2OSM(),
                                    length,
                                    heading));

    } 
    else 
    {
      std::cout << "Fck fck fck" << std::endl;
    }

    if (pathEnd->GetOsmNodeId() == destination->GetWay()->GetBeginNode()->getId() )
    {
      //intermediatePath.erase(pathEnd);
      const auto& exitSegments = destination->GetWay()->GetWaySegments();

      for ( int i = 0 ; i < destination->GetWaySegmentIndex() ; ++i )
      {
        intermediatePath.push_back( CShapePoint( CShapePoint::tViaPointType::eExit,
                                                  exitSegments[i].getBeginNode(),
                                                  exitSegments[i].getBeginNode(),
                                                  exitSegments[i].getLength(),
                                                  exitSegments[i].getHeading() ) );
      }

      double heading = GeoBase::GeoUtils::BearingDEG( *(exitSegments[destination->GetWaySegmentIndex()].getBeginNode()), destination->GetPositionSnapped2OSM() );
      double length = GeoBase::GeoUtils::Point2PointDistance( *exitSegments[destination->GetWaySegmentIndex()].getBeginNode(), destination->GetPositionSnapped2OSM() );
      intermediatePath.push_back( CShapePoint( CShapePoint::tViaPointType::ePOI,
                                    destination->GetRawPosition(),
                                    destination->GetPositionSnapped2OSM(),
                                    length,
                                    heading));



    } 
    else if ( pathEnd->GetOsmNodeId() == destination->GetWay()->GetEndNode()->getId() )
    {
      const auto& exitSegments = destination->GetWay()->GetWaySegments();
      int lastSegment = exitSegments.size() - 1;

      for ( int i = lastSegment ; i > destination->GetWaySegmentIndex() ; --i)
      {

      }


    } 
    else
    {
      std::cout << "Fck fck fck" << std::endl;
    }

    originNodeId = pathEnd->GetOsmNodeId();

    path.splice(path.end(), intermediatePath);

    origin = destination;
    ++destination;
  }

  return path;
}


tOSMShapePath COSMRouter::FindOptimalPath( const int64_t originNodeId, const COSMPosition& start, const COSMPosition& destination)
{
  std::unique_ptr<IRoutingUtilityFunction> utility = std::make_unique<CSimpleDistanceUtilityFunction>();
  std::unique_ptr<IExpectedScoreHeuristics> heuristics = std::make_unique<CSimpleDistanceHeuristics>();

  COSMRoutingPointSet openedNodesSet;
  std::set<int64_t> closedNodesSet;


  if ( !start.GetWay()->IsOneWay() && ( originNodeId != start.GetWay()->GetBeginNode()->getId()  ) )
  {
    double toGoHeuristics = { GeoBase::GeoUtils::Point2PointDistance(*(start.GetWay()->GetBeginNode()), destination.GetPositionSnapped2OSM() ) };
    double score = start.GetDistanceOnSegment();
    tPtrRoutingPoint beginRoutingPoint( new COSMRoutePoint({},start.GetWay(),start.GetWay()->GetBeginNode(),score,toGoHeuristics) );

    openedNodesSet.AddRoutingPoint( beginRoutingPoint);
  }

  if ( ( originNodeId != start.GetWay()->GetEndNode()->getId()  ) )
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


  return tOSMShapePath();
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

tOSMShapePath COSMRouter::BuildSolutionPath( tPtrRoutingPoint finalGeoPoint, const COSMPosition& destination )
{
  tOSMShapePath path = {};
  tPtrRoutingPoint currentRoutingSegment(finalGeoPoint);

  int64_t originNodeId(-1);

  if ( currentRoutingSegment->GetOriginWay()->GetBeginNode()->getId() == destination.GetWay()->GetBeginNode()->getId() ||
       currentRoutingSegment->GetOriginWay()->GetEndNode()->getId() == destination.GetWay()->GetBeginNode()->getId() )
  {
    originNodeId = destination.GetWay()->GetBeginNode()->getId();
    path.push_back(CShapePoint( CShapePoint::tViaPointType::eSimple, 
                                 destination.GetWay()->GetBeginNode(), 
                                 destination.GetWay()->GetBeginNode(),
                                 0,
                                 0 ));
  }
  
  if ( currentRoutingSegment->GetOriginWay()->GetBeginNode()->getId() == destination.GetWay()->GetEndNode()->getId() ||
       currentRoutingSegment->GetOriginWay()->GetEndNode()->getId() == destination.GetWay()->GetEndNode()->getId() )
  {
    originNodeId = destination.GetWay()->GetEndNode()->getId();
    path.push_back(CShapePoint( CShapePoint::tViaPointType::eSimple, 
                                 destination.GetWay()->GetEndNode(), 
                                 destination.GetWay()->GetEndNode(),
                                 0,
                                 0 ));
  }

  while( currentRoutingSegment )
  {
    if ( currentRoutingSegment->GetOriginWay()->GetBeginNode()->getId() == originNodeId )
    {
      ConvertWayFromEnd2Begin( currentRoutingSegment, path);
    }

    if ( currentRoutingSegment->GetOriginWay()->GetEndNode()->getId() == originNodeId )
    {
      ConvertWayFromBegin2End( currentRoutingSegment, path);
    }

    originNodeId = path.begin()->GetOsmNodeId();
    currentRoutingSegment = currentRoutingSegment->GetPreviousRoutingPoint();
  }

  return path;
}

void COSMRouter::ConvertWayFromBegin2End( tPtrRoutingPoint& routingSegment, tOSMShapePath& path )
{
  const auto& way = *routingSegment->GetOriginWay();

  for ( auto waysegmentIterator = way.GetWaySegments().rbegin(); waysegmentIterator != way.GetWaySegments().rend(); ++waysegmentIterator)
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple, 
                                 waysegmentIterator->getBeginNode(), 
                                 waysegmentIterator->getBeginNode(),
                                 waysegmentIterator->getLength(),
                                 waysegmentIterator->getHeading() +180 ) );
  }
}

void COSMRouter::ConvertWayFromEnd2Begin( tPtrRoutingPoint& routingSegment, tOSMShapePath& path )
{
  const auto& way = *routingSegment->GetOriginWay();

  for( auto waysegmentIterator = way.GetWaySegments().begin(); waysegmentIterator != way.GetWaySegments().end() ; ++waysegmentIterator )
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple,
                                  waysegmentIterator->getEndNode(), 
                                  waysegmentIterator->getEndNode(),
                                  waysegmentIterator->getLength(),
                                  waysegmentIterator->getHeading()));
  }
}


}