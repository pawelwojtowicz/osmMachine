#include "CRoutePathBuilder.h"
#include <iostream>

namespace osmMachine
{

void CRoutePathBuilder::ConvertEntryToBegin( const COSMPosition& originOsmPosition, tOSMShapePath& path)
{
  std::cout << "CRoutePathBuilder::ConvertEntryToBegin" << std::endl;
  const auto& waySegments = originOsmPosition.GetWay()->GetWaySegments();
  
  for ( int i = 0 ; i < originOsmPosition.GetWaySegmentIndex() ; ++i )
  {
    path.push_front( CShapePoint( CShapePoint::tViaPointType::eEntry,
                     waySegments[i].getEndNode(), waySegments[i].getEndNode() , waySegments[i].getLength(), waySegments[i].getHeading() + 180));
  }

  double length = waySegments[originOsmPosition.GetWaySegmentIndex()].getLength() - originOsmPosition.GetDistanceOnSegment(); 
  path.push_front(  CShapePoint( CShapePoint::tViaPointType::ePOI,
                    originOsmPosition.GetRawPosition(), 
                    originOsmPosition.GetPositionSnapped2OSM() , 
                    length, 
                    waySegments[originOsmPosition.GetWaySegmentIndex()].getHeading() + 180));
}

void CRoutePathBuilder::ConvertEntryToEnd( const COSMPosition& originOsmPosition , tOSMShapePath& path )
{
  std::cout << "CRoutePathBuilder::ConvertEntryToEnd" << std::endl;

  const auto& waySegments = originOsmPosition.GetWay()->GetWaySegments();
  const int lastSegment = waySegments.size() - 1;

  std::cout << "lastSegment = " << lastSegment << " index= " << originOsmPosition.GetWaySegmentIndex() << std::endl;

  for ( int i = lastSegment ; i > originOsmPosition.GetWaySegmentIndex() ; --i )
  {

    path.push_front( CShapePoint( CShapePoint::tViaPointType::eEntry,
                     waySegments[i].getBeginNode(), waySegments[i].getBeginNode() , waySegments[i].getLength(), waySegments[i].getHeading() + 180));

  }

  path.push_front(  CShapePoint( CShapePoint::tViaPointType::ePOI,
                  originOsmPosition.GetRawPosition(), 
                  originOsmPosition.GetPositionSnapped2OSM() , 
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
                                 waysegmentIterator->getLength(),
                                 waysegmentIterator->getHeading() +180 ) );
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
                                  waysegmentIterator->getLength(),
                                  waysegmentIterator->getHeading()));
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
                                  waySegments[i].getLength(),
                                  waySegments[i].getHeading()));
  }

  path.push_back( CShapePoint( CShapePoint::tViaPointType::eSimple,
                                waySegments[destinationOsmPosition.GetWaySegmentIndex()].getBeginNode(), 
                                waySegments[destinationOsmPosition.GetWaySegmentIndex()].getBeginNode(),
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
                            waySegments[i].getLength(),
                            waySegments[i].getHeading() - 180)));
  }

  path.push_back( CShapePoint( CShapePoint( CShapePoint::tViaPointType::eSimple,
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getEndNode(),
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getEndNode(),
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getLength() - destinationOsmPosition.GetDistanceOnSegment(),
                          waySegments[destinationOsmPosition.GetWaySegmentIndex()].getHeading() - 180)));


}



}