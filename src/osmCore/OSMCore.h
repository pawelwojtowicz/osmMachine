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
}