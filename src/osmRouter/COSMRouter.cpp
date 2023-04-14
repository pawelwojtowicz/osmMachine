#include "COSMRouter.h"
#include <memory>

namespace osmMachine
{
COSMRouter::COSMRouter( OSMRoutingNetwork& routingNetwork)
: m_routingNetwork( routingNetwork)
{

}

COSMRouter::~COSMRouter()
{
  
}

tOSMPath COSMRouter::FindOptimalPath( const COSMPosition& start, const COSMPosition& destination)
{
  tNodeId2RoutingPointMap openNodes;
  tNodeId2RoutingPointMap closedNodes;


  if ( !start.GetWay()->IsOneWay() )
  {
  }


  return tOSMPath();

}

}