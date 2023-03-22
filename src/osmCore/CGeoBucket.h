#pragma once
#include <map>
#include <list>
#include <CGeoPoint.h>
#include <CTileUtils.h>

namespace osmMachine
{

template < class OSM_ENTITY >
class CGeoBucket
{
public:
  typedef std::list<OSM_ENTITY> tEntityList ;
private:
  typedef std::map<uint32_t,tEntityList> tGeoIndex2EntityMap ;

public:

  CGeoBucket()
  : m_zoomLevel(0)
  {

  }

  bool Initialize( double latBegin, double lonBegin, double latEnd, double lonEnd, int zoomLevel )
  {
    bool isInitialized(false);
    m_zoomLevel = zoomLevel;

    if ( latBegin > latEnd && lonBegin > lonEnd )
    {
      m_xMin = CTileUtils::gpsLon2TileX( minLon ,m_zoomLevel );
      m_yMin = CTileUtils::gpsLat2TileY( minLat ,m_zoomLevel );
      m_dx = CTileUtils::gpsLon2TileX( maxLon ,m_zoomLevel ) - m_xMin;
      m_dy = CTileUtils::gpsLat2TileY( maxLat, m_zoomLevel ) - m_yMin;

      isInitialized = (dx > 0 & dy > 0);
    }

    return isInitialized;
  }

  const CGeoBucket<OSM_ENTITY>::tEntityList& getAllAround( const CGeoPoint& point, int radius = 2 )
  {
    uint32_t xIndex = CTileUtils::gpsLon2TileX(point.getLon(), m_zoomLevel);
    uint32_t yIndex = CTileUtils::gpsLat2TileY(point.getLat(), m_zoomLevel);

    uint32_t geoIndex = ( 0xffff & xIndex)<<16 | (0xffff & yIndex);

    const auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
    if ( m_geoIndex2EntityBucket.end() != bucketIter )
    {
      return bucketIter->second;
    }
    return {};
  }

  void addEntityToArea( const CGeoPoint& point, OSM_ENTITY osmEntity )
  {
    uint32_t xIndex = CTileUtils::gpsLon2TileX( point.getLon(), m_zoomLevel );
    uint32_t yIndex = CTileUtils::gpsLat2TileY( point.getLat(), m_zoomLevel );

    uint32_t geoIndex = ( 0xffff & xIndex)<<16 | (0xffff & yIndex);

    auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
    if ( m_geoIndex2EntityBucket.end() == bucketIter )
    {
      auto insertResult = m_geoIndex2EntityBucket.insert( typename CGeoBucket<INDEX_TYPE, OSM_ENTITY>::tGeoIndex2EntityMap::value_type( geoIndex, m_emptyList) ); 
      bucketIter = insertResult.first;
    }

    bucketIter->second.push_back( osmEntity );
  }
private:
  int m_zoomLevel;

  uint32_t m_xMin;
  uint32_t m_yMin;
  uint32_t m_dx;
  uint32_t m_dy;

  typename CGeoBucket<uint32_t , OSM_ENTITY>::tGeoIndex2EntityMap m_geoIndex2EntityBucket;

};
}