#pragma once
#include "GeoJSONTypes.h"

namespace GeoJSON
{
/**
 * GeoJSON object has a member "type"
 * GeoJSON may have member "bbox"
 * coordinates is [lon , lat]
 * Feature has type,geometry,properties
 * GeoMetryCollection has "geometries"
 * geometry has type and "coordinates"
*/

class CGeoJSON
{
public:
  CGeoJSON( tGeoJsonType geoJsonType = tGeoJsonType::eFeatureCollection  );
  virtual ~CGeoJSON();
  
private:
  tGeoJsonType m_geoJsonType;
};

}