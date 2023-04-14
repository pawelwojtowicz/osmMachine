#pragma once
#include "IOSMRouter.h"
#include <osmCore/OSMRoutingNetwork.h>
#include "COSMRoutePoint.h"

namespace osmMachine
{
class COSMRouter : public IOSMRouter
{
  using tNodeId2RoutingPointMap = std::map< int64_t ,  tPtrRoutingPoint>;
public:
  COSMRouter(OSMRoutingNetwork& routingNetwork );
  virtual ~COSMRouter();

private:
  virtual tOSMPath FindOptimalPath( const COSMPosition& start, const COSMPosition& destination) override;

private:
  double ToGoHeuristics( const GeoBase::CGeoPoint& begin, const GeoBase::CGeoPoint& end);


private:
  OSMRoutingNetwork& m_routingNetwork;
};
}