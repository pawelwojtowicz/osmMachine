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

  const int64_t GetOsmNodeId() const;

  const GeoBase::CGeoPoint& getOSMPosition() const;

private:
  tViaPointType m_type;
  int64_t m_osmNodeId;
  int64_t m_osmWayId;
  GeoBase::CGeoPoint m_rawPosition; 
  GeoBase::CGeoPoint m_snappedPosition;

  double m_length;

  double m_heading;
};

using tOSMShapePath = std::list<CShapePoint>;

}