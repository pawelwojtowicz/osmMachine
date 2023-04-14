#pragma once
#include <map>
#include "COSMRoutePoint.h"

namespace osmMachine
{
class COSMRoutingPointSet
{
  using tNodeId2RoutingPointMap = std::map< int64_t , tPtrRoutingPoint>;
public:
  COSMRoutingPointSet();
  virtual ~COSMRoutingPointSet();

  bool NotEmpty();

  void AddRoutingPoint( tPtrRoutingPoint);

  bool Contains ( const int64_t routingPointId );

  tPtrRoutingPoint GetBestRoutingPoint();

  tPtrRoutingPoint GetRoutingPointById( const int64_t routingPointId);

  void RemoveRoutingPoint( const int64_t routingPointId );

private:
  tNodeId2RoutingPointMap m_routingPoints;
};
}
