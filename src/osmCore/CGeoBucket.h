#pragma once
#include <map>
#include <list>
#include <CGeoIndex.h>

namespace osmMachine
{

template < class INDEX_TYPE, class OSM_ENTITY >
class CGeoBucket
{
public:
  typedef std::list<OSM_ENTITY> tEntityList ;
private:
  typedef std::map<INDEX_TYPE,tEntityList> tGeoIndex2EntityMap ;

public:

  CGeoBucket()
  : m_emptyList()
  {

  }

  const CGeoBucket<INDEX_TYPE, OSM_ENTITY>::tEntityList& getInArea( const INDEX_TYPE geoIndex )
  {
    const auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
    if ( m_geoIndex2EntityBucket.end() != bucketIter )
    {
      return bucketIter->second;
    }
    return m_emptyList;
  }

  void addEntityToArea( const INDEX_TYPE geoIndex, OSM_ENTITY osmEntity )
  {
    auto bucketIter = m_geoIndex2EntityBucket.find( geoIndex);
    if ( m_geoIndex2EntityBucket.end() == bucketIter )
    {
      auto insertResult = m_geoIndex2EntityBucket.insert( typename CGeoBucket<INDEX_TYPE, OSM_ENTITY>::tGeoIndex2EntityMap::value_type( geoIndex, m_emptyList) ); 
      bucketIter = insertResult.first;
    }

    bucketIter->second.push_back( osmEntity );
  }
private:
  typename CGeoBucket<INDEX_TYPE, OSM_ENTITY>::tGeoIndex2EntityMap m_geoIndex2EntityBucket;

  typename CGeoBucket<INDEX_TYPE, OSM_ENTITY>::tEntityList m_emptyList;



};
}