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

  CShapePoint( tViaPointType type, tOSMNodeShPtr rawPosition, tOSMNodeShPtr snappedPosition, const double& length, const double& heading );

private:
  tViaPointType m_type;
  tOSMNodeShPtr m_rawPosition;
  tOSMNodeShPtr m_snappedPosition;

  double m_length;

  double m_heading;
};

using tOSMShapePath = std::list<CShapePoint>;

}