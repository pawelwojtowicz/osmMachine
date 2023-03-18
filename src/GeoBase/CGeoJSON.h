#pragma once

constexpr char sTxtType[] = {"type"};
constexpr char sTxtFeatures[] = {"features"};
constexpr char sTxtGeometry[] = {"geometry"};
constexpr char sTxtGeometries[] = {"geometries"};
constexpr char sTxtCoordinates[] = {"coordinates"};
constexpr char sTxtProperties[] = {"properties"};
constexpr char sTxtFeatures[] = {"features"};


//GeoJSON types
constexpr char sTxtType_FeatureCollection[] = {"FeatureCollection"};
constexpr char sTxtType_Feature[] = {"Feature"};
constexpr char sTxtType_Collection[] = {"Collection"};

//geometry types
constexpr char sTxtType_Point[] = {"Point"};
constexpr char sTxtType_MultiPoint[] = {"MultiPoint"};
constexpr char sTxtType_LineString[] = {"LineString"};
constexpr char sTxtType_MultiLineString[]={"MultiLineString"};
constexpr char sTxtType_Polygon[]={"Polygon"};
constexpr char sTxtType_MultiPolygon[]={"MultiPolygon"};
constexpr char sTxtType_GeometryCollection[]={"GeometryCollection"};

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

/**
 * GeoJSON object has a member "type"
 * GeoJSON may have member "bbox"
 * coordinates is [lon , lat]
 * Feature has type,geometry,properties
 * GeoMetryCollection has "geometries"
 * geometry has type and "coordinates"
*/