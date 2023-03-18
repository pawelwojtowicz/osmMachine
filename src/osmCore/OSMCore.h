#pragma once
#include <map>
#include <list>
#include <memory>

namespace osmMachine
{
class COSMNode;
class COSMWay;

using tPropertyMap = std::map<std::string, std::string>;
using tOSMNodeShPtr = std::shared_ptr<COSMNode>;
using tWayShPtr = std::shared_ptr<COSMWay>;
using tNodeId2NodeMap = std::map< int64_t , tOSMNodeShPtr>;
using tWayId2WayMap = std::map< int64_t, tWayShPtr >;

using tWayList = std::list<tWayShPtr>;
using tNodeId2WayListsMap = std::map< int64_t, tWayList>;

}