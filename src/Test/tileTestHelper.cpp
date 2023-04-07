#include "tileTestHelper.h"
#include <GeoBase/CTileUtils.h>

using namespace GeoBase;

std::pair< double, double> returnCenterOfATile( uint32_t x, uint32_t y , int zoomLevel)
{
  double lat = (CTileUtils::TileY2gpsLat(y, zoomLevel) + CTileUtils::TileY2gpsLat(y+1, zoomLevel))/2;
  double lon = (CTileUtils::TileX2gpsLon(x, zoomLevel) + CTileUtils::TileX2gpsLon(x+1, zoomLevel))/2;

  return { lat, lon };
}

