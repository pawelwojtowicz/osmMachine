#include "CSimpleDistanceUtilityFunction.h"

namespace osmMachine
{

double CSimpleDistanceUtilityFunction::CalculateScore( tPtrRoutingPoint currentNode , tWayShPtr nextWay)
{
  return ( currentNode->GetScore() + nextWay->GetLength() );
}



}