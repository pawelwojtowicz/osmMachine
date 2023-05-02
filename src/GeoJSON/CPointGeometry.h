#pragma once
#include "CGeometry.h"

namespace GeoJSON
{
class CPointGeometry : public CGeometry
{
public:
  CPointGeometry();
  CPointGeometry( const GeoBase::CGeoPoint& point);
  
  virtual const GeoBase::CGeoPoint& GetPoint() const override;

public:
  virtual bool RebuildFromJSON( const json& jsonTree ) override;
  virtual json BuildJSONTree() override;


private:
  GeoBase::CGeoPoint m_point;
};
}