#include "IExpectedScoreHeuristics.h"

namespace osmMachine
{
class CSimpleDistanceHeuristics : public IExpectedScoreHeuristics
{
public:
  CSimpleDistanceHeuristics() = default;
  virtual ~CSimpleDistanceHeuristics() = default;

  virtual double CalcuateExpectedScoreThroughPoint( tOSMNodeShPtr osmNode, const COSMPosition& destination) override;
};
}