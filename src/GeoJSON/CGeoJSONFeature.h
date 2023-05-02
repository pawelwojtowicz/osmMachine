#pragma once
#include "GeoJSONTypes.h"

namespace GeoJSON
{
class CGeoJSONFeature
{
public:
  CGeoJSONFeature( );
  CGeoJSONFeature( tGeometryType type, const tGeometry geometry);
  CGeoJSONFeature( tGeometryType type, const tGeometry geometry, const tProperties properties);
  virtual ~CGeoJSONFeature();

  const bool IsValid() const { return (tGeometryType::eInvalid != m_type ); };
  const tGeometryType getType() const { return m_type; };
  const std::string GetProperty( const std::string& propertyName) const ;

  void AddProperty( const std::string& key, const std::string& value);



  const tGeometry& getGeometry() const {return m_geometry;};
  
  bool Parse( const std::string& geoJson);
  std::string ToJSON() const;

private:
  json BuildJSONModel() const;

private:
  tGeometryType m_type;

  tGeometry m_geometry;

  tProperties m_properties;
};
}