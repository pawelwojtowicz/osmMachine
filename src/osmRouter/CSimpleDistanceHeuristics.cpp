#include "CSimpleDistanceHeuristics.h"
#include <GeoBase/GeoUtils.h>

namespace osmMachine
{
double CSimpleDistanceHeuristics::CalcuateExpectedScoreThroughPoint( tOSMNodeShPtr osmNode, const COSMPosition& destination)
{
  return GeoBase::GeoUtils::Point2PointDistance(*osmNode, destination.GetPositionSnapped2OSM());
}

}