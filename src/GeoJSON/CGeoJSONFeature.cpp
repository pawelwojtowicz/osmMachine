#include "CGeoJSONFeature.h"
#include "CGeoJSONUtils.h"
#include <iostream>

namespace GeoJSON
{
CGeoJSONFeature::CGeoJSONFeature( )
: m_type(tGeometryType::eInvalid)
{

}

CGeoJSONFeature::CGeoJSONFeature( tGeometryType type, const tGeometry geometry)
: m_type(type)
, m_geometry(geometry)
{

}

CGeoJSONFeature::CGeoJSONFeature( tGeometryType type, const tGeometry geometry, const tProperties properties)
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

  jsonGeometryStructure[sTxtType] = CGeoJSONUtils::GeoJSONElementTypeEnum2String(m_type);

  if ( tGeometryType::ePoint == m_type)
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

    m_type = CGeoJSONUtils::GeoJSONElementTypeString2EnumType( geometryType );

    if ( tGeometryType::eInvalid == m_type )
    {
      return false;
    }

    const auto& coordinates = geometryStructure[sTxtCoordinates];
    
    if ( tGeometryType::ePoint == m_type )
    {
      m_geometry.push_back( GeoBase::CGeoPoint(DEG2RAD(coordinates[0].get<double>()), DEG2RAD(coordinates[1].get<double>())));
    }
    else
    {
      for ( const auto& point : coordinates )
      {
        m_geometry.push_back( GeoBase::CGeoPoint(DEG2RAD(point[0].get<double>()), DEG2RAD(point[1].get<double>())));
      }
    }

    if ( geoJsonStructure.contains( sTxtProperties ) )
    {
      const auto& properties = geoJsonStructure[sTxtProperties];

      for ( auto property : properties.items() )
      {
        m_properties[property.key()] = property.value();
      }
    }
    return true;
  }
  return false;
}


}