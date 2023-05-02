#pragma once
#include "CGeometry.h"

namespace GeoJSON
{
class CMultiShapeGeometry : public CGeometry
{
public:
  CMultiShapeGeometry();
  CMultiShapeGeometry( const tGeometryType type, const tMultiGeometry& geometry );
  virtual ~CMultiShapeGeometry();

  virtual const tMultiGeometry& GetMultiGeometry() const override;

public:
  virtual bool RebuildFromJSON( const json& jsonTree ) override;
  virtual json BuildJSONTree() override;

private:
  tMultiGeometry m_geometry;
};
}