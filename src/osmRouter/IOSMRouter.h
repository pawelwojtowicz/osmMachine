#pragma once
#include <list>
#include <osmCore/COSMWay.h>
#include <osmCore/COSMPosition.h>

namespace osmMachine
{
using tOSMPath = std::list<tWayShPtr>;

class IOSMRouter
{
public:
  virtual tOSMPath FindOptimalPath( const COSMPosition& start, const COSMPosition& destination) = 0;
};
}