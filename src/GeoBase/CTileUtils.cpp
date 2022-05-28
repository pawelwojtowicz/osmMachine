#include "CTileUtils.h"
#include <cmath>

namespace osmMachine
{

int CTileUtils::gpsLon2TileX(double lon, int z)
{
   return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}
 
int CTileUtils::gpslat2TileY(double lat, int z)
{
   return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}
 
double CTileUtilsTileX2gpsLon(int x, int z)
{
   return x / pow(2.0, z) * 360.0 - 180;
}
 
double CTileUtils::TileY2gpsLat(int y, int z)
{
   double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
   return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

}