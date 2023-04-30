#include "CGeoJSONFeature.h"

namespace GeoJSON
{
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

  json jsonCoordinates;
  for ( const auto& geoPoint : m_geometry)
  {
    jsonCoordinates.push_back( { geoPoint.getLat(), geoPoint.getLon() } );
  }
  jsonGeometryStructure[sTxtCoordinates] = jsonCoordinates;
  jsonFeatureStructure[sTxtGeometry] = jsonGeometryStructure;

  json jsonPropertyMap;
  for ( const auto& propertyPair : m_properties )
  {
    jsonPropertyMap[ propertyPair.first] = propertyPair.second;
  }
  jsonFeatureStructure[sTxtProperties] = jsonPropertyMap;

  return jsonFeatureStructure;
}

}