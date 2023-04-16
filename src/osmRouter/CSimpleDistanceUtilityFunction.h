#pragma once
#include "IRoutingUtilityFunction.h"

namespace osmMachine
{
class CSimpleDistanceUtilityFunction : public IRoutingUtilityFunction
{
public:
  CSimpleDistanceUtilityFunction() =default ;
  virtual ~CSimpleDistanceUtilityFunction() =default ;

  virtual double CalculateScore( tPtrRoutingPoint currentNode , tWayShPtr nextWay ) override;
};
}