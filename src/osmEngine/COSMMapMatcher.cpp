#include "COSMMapMatcher.h"
#include <GeoBase/GeoUtils.h>
#include <iostream>

namespace osmMachine
{

COSMMapMatcher::COSMMapMatcher( const OSMRoutingNetwork& routingNetwork )
: m_routingNetwork( routingNetwork)
, m_neighbourhoodSize( 1 )
, m_recomendationSize(1)
, m_mapMatchingTolerance( std::numeric_limits<double>::max() )
{
}

COSMMapMatcher::~COSMMapMatcher()
{

}

void COSMMapMatcher::Initialize ( const int neighbourhoodSize, 
                                  const int mapMatcherRecomendationSize, 
                                  const double mapMatchingTolerance )
{
  m_neighbourhoodSize = neighbourhoodSize;
  m_recomendationSize = mapMatcherRecomendationSize;
  if ( -1 == mapMatchingTolerance )
  {
    m_mapMatchingTolerance = std::numeric_limits<double>::max();
  }
}

tMapMatching COSMMapMatcher::FindOSMPosition( const GeoBase::CGeoPoint& point)
{
  const auto wayElementsInArea = m_routingNetwork.wayGeoBuckets.getAllAround(point, m_neighbourhoodSize );

  tMapMatching osmMapMatchings;

  for( const auto& way : wayElementsInArea)
  {

    if ( way->IsUsed() )
    {
      const auto& segments = way->GetWaySegments();
      int segmentCount = segments.size();
      double distanceOnTheWay = 0;
      

      for ( int index = 0 ; index < segmentCount ; ++index)
      {
        GeoBase::CGeoPoint projection;
        double distance = std::numeric_limits<double>::max() ;
        GeoBase::GeoUtils::ProjectPoint2Shape( point, 
                                               *segments[index].getBeginNode(),
                                               *segments[index].getEndNode(), 
                                               projection,
                                               distance );
        if ( distance < m_mapMatchingTolerance )
        {
          osmMapMatchings.insert( COSMPosition(
            way,
            index,
            distanceOnTheWay + GeoBase::GeoUtils::Point2PointDistance(*(segments[index].getBeginNode()), projection ),
            distance,
            point,
            projection
          ));

          if ( osmMapMatchings.size() > m_recomendationSize )
          {
            osmMapMatchings.erase( --osmMapMatchings.end() );
          }
        }

        distanceOnTheWay += segments[index].getLength();
      }
    }
  }

  return osmMapMatchings;
}
}