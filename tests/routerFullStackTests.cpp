#include <osmEngine/COSMEngine.h>
#include <memory>
#include <Logger/Logger.h>
#include <Logger/CSimpleLogger.h>
#include <Utils/CTimespanMeter.h>

#include <iostream>
#include <iomanip>

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

    GeoBase::CGeoPoint origin( DEG2RAD(51.121398),DEG2RAD(15.906612)); // wayID = 229214577
    GeoBase::CGeoPoint destination1( DEG2RAD(51.1237259939271),DEG2RAD(15.915939244701315)); // wayID = 234858257
    GeoBase::CGeoPoint destination2( DEG2RAD(51.1267799),DEG2RAD(15.9230522) );

    std::list< GeoBase::CGeoPoint > viaList = {  destination2, destination1 };// , origin };

    auto path = engine.FindOptimalPath(viaList);

    int i = 0;

    for( const auto& point : path)
    {
      std::cout << ++i << "|" << std::setprecision (15) << RAD2DEG(point.getOSMPosition().getLon()) << "|"<<  std::setprecision (15)<< RAD2DEG(point.getOSMPosition().getLat()) << "|"<< point.GetOsmNodeId() << "|" << static_cast<int>(point.GetType()) << std::endl; 
    }
  }

  return 0;
}