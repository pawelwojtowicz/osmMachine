#pragma once
#include <COSMNode.h>

namespace osmMachine
{

struct OSMRoutingNetwork
{
  tNodeId2NodeMap id2NodeMap;

  tWayId2WayMap id2WayMap;

  tWayId2WayMap helperWayId2MapWay;

  tNodeId2WayListsMap nodeId2Ways;

  tWayGeoBuckets wayGeoBuckets;
};

}