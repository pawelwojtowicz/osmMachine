#pragma once
#include <list>
#include <osmCore/CShapePoint.h>
#include <osmCore/COSMPosition.h>

namespace osmMachine
{

class IOSMRouter
{
public:
  virtual tOSMShapePath FindOptimalPath( const std::list<COSMPosition>& viaPoints ) = 0;
};
}