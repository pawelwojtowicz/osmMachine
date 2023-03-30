#include <iostream>
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

      std::cout << "ZoomLevel=" << geoBucketStatus.zoomLevel
                << "\t\tbucketCount=" << geoBucketStatus.bucketCount
                << "\t\tmin=" << geoBucketStatus.min
                << "\t\tmax= " << geoBucketStatus.max
                << "\t\tavrg=" << geoBucketStatus.avrg << std::endl;
    }

    std::cout << osmFileName << std::endl;
  }

  return 0;
}