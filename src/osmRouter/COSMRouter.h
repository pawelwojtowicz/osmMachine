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

  virtual tOSMShapePath FindOptimalPath( const std::list<COSMPosition>& viaPoints );

private:
  tOSMShapePath FindOptimalPath( const int64_t originNodeId, const COSMPosition& start, const COSMPosition& destination);

private:
  double ToGoHeuristics( const GeoBase::CGeoPoint& begin, const GeoBase::CGeoPoint& end);

  tWayList GetRoutingPointNeighbours( const int64_t osmNodeId );

private:
  const OSMRoutingNetwork& m_routingNetwork;
};
}