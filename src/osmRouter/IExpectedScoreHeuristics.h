#pragma once
#include "COSMRoutePoint.h"
#include <osmCore/COSMPosition.h>

namespace osmMachine
{
class IExpectedScoreHeuristics
{
public:
  IExpectedScoreHeuristics() = default;
  virtual ~IExpectedScoreHeuristics() = default;

  virtual double CalcuateExpectedScoreThroughPoint( tOSMNodeShPtr osmNode, const COSMPosition& destination) = 0; 
};
}