#include "CGeoJSONUtils.h"

namespace GeoJSON
{

tGeometryType CGeoJSONUtils::GeoJSONElementTypeString2EnumType(  const std::string& geometryTypeString )
{
  tGeometryType type( tGeometryType::eInvalid );
  if ( geometryTypeString == sTxtType_Point )
  {
    type = tGeometryType::ePoint;
  } 
  else if ( geometryTypeString == sTxtType_MultiPoint )
  {
    type = tGeometryType::eMultipoint;
  } 
  else if ( geometryTypeString == sTxtType_LineString )
  {
    type = tGeometryType::eLineString;
  } 
  else if ( geometryTypeString == sTxtType_Polygon )
  {
    type = tGeometryType::ePolygon;
  } 
  else if ( geometryTypeString == sTxtType_MultiPolygon)
  {
    type = tGeometryType::eMultiPolygon;
  } 
  else if ( geometryTypeString == sTxtType_MultiLineString)
  {
    type = tGeometryType::eMultiLineString;
  }

  return type;
}

std::string CGeoJSONUtils::GeoJSONElementTypeEnum2String(  const tGeometryType geometryType )
{
  std::string stringMapping;

  switch( geometryType )
  {
  case tGeometryType::ePoint:
    stringMapping = sTxtType_Point;
    break;
  case tGeometryType::eMultipoint:
    stringMapping = sTxtType_MultiPoint;
    break;
  case tGeometryType::eLineString:
    stringMapping = sTxtType_LineString;
    break;
  case tGeometryType::eMultiLineString:
    stringMapping = sTxtType_MultiLineString;
    break;
  case tGeometryType::ePolygon:
    stringMapping = sTxtType_Polygon;
    break;
  case tGeometryType::eMultiPolygon:
    stringMapping = sTxtType_MultiPolygon;
    break;
  default:;
  }

  return stringMapping;
}

}