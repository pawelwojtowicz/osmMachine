#pragma once
#include "GeoJSONTypes.h"
#include "CGeometry.h"

namespace GeoJSON
{
class CGeoJSONUtils
{
public:
  static tGeometryType GeoJSONElementTypeString2EnumType(  const std::string& geometryTypeString );

  static  std::string GeoJSONElementTypeEnum2String(  const tGeometryType geometryTypeString );

  static tGeometryPtr CreateGeometryFromType( const tGeometryType type );

  static tGeometryPtr CreateGeometryFromStringType( const std::string& type );

};
}