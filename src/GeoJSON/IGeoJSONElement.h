#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GeoJSON
{
class IGeoJSONElement
{
public:
  virtual bool RebuildFromJSON( const json& jsonTree ) = 0;

  virtual json BuildJSONTree() = 0; 
};
}