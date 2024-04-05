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
  eSimple = 1,
  ePOI = 2,
  };

  CShapePoint(  tViaPointType type, 
                tOSMNodeShPtr rawPosition, 
                tOSMNodeShPtr snappedPosition, 
                const int64_t osmWayId, 
                const double length, 
                const int heading );

  CShapePoint(  tViaPointType type, 
                const GeoBase::CGeoPoint& rawPosition, 
                const GeoBase::CGeoPoint& snappedPosition, 
                const int64_t osmWayId,
                const double length, 
                const int heading );

  const int64_t GetOsmNodeId() const;

  const GeoBase::CGeoPoint& getOSMPosition() const;

  const tViaPointType GetType() const;

  const double GetLength() const;
  const int GetHeading() const;

private:
  tViaPointType m_type;
  int64_t m_osmNodeId;
  int64_t m_osmWayId;
  GeoBase::CGeoPoint m_rawPosition; 
  GeoBase::CGeoPoint m_snappedPosition;

  double m_length;

  int m_heading;
};

using tOSMShapePath = std::list<CShapePoint>;

}