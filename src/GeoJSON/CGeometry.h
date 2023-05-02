#pragma once
#include "IGeoJSONElement.h"
#include "GeoJSONTypes.h"
#include <memory>

namespace GeoJSON
{
class CGeometry : public IGeoJSONElement
{
public:
  CGeometry();
  CGeometry( const tGeometryType type );
  virtual ~CGeometry();

  tGeometryType GetType() const { return m_geometryType; };

public:
  virtual const GeoBase::CGeoPoint& GetPoint() const;
  virtual const tGeometry& GetPoints() const;
  virtual const tMultiGeometry& GetMultiGeometry() const;

public:
  virtual bool RebuildFromJSON( const json& jsonTree ) override;
  virtual json BuildJSONTree() override;

private:
  tGeometryType m_geometryType;

};

using tGeometryPtr = std::shared_ptr<CGeometry>;

}
