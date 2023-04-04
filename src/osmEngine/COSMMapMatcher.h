#pragma once
#include <osmCore/OSMRoutingNetwork.h>
#include "COSMPosition.h"

namespace osmMachine
{

class COSMMapMatcher
{
public:
  COSMMapMatcher( const OSMRoutingNetwork& routingNetwork );
  virtual ~COSMMapMatcher();

  void Initialize ( const int neighbourhoodSize );

  COSMPosition FindOSMPosition( const CGeoPoint& point);

private:
  const OSMRoutingNetwork& m_routingNetwork;

  int m_neighbourhoodSize;
};

}