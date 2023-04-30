#pragma once

namespace Utils
{
using tGeoJsonType = enum {
  eFeatureCollection,
  eFeature,
  eCollection
};

using tGeoJsonElementType = enum 
{
ePoint,
eMultipoint,
eLineString,
eMultiLineString,
ePolygon,
eMultiPolygon,
eGeometryCollection
};

}