#pragma once
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <string>
#include <GeoBase/CGeoPoint.h>

using json = nlohmann::json;

namespace GeoJSON
{
enum class tGeoJsonType {
  eFeatureCollection,
  eGeometryCollection,
  eFeature,
  eCollection
};

enum class tGeometryType 
{
eInvalid,
ePoint,
eMultipoint,
eLineString,
eMultiLineString,
ePolygon,
eMultiPolygon,
};

constexpr char sTxtType[] = {"type"};
constexpr char sTxtFeatures[] = {"features"};
constexpr char sTxtGeometry[] = {"geometry"};
constexpr char sTxtGeometries[] = {"geometries"};
constexpr char sTxtCoordinates[] = {"coordinates"};
constexpr char sTxtProperties[] = {"properties"};


//GeoJSON types
constexpr char sTxtType_FeatureCollection[] = {"FeatureCollection"};
constexpr char sTxtType_Feature[] = {"Feature"};
constexpr char sTxtType_Collection[] = {"Collection"};



constexpr char sTxtType_Point[] = {"Point"};
constexpr char sTxtType_MultiPoint[] = {"MultiPoint"};
constexpr char sTxtType_LineString[] = {"LineString"};
constexpr char sTxtType_MultiLineString[]={"MultiLineString"};
constexpr char sTxtType_Polygon[]={"Polygon"};
constexpr char sTxtType_MultiPolygon[]={"MultiPolygon"};
constexpr char sTxtType_GeometryCollection[]={"GeometryCollection"};


using tProperties = std::map<std::string, std::string>;
using tGeometry = std::vector<GeoBase::CGeoPoint>;
using tMultiGeometry = std::vector<tGeometry>;
}