#include "CGeoJSONFeature.h"
#include "CGeoJSONUtils.h"
#include <iostream>

namespace GeoJSON
{
CGeoJSONFeature::CGeoJSONFeature()
{

}

CGeoJSONFeature::CGeoJSONFeature( tGeometryPtr geometry )
{
  m_geometry = geometry;
}

CGeoJSONFeature::CGeoJSONFeature( tGeometryPtr geometry,const tProperties properties)
: m_properties(properties)
{
  m_geometry = geometry;
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
  return BuildJSONTree().dump();
}

json CGeoJSONFeature::BuildJSONTree() const
{
  json jsonFeatureStructure;
  jsonFeatureStructure[sTxtType] = sTxtType_Feature;
  jsonFeatureStructure[sTxtGeometry] = m_geometry->BuildJSONTree() ;

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

bool CGeoJSONFeature::Parse( const std::string& geoJsonString )
{
  json geoJsonStructure = json::parse(geoJsonString);

  if (!geoJsonStructure.is_discarded())
  {
    return RebuildFromJSON( geoJsonStructure );
  }
  return false;
}

bool CGeoJSONFeature::RebuildFromJSON( const json& featureJsonStructure )
{
    if ( !featureJsonStructure.contains(sTxtType) || !featureJsonStructure.contains(sTxtGeometry))
  {
    return false;
  }

  const std::string& type = featureJsonStructure[sTxtType];

  if ( type == sTxtType_Feature )
  {
    const auto& geometryStructure = featureJsonStructure[sTxtGeometry];

    if ( !geometryStructure.contains( sTxtType) )
    {
      return false;
    }

    const std::string geometryType = geometryStructure[sTxtType];

    m_geometry = CGeoJSONUtils::CreateGeometryFromStringType(geometryType);
    if (!m_geometry)
    {
      return false;
    }

    m_geometry->RebuildFromJSON( geometryStructure );

    if ( featureJsonStructure.contains( sTxtProperties ) )
    {
      const auto& properties = featureJsonStructure[sTxtProperties];

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