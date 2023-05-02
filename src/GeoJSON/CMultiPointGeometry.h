#pragma once
#include "CGeometry.h"

namespace GeoJSON
{
class CMultiPointGeometry : public CGeometry
{
public:
  CMultiPointGeometry();
  CMultiPointGeometry( const tGeometryType type, const tGeometry& geometry );
  virtual ~CMultiPointGeometry();

  virtual const tGeometry& GetPoints() const override;

public:
  virtual bool RebuildFromJSON( const json& jsonTree ) override;
  virtual json BuildJSONTree() override;

private:
  tGeometry m_geometry;
};
}