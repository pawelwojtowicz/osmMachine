#pragma once
#include "GeoJSONTypes.h"

namespace GeoJSON
{
class CGeoJSONUtils
{
public:
  static tGeometryType GeoJSONElementTypeString2EnumType(  const std::string& geometryTypeString );

  static  std::string GeoJSONElementTypeEnum2String(  const tGeometryType geometryTypeString );

};
}