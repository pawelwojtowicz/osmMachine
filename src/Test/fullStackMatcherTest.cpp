#include <iostream>
#include <COSMEngine.h>

using namespace std;

int main( int argc, char** argv)
{
  if ( argc > 1 )
  {
    std::string osmFileName(argv[1]);

    std::cout << "Loading [" << osmFileName << "]" << std::endl;

    osmMachine::COSMEngine engine;

    osmMachine::OSMConfiguration configuration;

    configuration.osmMapFile = osmFileName;

    engine.Initialize( configuration );

    std::cout << "Loaded [" << osmFileName << "] ! " << std::endl;

//    osmMachine::CGeoPoint point( DEG2RAD(51.121398),DEG2RAD(15.906612)); // wayID = 229214577
    osmMachine::CGeoPoint point( DEG2RAD(51.1237259939271),DEG2RAD(15.915939244701315)); // wayID = 234858257 
    osmMachine::COSMPosition mapMatching = engine.FindOSMLocation(point);

    std::cout << "Map matched WayId=" << std::dec << mapMatching.GetWayId() <<" dist="<< mapMatching.GetDistance() <<std::endl;
  }

  return 0;
}