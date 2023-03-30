#pragma once
#include <OSMRoutingNetwork.h>
#include "COSMMapMatcher.h"

namespace osmMachine
{

class COSMEngine
{
  COSMEngine();
  virtual ~COSMEngine();

  bool Initialize();
  void CleanUp();

private:
  COSMEngine(const COSMEngine&) = delete;
  COSMEngine& operator=(const COSMEngine&) = delete;


private:
  OSMRoutingNetwork m_routingNetwork;

  COSMMapMatcher m_mapMatcher;

};

}