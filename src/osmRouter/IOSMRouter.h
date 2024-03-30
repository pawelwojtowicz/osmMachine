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
  virtual tOSMPath FindOptimalPath( const std::list<COSMPosition>& viaPoints ) = 0;
};
}