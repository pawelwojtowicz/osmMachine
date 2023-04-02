#include <iostream>
#include <iomanip>
#include <OSMRoutingNetwork.h>
#include <COSMModelBuilder.h>

int main( int argc, char** argv)
{
  if ( argc > 1 )
  {
    std::string osmFileName(argv[1]);

    for ( int zoomLevel = 5 ; zoomLevel < 20 ; ++zoomLevel )
    {
      osmMachine::OSMRoutingNetwork routingNetwork;
      osmMachine::COSMModelBuilder routingNetworkBuilder(routingNetwork);

      routingNetworkBuilder.ReadOSMData( osmFileName, zoomLevel);

      const auto geoBucketStatus = routingNetwork.wayGeoBuckets.Stats();

      std::cout << "ZoomLevel=" << std::setw(3) << geoBucketStatus.zoomLevel
                << "\tbucketCount=" << std::setw(6) << geoBucketStatus.bucketCount
                << "\tmin=" << std::setw(6) << geoBucketStatus.min
                << "\tmax= " << std::setw(6) << geoBucketStatus.max
                << "\tavrg=" << std::setw(6) << geoBucketStatus.avrg << std::endl;
    }

    std::cout << osmFileName << std::endl;
  }

  return 0;
}