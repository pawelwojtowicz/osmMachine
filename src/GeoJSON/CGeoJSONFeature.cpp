#include "CGeoJSONFeature.h"

namespace GeoJSON
{
CGeoJSONFeature::CGeoJSONFeature( )
: m_type(tGeoJsonElementType::eInvalid)
{

}

CGeoJSONFeature::CGeoJSONFeature( tGeoJsonElementType type, const tGeometry geometry)
: m_type(type)
, m_geometry(geometry)
{

}


CGeoJSONFeature::CGeoJSONFeature( tGeoJsonElementType type, const tGeometry geometry, const tProperties properties)
: m_type(type)
, m_geometry(geometry)
, m_properties(properties)
{

}

CGeoJSONFeature::~CGeoJSONFeature()
{

}

void CGeoJSONFeature::AddProperty( const std::string& key, const std::string& value)
{
  m_properties[key] = value;
}

const std::string CGeoJSONFeature::GetProperty( const std::string& propertyName) const
{
  const auto propertyIter = m_properties.find( propertyName);
  if ( m_properties.end() != propertyIter)
  {
    return propertyIter->second;
  }

  return {};
}

std::string CGeoJSONFeature::ToJSON() const
{
  return BuildJSONModel().dump();
}

json CGeoJSONFeature::BuildJSONModel() const
{
  json jsonFeatureStructure;
  jsonFeatureStructure[sTxtType] = sTxtType_Feature;
  json jsonGeometryStructure;

  switch( m_type )
  {
  case tGeoJsonElementType::ePoint:
    jsonGeometryStructure[sTxtType] = sTxtType_Point;
    break;
  case tGeoJsonElementType::eMultipoint:
    jsonGeometryStructure[sTxtType] = sTxtType_MultiPoint;
    break;
  case tGeoJsonElementType::eLineString:
    jsonGeometryStructure[sTxtType] = sTxtType_LineString;
    break;
  case tGeoJsonElementType::eMultiLineString:
    jsonGeometryStructure[sTxtType] = sTxtType_MultiLineString;
    break;
  case tGeoJsonElementType::ePolygon:
    jsonGeometryStructure[sTxtType] = sTxtType_Polygon;
    break;
  case tGeoJsonElementType::eMultiPolygon:
    jsonGeometryStructure[sTxtType] = sTxtType_MultiPolygon;
    break;
  default:
    jsonGeometryStructure[sTxtType] = sTxtType_GeometryCollection;
  }

  if ( tGeoJsonElementType::ePoint == m_type)
  {
    json jsonCoordinates( { RAD2DEG(m_geometry.begin()->getLat()), RAD2DEG(m_geometry.begin()->getLon() ) } );
    jsonGeometryStructure[sTxtCoordinates] = jsonCoordinates;
  }
  else
  {
    json jsonCoordinates(json::value_t::array);
    for ( const auto& geoPoint : m_geometry)
    {
      jsonCoordinates.push_back( { RAD2DEG(geoPoint.getLat()), RAD2DEG(geoPoint.getLon() ) } );
    }
    jsonGeometryStructure[sTxtCoordinates] = jsonCoordinates;
  }
  jsonFeatureStructure[sTxtGeometry] = jsonGeometryStructure;

  if ( m_properties.size() )
  {
    json jsonPropertyMap({});
    for ( const auto& propertyPair : m_properties )
    {
      jsonPropertyMap[ propertyPair.first] = propertyPair.second;
    }
    jsonFeatureStructure[sTxtProperties] = jsonPropertyMap;
  }
  return jsonFeatureStructure;
}

bool CGeoJSONFeature::Parse( const std::string& geoJsonString)
{
  json geoJsonStructure = json::parse(geoJsonString); 

  if ( geoJsonStructure.is_discarded() || !geoJsonStructure.contains(sTxtType) || !geoJsonStructure.contains(sTxtGeometry))
  {
    return false;
  }

  const std::string& type = geoJsonStructure[sTxtType];

  if ( type == sTxtType_Feature )
  {
    const auto& geometryStructure = geoJsonStructure[sTxtGeometry];

    if ( !geometryStructure.contains( sTxtType) || !geometryStructure.contains( sTxtCoordinates) )
    {
      return false;
    }

    const std::string geometryType = geometryStructure[sTxtType];

    if ( geometryType == sTxtType_Point )
    {
      m_type = tGeoJsonElementType::ePoint;
    } 
    else if ( geometryType == sTxtType_MultiPoint )
    {
      m_type = tGeoJsonElementType::eMultipoint;
    } 
    else if ( geometryType == sTxtType_LineString )
    {
      m_type = tGeoJsonElementType::eLineString;
    } 
    else if ( geometryType == sTxtType_Polygon )
    {
      m_type = tGeoJsonElementType::ePolygon;
    } 
    else if ( geometryType == sTxtType_MultiPolygon)
    {
      m_type = tGeoJsonElementType::eMultiPolygon;
    } 
    else if ( geometryType == sTxtType_MultiLineString)
    {
      m_type = tGeoJsonElementType::eMultiLineString;
    }
    else
    {
      return false;
    }

    const auto& coordinates = geometryStructure[sTxtCoordinates];
    
    if ( tGeoJsonElementType::ePoint == m_type )
    {
      m_geometry.push_back( GeoBase::CGeoPoint(DEG2RAD(coordinates[0].get<double>()), DEG2RAD(coordinates[1].get<double>())));
    }
    else
    {
      for ( const auto& point : coordinates )
      {
        m_geometry.push_back( GeoBase::CGeoPoint(DEG2RAD(std::stod(point[0].get<std::string>())), DEG2RAD(std::stod(point[1].get<std::string>()))));
      }
    }

    if ( geoJsonStructure.contains(sTxtProperties) )
    {
      const auto& properties = geoJsonStructure[sTxtProperties];
    }

    return true;
  }
  return false;
}


}