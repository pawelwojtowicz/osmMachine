#include "CGeoJSON.h"

namespace Utils
{
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



CGeoJSON::CGeoJSON( tGeoJsonType geoJsonType)
: m_geoJsonType(geoJsonType)
{

}

CGeoJSON::~CGeoJSON()
{

}

}