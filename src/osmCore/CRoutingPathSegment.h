#pragma once
#include "COSMWay.h"

namespace osmMachine
{
class CRoutingPathSegment 
{
  enum class tPathSegmentDirection
  {
    eConsistent,
    eOpposite
  };
public:
  CRoutingPathSegment( tWayShPtr osmWay, bool consistent);
  virtual ~CRoutingPathSegment();

private:
  tWayShPtr m_osmWay;

  tPathSegmentDirection m_pathDirection;
};
}