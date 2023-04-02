#pragma once
#include <CGeoBucket.h>
#include "COSMNode.h"
#include "COSMWay.h"
#include <string>
#include <list>
#include <map>

namespace osmMachine
{
using tNodeId2NodeMap = std::map< int64_t , tOSMNodeShPtr>;
using tWayId2WayMap = std::map< int64_t, tWayShPtr >;
using tWayList = std::list<tWayShPtr>;
using tNodeId2WayListsMap = std::map< int64_t, tWayList>;
using tWayGeoBuckets = CGeoBucket<tWayShPtr>;

struct OSMRoutingNetwork
{
  OSMRoutingNetwork() {};
  
  tNodeId2NodeMap id2NodeMap;

  tWayId2WayMap id2WayMap;

  tWayId2WayMap helperWayId2MapWay;

  tNodeId2WayListsMap nodeId2Ways;

  tWayGeoBuckets wayGeoBuckets;
};

}