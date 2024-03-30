#pragma once
#include <osmCore/OSMRoutingNetwork.h>
#include <Logger/Logger.h>
#include <Logger/ILogger.h>
#include "COSMMapMatcher.h"
#include "OSMConfiguration.h"
#include <osmRouter/COSMRouter.h>


namespace osmMachine
{

class COSMEngine
{
public:
  COSMEngine();
  virtual ~COSMEngine();

  bool Initialize( const OSMConfiguration& configuration, std::shared_ptr<Logger::ILogger> pLogger = {} );

  void CleanUp();

  tMapMatching FindOSMLocation( const GeoBase::CGeoPoint& point );

  tOSMPath FindOptimalPath( const std::list< GeoBase::CGeoPoint > viaPointList);

private:
  OSMRoutingNetwork m_routingNetwork;
  
  COSMMapMatcher m_mapMatcher;

  COSMRouter m_router;

  std::shared_ptr<Logger::ILogger> m_pLogger;
};

}