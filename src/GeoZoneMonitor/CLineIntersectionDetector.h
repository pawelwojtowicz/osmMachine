#pragma once
#include <GeoBase/CGeoPoint.h>

namespace GeoZoneMonitor
{
class CLineIntersectionDetector
{
  enum class tLineType {
    eVertical,
    eOther
  };

public:
  CLineIntersectionDetector( const GeoBase::CGeoPoint& begin, const GeoBase::CGeoPoint& end );
  ~CLineIntersectionDetector();

  bool Intersects( const GeoBase::CGeoPoint& point) const;

private:
  tLineType m_lineType;
  double m_lineDefinitionA;
  double m_lineDefinitionB;

  double m_lonBegin;
  double m_lonEnd;

  double m_latBegin;
  double m_latEnd;
};
}