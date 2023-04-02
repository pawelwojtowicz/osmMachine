#include "CGeoIndex.h"
#include <cmath>
#include "CTileUtils.h"

namespace osmMachine
{

CGeoIndex::CGeoIndex()
: m_zoomLevel(0)
, m_xMin(0)
, m_yMin(0)
, m_dx(0)
, m_dy(0)

{

}
CGeoIndex::~CGeoIndex()
{

}

int CGeoIndex::Initialize( double minLat, double minLon, double maxLat, double maxLon, int zoomLevel )
{
  m_zoomLevel = zoomLevel;
  m_xMin = CTileUtils::gpsLon2TileX( minLon ,m_zoomLevel );
  m_yMin = CTileUtils::gpsLat2TileY( minLat ,m_zoomLevel );
  m_dx = CTileUtils::gpsLon2TileX( maxLon ,m_zoomLevel ) - m_xMin;
  m_dy = CTileUtils::gpsLat2TileY( maxLat, m_zoomLevel ) - m_yMin;

  return 0;
}

int64_t CGeoIndex::CalculateIndex( double lat, double lon ) const
{
  int64_t index(0);

  if ( 0 != m_zoomLevel )
  {
    int xTile = CTileUtils::gpsLon2TileX( lon ,m_zoomLevel ) - m_xMin;
    int yTile = CTileUtils::gpsLat2TileY( lat ,m_zoomLevel ) - m_yMin;
    index = ( (0xffffffff & static_cast<int64_t>(yTile)) << 32 ) + (0xffffffff & static_cast<int64_t>(xTile));
  }

  return index;
}

}