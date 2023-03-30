#pragma once
#include <OSMRoutingNetwork.h>

namespace osmMachine
{

class COSMMapMatcher
{
public:
  COSMMapMatcher( const OSMRoutingNetwork& routingNetwork );
  virtual ~COSMMapMatcher();

private:
  const OSMRoutingNetwork& m_routingNetwork;
};

}