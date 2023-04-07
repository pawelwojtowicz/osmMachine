#pragma once
#include <cstdint>

namespace GeoBase
{
class CTileUtils
{
  CTileUtils();
public:
    static uint32_t gpsLon2TileX(double lon, int z);
    static uint32_t gpsLat2TileY(double lat, int z);
    static double TileX2gpsLon(uint32_t x, int z);
    static double TileY2gpsLat(uint32_t y, int z);
};
}
