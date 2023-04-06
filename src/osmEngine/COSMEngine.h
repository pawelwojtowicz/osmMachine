#pragma once
#include <osmCore/OSMRoutingNetwork.h>
#include <Logger/Logger.h>
#include <Logger/ILogger.h>
#include "COSMMapMatcher.h"
#include "OSMConfiguration.h"

namespace osmMachine
{

class COSMEngine
{
public:
  COSMEngine();
  virtual ~COSMEngine();

  bool Initialize( const OSMConfiguration& configuration, std::shared_ptr<Logger::ILogger> pLogger = {} );

  void CleanUp();

  tMapMatching FindOSMLocation( const CGeoPoint& point );

private:
  OSMRoutingNetwork m_routingNetwork;
  
  COSMMapMatcher m_mapMatcher;

  std::shared_ptr<Logger::ILogger> m_pLogger;
};

}