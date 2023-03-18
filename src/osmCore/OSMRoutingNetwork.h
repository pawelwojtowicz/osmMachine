#pragma once
#include "OSMCore.h"

namespace osmMachine
{

struct OSMRoutingNetwork
{
  tNodeId2NodeMap id2NodeMap;

  tWayId2WayMap id2WayMap;

  tNodeId2WayListsMap nodeId2Ways;
};

}