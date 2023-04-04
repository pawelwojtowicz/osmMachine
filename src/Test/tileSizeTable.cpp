#include <GeoBase/CTileUtils.h>
#include <GeoBase/CGeoPoint.h>
#include <GeoBase/GeoUtils.h>
#include <iostream>

using namespace std;
using namespace osmMachine;

void PrintTileSizeForZoomLevel( int zoomLevel )
{
  CGeoPoint p1( CTileUtils::TileX2gpsLon(5, zoomLevel) , CTileUtils::TileY2gpsLat(1, zoomLevel) );
  CGeoPoint p2( CTileUtils::TileX2gpsLon(5, zoomLevel) , CTileUtils::TileY2gpsLat(2, zoomLevel) );
  CGeoPoint p3( CTileUtils::TileX2gpsLon(6, zoomLevel) , CTileUtils::TileY2gpsLat(1, zoomLevel) );

  std::cout <<  "zoomLevel=" << zoomLevel << 
                " dx=" << GeoUtils::Point2PointDistance(p3,p1) << 
                " dy=" << GeoUtils::Point2PointDistance(p2,p1) << std::endl;
}

int main( int argc, char** argv)
{
  for ( int zoomLevel = 0 ; zoomLevel < 21 ; ++zoomLevel)
  {
    PrintTileSizeForZoomLevel( zoomLevel ) ;
  }
  return 0;
}