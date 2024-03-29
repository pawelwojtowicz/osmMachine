#include "COSMEngine.h"
#include <osmReader/COSMModelBuilder.h>
#ifdef WITH_LOGGER
#include "Logger/CSimpleLogger.h"
#endif

namespace osmMachine
{

COSMEngine::COSMEngine()
: m_routingNetwork()
, m_mapMatcher(m_routingNetwork)
, m_router(m_routingNetwork)
{

}

COSMEngine::~COSMEngine()
{

}

bool COSMEngine::Initialize( const OSMConfiguration& configuration, std::shared_ptr<Logger::ILogger> pLogger )
{
#ifdef WITH_LOGGER
  if ( !pLogger )
  {
    m_pLogger =  std::make_shared<Logger::CSimpleLogger>();
  }
  else
  {
    m_pLogger = pLogger;
  }
#endif

  COSMModelBuilder osmBuilder(m_routingNetwork);
  osmBuilder.ReadOSMData(configuration.osmMapFile, configuration.geoBucketingFactor );

  m_mapMatcher.Initialize( configuration.mapMatcherNeighbourhoodSize,
                           configuration.mapMatcherRecomendationSize,
                           configuration.mapMatchingTolerance );

  return true;
}

void COSMEngine::CleanUp()
{

}

tMapMatching COSMEngine::FindOSMLocation( const GeoBase::CGeoPoint& point )
{
  return m_mapMatcher.FindOSMPosition( point);
}

tOSMPath COSMEngine::FindOptimalPath( const GeoBase::CGeoPoint& origin, const GeoBase::CGeoPoint& destination)
{
  tMapMatching originMatching = m_mapMatcher.FindOSMPosition( origin );
  tMapMatching destinationMatching = m_mapMatcher.FindOSMPosition( destination );

  return m_router.FindOptimalPath(*originMatching.begin(), *destinationMatching.begin());
}

}