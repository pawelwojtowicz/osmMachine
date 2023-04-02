#pragma once
#include <OSMRoutingNetwork.h>
#include "COSMMapMatcher.h"
#include "OSMConfiguration.h"

namespace osmMachine
{

class COSMEngine
{
public:
  COSMEngine();
  virtual ~COSMEngine();

  bool Initialize( const OSMConfiguration& configuration);
  void CleanUp();

private:
  OSMRoutingNetwork m_routingNetwork;
  
  COSMMapMatcher m_mapMatcher;

};

}