#pragma once
#include "GeoJSONTypes.h"

namespace GeoJSON
{
class CGeoJSONFeature
{
public:
  CGeoJSONFeature( tGeoJsonElementType type, const tGeometry geometry, const tProperties properties);
  virtual ~CGeoJSONFeature();

  void AddProperty( const std::string& key, const std::string& value);

  const tGeoJsonElementType getFeatureType() const { return m_type; };
  const tGeometry& getGeometry() const {return m_geometry;};
  const std::string GetProperty( const std::string& propertyName) const ;

  std::string ToJSON() const;

private:
  json BuildJSONModel() const;

private:
  tGeoJsonElementType m_type;

  tGeometry m_geometry;

  tProperties m_properties;
};
}