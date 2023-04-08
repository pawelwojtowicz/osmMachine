#pragma once
#include "IGeoZoneMonitor.h"
#include <vector>
#include <GeoBase/CBoundingBox.h>

namespace GeoZoneMonitor
{
class CPolylineZoneMonitor : public IGeoZoneMonitor
{
public:

  CPolylineZoneMonitor( const std::vector<GeoBase::CGeoPoint>& definition );
  virtual ~CPolylineZoneMonitor();

  void PreprocessGeoZoneDefinition( const std::vector<GeoBase::CGeoPoint>& definition);

  virtual bool IsInsideArea( const GeoBase::CGeoPoint& point ) override; 

private:
  GeoBase::CBoundingBox m_boundingBox;
};
}