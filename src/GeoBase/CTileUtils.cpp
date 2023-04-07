#include "CTileUtils.h"
#include <cmath>

namespace GeoBase
{

uint32_t CTileUtils::gpsLon2TileX(double lon, int z)
{
   return (uint32_t)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}
 
uint32_t CTileUtils::gpsLat2TileY(double lat, int z)
{
   double latrad = lat * M_PI/180.0;
	return (uint32_t)(floor((1.0 - asinh(tan(latrad)) / M_PI) / 2.0 * (1 << z))); }
 
double CTileUtils::TileX2gpsLon(uint32_t x, int z)
{
   return x / pow(2.0, z) * 360.0 - 180;
}
 
double CTileUtils::TileY2gpsLat(uint32_t y, int z)
{
   double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
   return double((180.0 / M_PI) * (atan(0.5 * (exp(n) - exp(-n)))));
}

}