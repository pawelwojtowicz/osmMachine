#include <gtest/gtest.h>
#include <GeoBase/CTileUtils.cpp>
#include <GeoBase/GeoDefs.h>
#include "tileTestHelper.h"

using namespace GeoBase;

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 7 should be on the tile: 32,47
TEST( CTileUtils, Tiling_zoom7 ) 
{
  int zoomLevel(7);
  auto tileY = GeoBase::CTileUtils::gpsLat2TileY((41.85), zoomLevel);
  auto tileX = GeoBase::CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
  ASSERT_EQ( tileX , 32 );
  ASSERT_EQ( tileY , 47 );
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 6 should be on the tile: 16,23
TEST( CTileUtils, Tiling_zoom6 ) 
{
  int zoomLevel(6);
  auto tileY = GeoBase::CTileUtils::gpsLat2TileY((41.85), zoomLevel);
  auto tileX = GeoBase::CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
  ASSERT_EQ( tileX , 16 );
  ASSERT_EQ( tileY , 23 );    
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 10 should be on the tile: 262,380
TEST( CTileUtils, Tiling_zoom10 ) 
{
  int zoomLevel(10);
  auto tileY = GeoBase::CTileUtils::gpsLat2TileY((41.85), zoomLevel);
  auto tileX = GeoBase::CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
  ASSERT_EQ( tileX , 262 );
  ASSERT_EQ( tileY , 380 );    
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 15 should be on the tile: 8405,12182
TEST( CTileUtils, Tiling_zoom15 ) 
{
  int zoomLevel(15);
  auto tileY = GeoBase::CTileUtils::gpsLat2TileY((41.85), zoomLevel);
  auto tileX = GeoBase::CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
  ASSERT_EQ( tileX , 8405 );
  ASSERT_EQ( tileY , 12182 );    
}

TEST( CTileUtils, BackAndForthZoom10 ) 
{
  uint32_t tileX = 100;
  uint32_t tileY = 100;

  std::pair<double, double> center =  returnCenterOfATile( tileX, tileY, 10);
  
  ASSERT_EQ( tileY , GeoBase::CTileUtils::gpsLat2TileY(center.first, 10) );
  ASSERT_EQ( tileX , GeoBase::CTileUtils::gpsLon2TileX(center.second, 10 ) );    
}

TEST( CTileUtils, BackAndForthZoom15 ) 
{
  uint32_t tileX = 1000;
  uint32_t tileY = 100;

  std::pair<double, double> center =  returnCenterOfATile( tileX, tileY, 10);
  
  ASSERT_EQ( tileY , GeoBase::CTileUtils::gpsLat2TileY(center.first, 10) );
  ASSERT_EQ( tileX , GeoBase::CTileUtils::gpsLon2TileX(center.second, 10 ) );    
}

TEST( CTileUtils, BackAndForthZoom20 ) 
{
  uint32_t tileX = 1000;
  uint32_t tileY = 5000;

  std::pair<double, double> center =  returnCenterOfATile( tileX, tileY, 10);
  
  ASSERT_EQ( tileY , GeoBase::CTileUtils::gpsLat2TileY(center.first, 10) );
  ASSERT_EQ( tileX , GeoBase::CTileUtils::gpsLon2TileX(center.second, 10 ) );    
}