#include "COSMEngine.h"
#include <COSMModelBuilder.h>

namespace osmMachine
{

COSMEngine::COSMEngine()
: m_routingNetwork()
, m_mapMatcher(m_routingNetwork)
{

}

COSMEngine::~COSMEngine()
{

}

bool COSMEngine::Initialize( const OSMConfiguration& configuration )
{
  COSMModelBuilder osmBuilder(m_routingNetwork);
  osmBuilder.ReadOSMData(configuration.osmMapFile, configuration.geoBucketingFactor );

  m_mapMatcher.Initialize( configuration.mapMatcherNeighbourhoodSize);

  return true;
}

void COSMEngine::CleanUp()
{

}

COSMPosition COSMEngine::FindOSMLocation( const CGeoPoint& point )
{
  return m_mapMatcher.FindOSMPosition( point);
}

}