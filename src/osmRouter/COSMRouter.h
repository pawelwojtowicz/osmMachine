#pragma once
#include "IOSMRouter.h"
#include <osmCore/OSMRoutingNetwork.h>
#include "COSMRoutePoint.h"

namespace osmMachine
{
class COSMRouter : public IOSMRouter
{
public:
  COSMRouter(const OSMRoutingNetwork& routingNetwork );
  virtual ~COSMRouter();

  virtual tOSMPath FindOptimalPath( const COSMPosition& start, const COSMPosition& destination) override;

private:
  tOSMPath BuildSolutionPath( tPtrRoutingPoint routingPoint, const COSMPosition& destination );

private:
  double ToGoHeuristics( const GeoBase::CGeoPoint& begin, const GeoBase::CGeoPoint& end);

  tWayList GetRoutingPointNeighbours( const int64_t osmNodeId );

private:
  const OSMRoutingNetwork& m_routingNetwork;
};
}