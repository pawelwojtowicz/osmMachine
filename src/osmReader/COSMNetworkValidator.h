#pragma once
#include <OSMRoutingNetwork.h>

namespace osmMachine
{
class COSMNetworkValidator
{
public:
  COSMNetworkValidator( const OSMRoutingNetwork& routingNetwork );
  virtual ~COSMNetworkValidator();

  bool Validate();

  bool InTheMiddlePoints();

private:
  const OSMRoutingNetwork& m_routingNetwork;
};
}