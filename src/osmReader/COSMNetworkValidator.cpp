#include "COSMNetworkValidator.h"
#include <COSMWay.h>
#include <COSMNode.h>
#include <iostream>
namespace osmMachine
{

COSMNetworkValidator::COSMNetworkValidator(const OSMRoutingNetwork& routingNetwork)
: m_routingNetwork(routingNetwork)
{

}

COSMNetworkValidator::~COSMNetworkValidator()
{

}

bool COSMNetworkValidator::Validate()
{
  bool validationResult(true);

  for ( auto wayIter : m_routingNetwork.id2WayMap )
  {
    auto wayPtr = wayIter.second;

    for ( const auto& waySegment : wayPtr->GetWaySegments() )
    {
      if ( !waySegment.getBeginNode()->isValid() )
      {
        return false;
      }
      
      if ( !waySegment.getEndNode()->isValid() )
      {
        return false;
      }
    }
  }

  return validationResult;
}

bool COSMNetworkValidator::InTheMiddlePoints()
{
  bool validationResult(false);

  

  return validationResult;
}

}