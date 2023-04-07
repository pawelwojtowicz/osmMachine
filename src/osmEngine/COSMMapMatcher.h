#pragma once
#include "IOSMMapMatcher.h"
#include <osmCore/OSMRoutingNetwork.h>
#include "COSMPosition.h"

namespace osmMachine
{

class COSMMapMatcher : public IOSMMapMatcher
{
public:
  COSMMapMatcher( const OSMRoutingNetwork& routingNetwork );
  virtual ~COSMMapMatcher();

  void Initialize ( const int neighbourhoodSize, const int mapMatcherRecomendationSize, const double mapMatchingTolerance);

  tMapMatching FindOSMPosition( const GeoBase::CGeoPoint& position) override;

private:
  const OSMRoutingNetwork& m_routingNetwork;

  int m_neighbourhoodSize;

  int m_recomendationSize;

  double m_mapMatchingTolerance;
};

}