#pragma once

namespace osmMachine
{
class CTileUtils
{
  CTileUtils();
public:
    static int gpsLon2TileX(double lon, int z);
    static int gpsLat2TileY(double lat, int z);
    static double TileX2gpsLon(int x, int z);
    static double TileY2gpsLat(int y, int z);
};
}
