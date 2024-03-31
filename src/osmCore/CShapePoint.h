#pragma once
#include "COSMNode.h"
#include <list>

namespace osmMachine
{
class CShapePoint
{
public:
  enum class tViaPointType
  {
  eSimple,
  ePOI
  };

private:
  tViaPointType m_type;
  tOSMNodeShPtr m_rawPosition;
  tOSMNodeShPtr m_snappedPosition;

  double m_length;

  double m_heading;
};

using tOSMShapePath = std::list<CShapePoint>;

}