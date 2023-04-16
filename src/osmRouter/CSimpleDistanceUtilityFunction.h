#pragma once
#include "IOSMRoutingUtilityFunction.h"

namespace osmMachine
{
class CSimpleDistanceUtilityFunction : public IOSMRoutingUtilityFunction
{
public:
  CSimpleDistanceUtilityFunction() =default ;
  virtual ~CSimpleDistanceUtilityFunction() =default ;

  virtual double CalculateScore( tPtrRoutingPoint currentNode , tWayShPtr nextWay ) override;
};
}