#include "COSMEngine.h"
#include <COSMModelBuilder.h>

#include <string>

namespace osmMachine
{

COSMEngine::COSMEngine()
: m_routingNetwork()
, m_mapMatcher( m_routingNetwork )
{

}

COSMEngine::~COSMEngine()
{

}

bool COSMEngine::Initialize()
{
  bool success(false);

  std::string osmDataFileName("mapaZlotoryja.osm");

  COSMModelBuilder osmBuilder(m_routingNetwork);
  osmBuilder.ReadOSMData(osmDataFileName);

  return success;
}

void COSMEngine::CleanUp()
{

}

}