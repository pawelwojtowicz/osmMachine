#include "COSMMapMatcher.h"
#include <GeoUtils.h>

namespace osmMachine
{

COSMMapMatcher::COSMMapMatcher( const OSMRoutingNetwork& routingNetwork )
: m_routingNetwork( routingNetwork)
, m_neighbourhoodSize( 1 )
{
}

COSMMapMatcher::~COSMMapMatcher()
{

}

void COSMMapMatcher::Initialize ( const int neighbourhoodSize )
{
  m_neighbourhoodSize = neighbourhoodSize;
}

COSMPosition COSMMapMatcher::FindOSMPosition( const CGeoPoint& point)
{
  const auto wayElementsInArea = m_routingNetwork.wayGeoBuckets.getAllAround(point, m_neighbourhoodSize );

  tWayShPtr bestMatchingWay;
  double bestDistance = std::numeric_limits<double>::max();
  CGeoPoint mapMatchedGeoNode;
  int bestMatchingSegmentIdx = 0;

  for( const auto& way : wayElementsInArea)
  {
    if ( way->IsUsed() )
    {
      const auto& segments = way->GetWaySegments();
      int segmentCount = segments.size();
      

      for ( int index = 0 ; index < segmentCount ; ++index)
      {
        CGeoPoint projection;
        double distance = std::numeric_limits<double>::max() ;
        GeoUtils::ProjectPoint2Shape( point, 
                                      *segments[index].getBeginNode(),
                                      *segments[index].getEndNode(), 
                                      projection,
                                      distance );
        if ( distance < bestDistance )
        {
          bestMatchingWay = way;
          mapMatchedGeoNode = projection;
          bestDistance = distance;
          bestMatchingSegmentIdx = index;
        }
      }
    }
  }

  return COSMPosition( bestMatchingWay->GetId() , bestMatchingSegmentIdx, bestDistance, point, mapMatchedGeoNode);
}
}