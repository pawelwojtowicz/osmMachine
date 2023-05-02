#pragma once
#include <memory>
#include "GeoJSONTypes.h"
#include "CGeometry.h"

namespace GeoJSON
{
class CGeoJSONFeature
{
public:
  CGeoJSONFeature( );
  CGeoJSONFeature( tGeometryPtr geometry);
  CGeoJSONFeature( tGeometryPtr geometry, const tProperties properties);
  virtual ~CGeoJSONFeature();

  const bool IsValid() const { return (m_geometry && tGeometryType::eInvalid != m_geometry->GetType() ); };

  const tGeometryType getType() const { return m_geometry ? m_geometry->GetType() : tGeometryType::eInvalid; };
  const std::string GetProperty( const std::string& propertyName) const ;

  void AddProperty( const std::string& key, const std::string& value);

  const CGeometry& getGeometry() const { return *m_geometry; };
  
  bool Parse( const std::string& geoJson);
  std::string ToJSON() const;

private:
  virtual bool RebuildFromJSON( const json& jsonTree );
  virtual json BuildJSONTree() const;


private:
  tGeometryPtr m_geometry;

  tProperties m_properties;
};
}