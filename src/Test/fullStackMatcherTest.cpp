#include <osmEngine/COSMEngine.h>
#include <memory>
#include <Logger/Logger.h>
#include <Logger/CSimpleLogger.h>
#include <Utils/CTimespanMeter.h>

using namespace std;

int main( int argc, char** argv)
{
  std::shared_ptr<Logger::CSimpleLogger> logger = std::make_unique<Logger::CSimpleLogger>();

  if ( argc > 1 )
  {
    std::string osmFileName(argv[1]);

    LOG(INFO,("Loading [%s]",osmFileName.c_str()));

    osmMachine::COSMEngine engine;

    osmMachine::OSMConfiguration configuration;

    configuration.osmMapFile = osmFileName;
    configuration.geoBucketingFactor = 15;

    Utils::CTimespanMeter timespanMeter("LoadingOSM");

    engine.Initialize( configuration ,logger);
    timespanMeter.CatchTimestampToBaseline("Finished");
    LOG(INFO,("Loaded [%s]",osmFileName.c_str()));

//    osmMachine::CGeoPoint point( DEG2RAD(51.121398),DEG2RAD(15.906612)); // wayID = 229214577
    osmMachine::CGeoPoint point( DEG2RAD(51.1237259939271),DEG2RAD(15.915939244701315)); // wayID = 234858257 
    timespanMeter.ResetTimeBaseline();
    osmMachine::COSMPosition mapMatching = engine.FindOSMLocation(point);
    timespanMeter.CatchTimestampToBaseline("Map matching");
   LOG(INFO,("Map matched WayId=%d", mapMatching.GetWayId()));
  }

  return 0;
}