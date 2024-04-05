#include "CRoutePathBuilder.h"
#include <GeoBase/GeoUtils.h>
#include <iostream>

namespace osmMachine
{

void CRoutePathBuilder::ConvertEntryToBegin( const COSMPosition& originOsmPosition, tOSMShapePath& path)
{
  std::cout << "CRoutePathBuilder::ConvertEntryToBegin" << std::endl;
  const auto& waySegments = originOsmPosition.GetWay()->GetWaySegments();
  
  for ( int i = 0 ; i < originOsmPosition.GetWaySegmentIndex() ; ++i )
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple,
                     waySegments[i].getEndNode(), 
                     waySegments[i].getEndNode(),
                     originOsmPosition.GetWay()->GetId(),
                     waySegments[i].getLength(), 
                     GeoBase::GeoUtils::OpositeDirection(waySegments[i].getHeading())));
  }

  double length = waySegments[originOsmPosition.GetWaySegmentIndex()].getLength() - originOsmPosition.GetDistanceOnSegment(); 
  path.push_front(  CShapePoint( CShapePoint::tViaPointType::ePOI,
                    originOsmPosition.GetRawPosition(), 
                    originOsmPosition.GetPositionSnapped2OSM(),
                    originOsmPosition.GetWay()->GetId(),
                    length, 
                    GeoBase::GeoUtils::OpositeDirection(waySegments[originOsmPosition.GetWaySegmentIndex()].getHeading())));
}

void CRoutePathBuilder::ConvertEntryToEnd( const COSMPosition& originOsmPosition , tOSMShapePath& path )
{
  const auto& waySegments = originOsmPosition.GetWay()->GetWaySegments();
  const int lastSegment = waySegments.size() - 1;

  for ( int i = lastSegment ; i > originOsmPosition.GetWaySegmentIndex() ; --i )
  {

    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple,
                     waySegments[i].getBeginNode(), 
                     waySegments[i].getBeginNode() ,
                     originOsmPosition.GetWay()->GetId(),
                     waySegments[i].getLength(), 
                     waySegments[i].getHeading()));

  }

  path.push_front(  CShapePoint( CShapePoint::tViaPointType::ePOI,
                  originOsmPosition.GetRawPosition(), 
                  originOsmPosition.GetPositionSnapped2OSM() ,
                  originOsmPosition.GetWay()->GetId(),
                  originOsmPosition.GetDistanceOnSegment(), 
                  waySegments[originOsmPosition.GetWaySegmentIndex()].getHeading()));
}


void CRoutePathBuilder::ConvertWayFromBegin2End( tPtrRoutingPoint& routingSegment, tOSMShapePath& path )
{
  const auto& way = *routingSegment->GetOriginWay();

  for ( auto waysegmentIterator = way.GetWaySegments().rbegin(); waysegmentIterator != way.GetWaySegments().rend(); ++waysegmentIterator)
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple, 
                                 waysegmentIterator->getBeginNode(), 
                                 waysegmentIterator->getBeginNode(),
                                 way.GetId(),
                                 waysegmentIterator->getLength(),
                                 waysegmentIterator->getHeading() ) );
  }
}

void CRoutePathBuilder::ConvertWayFromEnd2Begin( tPtrRoutingPoint& routingSegment, tOSMShapePath& path )
{
  const auto& way = *routingSegment->GetOriginWay();

  for( auto waysegmentIterator = way.GetWaySegments().begin(); waysegmentIterator != way.GetWaySegments().end() ; ++waysegmentIterator )
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eSimple,
                                  waysegmentIterator->getEndNode(), 
                                  waysegmentIterator->getEndNode(),
                                  way.GetId(),
                                  waysegmentIterator->getLength(),
                                  GeoBase::GeoUtils::OpositeDirection(waysegmentIterator->getHeading())));
  }
}

void CRoutePathBuilder::ConvertExitFromBegin( const COSMPosition& destinationOsmPosition , tOSMShapePath& path )
{
  const auto& waySegments = destinationOsmPosition.GetWay()->GetWaySegments();

  for ( int i = 0 ; i < destinationOsmPosition.GetWaySegmentIndex() ; ++i )
  {
    path.push_back( CShapePoint( CShapePoint::tViaPointType::eSimple,
                                  waySegments[i].getBeginNode(), 
                                  waySegments[i].getBeginNode(),
                                  destinationOsmPosition.GetWay()->GetId(),
                                  waySegments[i].getLength(),
                                  waySegments[i].getHeading()));
  }

  path.push_back( CShapePoint( CShapePoint::tViaPointType::eSimple,
                                waySegments[destinationOsmPosition.GetWaySegmentIndex()].getBeginNode(), 
                                waySegments[destinationOsmPosition.GetWaySegmentIndex()].getBeginNode(),
                                destinationOsmPosition.GetWay()->GetId(),
                                destinationOsmPosition.GetDistanceOnSegment(),
                                waySegments[destinationOsmPosition.GetWaySegmentIndex()].getHeading()));

}

void CRoutePathBuilder::ConvertExitFromEnd( const COSMPosition& destinationOsmPosition ,tOSMShapePath& path )
{
  const auto& waySegments = destinationOsmPosition.GetWay()->GetWaySegments();
  const int lastSegment = waySegments.size() - 1;

  for ( int i = lastSegment ; i > destinationOsmPosition.GetWaySegmentIndex() ; ++i )
  {
    path.push_back( CShapePoint( CShapePoint( CShapePoint::tViaPointType::eSimple,
                            waySegments[i].getEndNode(),
                            waySegments[i].getEndNode(),
                            destinationOsmPosition.GetWay()->GetId(),
                            waySegments[i].getLength(),
                            GeoBase::GeoUtils::OpositeDirection(waySegments[i].getHeading()))));
  }

  path.push_back( CShapePoint( CShapePoint( CShapePoint::tViaPointType::eSimple,
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getEndNode(),
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getEndNode(),
                          destinationOsmPosition.GetWay()->GetId(),
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getLength() - destinationOsmPosition.GetDistanceOnSegment(),
                          GeoBase::GeoUtils::OpositeDirection(waySegments[destinationOsmPosition.GetWaySegmentIndex()].getHeading()))));
}

tOSMShapePath CRoutePathBuilder::BuildSolutionPath( tPtrRoutingPoint finalGeoPoint, const COSMPosition& destination )
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
                                 destination.GetWay()->GetId(),
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
                                 destination.GetWay()->GetId(),
                                 0,
                                 0 ));
  }

  while( currentRoutingSegment && currentRoutingSegment->GetOriginWay() )
  {
    if ( currentRoutingSegment->GetOriginWay()->GetBeginNode()->getId() == originNodeId )
    {
      CRoutePathBuilder::ConvertWayFromEnd2Begin( currentRoutingSegment, path);
    }

    if ( currentRoutingSegment->GetOriginWay()->GetEndNode()->getId() == originNodeId )
    {
      CRoutePathBuilder::ConvertWayFromBegin2End( currentRoutingSegment, path);
    }

    originNodeId = path.begin()->GetOsmNodeId();
    currentRoutingSegment = currentRoutingSegment->GetPreviousRoutingPoint();
  }

  return path;
}

}