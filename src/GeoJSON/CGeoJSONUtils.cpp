#include "CGeoJSONUtils.h"

namespace GeoJSON
{

tGeoJsonElementType CGeoJSONUtils::GeoJSONElementTypeString2EnumType(  const std::string& geometryTypeString )
{
  tGeoJsonElementType type( tGeoJsonElementType::eInvalid );
  if ( geometryTypeString == sTxtType_Point )
  {
    type = tGeoJsonElementType::ePoint;
  } 
  else if ( geometryTypeString == sTxtType_MultiPoint )
  {
    type = tGeoJsonElementType::eMultipoint;
  } 
  else if ( geometryTypeString == sTxtType_LineString )
  {
    type = tGeoJsonElementType::eLineString;
  } 
  else if ( geometryTypeString == sTxtType_Polygon )
  {
    type = tGeoJsonElementType::ePolygon;
  } 
  else if ( geometryTypeString == sTxtType_MultiPolygon)
  {
    type = tGeoJsonElementType::eMultiPolygon;
  } 
  else if ( geometryTypeString == sTxtType_MultiLineString)
  {
    type = tGeoJsonElementType::eMultiLineString;
  }

  return type;
}

std::string CGeoJSONUtils::GeoJSONElementTypeEnum2String(  const tGeoJsonElementType geometryType )
{
  std::string stringMapping;

  switch( geometryType )
  {
  case tGeoJsonElementType::ePoint:
    stringMapping = sTxtType_Point;
    break;
  case tGeoJsonElementType::eMultipoint:
    stringMapping = sTxtType_MultiPoint;
    break;
  case tGeoJsonElementType::eLineString:
    stringMapping = sTxtType_LineString;
    break;
  case tGeoJsonElementType::eMultiLineString:
    stringMapping = sTxtType_MultiLineString;
    break;
  case tGeoJsonElementType::ePolygon:
    stringMapping = sTxtType_Polygon;
    break;
  case tGeoJsonElementType::eMultiPolygon:
    stringMapping = sTxtType_MultiPolygon;
    break;
  case tGeoJsonElementType::eGeometryCollection:
    stringMapping = sTxtType_GeometryCollection;
    break;
  default:;
  }

  return stringMapping;
}

}