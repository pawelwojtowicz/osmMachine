#include <gtest/gtest.h>
#include <CTileUtils.cpp>
#include <GeoDefs.h>

using namespace osmMachine;

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 7 should be on the tile: 32,47
TEST( CTileUtils, Tiling_zoom7 ) 
{
    int zoomLevel(7);
    auto tileY = CTileUtils::gpsLat2TileY((41.85), zoomLevel);
    auto tileX = CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
    ASSERT_EQ( tileX , 32 );
    ASSERT_EQ( tileY , 47 );
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 6 should be on the tile: 16,23
TEST( CTileUtils, Tiling_zoom6 ) 
{
    int zoomLevel(6);
    auto tileY = CTileUtils::gpsLat2TileY((41.85), zoomLevel);
    auto tileX = CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
    ASSERT_EQ( tileX , 16 );
    ASSERT_EQ( tileY , 23 );    
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 7 should be on the tile: 262,380
TEST( CTileUtils, Tiling_zoom10 ) 
{
    int zoomLevel(10);
    auto tileY = CTileUtils::gpsLat2TileY((41.85), zoomLevel);
    auto tileX = CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
    ASSERT_EQ( tileX , 262 );
    ASSERT_EQ( tileY , 380 );    
}

//base on the: https://oms.wff.ch/calc.htm
// cordinates lat/lon - 41.85/-87.65
// for zoom level 15 should be on the tile: 8405,12182
TEST( CTileUtils, Tiling_zoom15 ) 
{
    int zoomLevel(15);
    auto tileY = CTileUtils::gpsLat2TileY((41.85), zoomLevel);
    auto tileX = CTileUtils::gpsLon2TileX((-87.65),zoomLevel);
    ASSERT_EQ( tileX , 8405 );
    ASSERT_EQ( tileY , 12182 );    
}
