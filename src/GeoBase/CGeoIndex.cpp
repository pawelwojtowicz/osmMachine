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

tGeoIndex CGeoIndex::CalculateIndex( double lat, double lon ) const
{
  tGeoIndex index(-1);

  if ( 0 != m_zoomLevel )
  {
    int xTile = CTileUtils::gpsLon2TileX( lon ,m_zoomLevel ) - m_xMin;
    int yTile = CTileUtils::gpsLat2TileY( lat ,m_zoomLevel ) - m_yMin;
    index = ( (0xffff & yTile) << 16 ) + (0xffff & xTile);
  }

  return index;
}

}