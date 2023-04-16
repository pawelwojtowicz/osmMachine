#pragma once
#include "COSMRoutePoint.h"

namespace osmMachine
{
/** Maybe this polymorphism should be removed from here, but for it put here to enable further tweaking of the utility function*/
class IRoutingUtilityFunction
{
public:
  virtual double CalculateScore(  tPtrRoutingPoint currentNode , tWayShPtr nextWay ) = 0;
};
}