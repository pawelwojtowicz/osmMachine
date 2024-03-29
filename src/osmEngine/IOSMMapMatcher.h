#pragma once
#include <set>
#include <GeoBase/CGeoPoint.h>
#include <osmCore/COSMPosition.h>

namespace osmMachine
{

using tMapMatching = std::set<COSMPosition>;

class IOSMMapMatcher
{
public:
  IOSMMapMatcher() = default;
  virtual ~IOSMMapMatcher() = default;

  virtual tMapMatching FindOSMPosition( const GeoBase::CGeoPoint& position) = 0;
};
}