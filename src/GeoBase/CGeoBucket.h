#pragma once
#include <map>
#include <set>
#include "CGeoPoint.h"
#include "CTileUtils.h"

namespace osmMachine
{

template <class OSM_ENTITY >
class CGeoBucket
{
public:
  using tEntitySet = std::set<OSM_ENTITY>  ;
private:
  using tGeoIndex2EntityMap = std::map<uint64_t,tEntitySet>  ;

public:

  struct tGeoBucketStats
  {
    int zoomLevel;
    int min;
    int max;
    int avrg;
    int bucketCount;
  };

  CGeoBucket()
  : m_zoomLevel(0)
  , m_rowLength(1)
  {

  }

  bool Initialize( int zoomLevel )
  {
    m_zoomLevel = zoomLevel;
    m_rowLength <<= zoomLevel;

    return (m_zoomLevel = zoomLevel);
  }

  CGeoBucket<OSM_ENTITY>::tEntitySet getAllAround( const CGeoPoint& point, int radius = 0 ) const
  {
    uint64_t xIndex = CTileUtils::gpsLon2TileX(RAD2DEG(point.getLon()), m_zoomLevel);
    uint64_t yIndex = CTileUtils::gpsLat2TileY(RAD2DEG(point.getLat()), m_zoomLevel);

    uint64_t zero = 0;

    uint64_t xBegining( std::max( zero , xIndex - radius ));
    uint64_t xEnd(std::min(m_rowLength-1, xIndex + radius  ));
    uint64_t yBegining( std::max( zero,yIndex- radius));
    uint64_t yEnd( std::min( m_rowLength-1, yIndex+radius));

    CGeoBucket<OSM_ENTITY>::tEntitySet entitiesInArea;

    for ( uint64_t x = xBegining ; x<= xEnd ; ++x )
    {
      for ( uint64_t y = yBegining ; y<= yEnd ; ++y)
      {
        uint64_t geoIndex = ( 0xffffffff & x)<<32 | (0xffffffff & y);
        const auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
        if ( m_geoIndex2EntityBucket.end() != bucketIter )
        {
          entitiesInArea.insert( bucketIter->second.begin(), bucketIter->second.end());
        }
      }
    }
   
    return entitiesInArea;
  }

  void addEntityToArea( const CGeoPoint& point, OSM_ENTITY osmEntity )
  {
    uint64_t xIndex = CTileUtils::gpsLon2TileX( RAD2DEG(point.getLon()), m_zoomLevel );
    uint64_t yIndex = CTileUtils::gpsLat2TileY( RAD2DEG(point.getLat()), m_zoomLevel );

    uint64_t geoIndex = ( 0xffffff & xIndex)<<32 | (0xffffffff & yIndex);

    auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
    if ( m_geoIndex2EntityBucket.end() == bucketIter )
    {
      auto insertResult = m_geoIndex2EntityBucket.insert( typename CGeoBucket<OSM_ENTITY>::tGeoIndex2EntityMap::value_type( geoIndex, {} ) ); 
      bucketIter = insertResult.first;
    }

    bucketIter->second.insert( osmEntity );
  }

  tGeoBucketStats Stats()
  {
    tGeoBucketStats geoBucketStats;
    geoBucketStats.zoomLevel = m_zoomLevel;
    geoBucketStats.min = 999999999;
    geoBucketStats.max = 0;
    geoBucketStats.bucketCount = m_geoIndex2EntityBucket.size();
    geoBucketStats.avrg = 0;

    for ( const auto& indexWayPair : m_geoIndex2EntityBucket )
    {
      int count = indexWayPair.second.size();
      geoBucketStats.avrg += count;
      geoBucketStats.min = std::min(geoBucketStats.min, count);
      geoBucketStats.max = std::max(geoBucketStats.max, count);
    }
    geoBucketStats.avrg = geoBucketStats.avrg/geoBucketStats.bucketCount;

    return geoBucketStats;
  }

private:
  int m_zoomLevel;

  uint64_t m_rowLength;

  typename CGeoBucket<OSM_ENTITY>::tGeoIndex2EntityMap m_geoIndex2EntityBucket;

};
}