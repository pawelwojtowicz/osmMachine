#include "CLineIntersectionDetector.h"
#include <GeoBase/CGeoPoint.h>

namespace GeoZoneMonitor
{


CLineIntersectionDetector::CLineIntersectionDetector( const GeoBase::CGeoPoint& begin, const GeoBase::CGeoPoint& end )
: m_lineType(tLineType::eOther)
, m_lineDefinitionA(0)
, m_lineDefinitionB(0)
, m_lonBegin(0)
, m_lonEnd(0)
, m_latBegin(0)
, m_latEnd(0)
{
  if ( begin.getLon() == end.getLon() )
  {
    m_latBegin = std::min(m_latBegin, m_latEnd);
    m_latEnd = std::max(m_latBegin, m_latEnd);

  }
}


CLineIntersectionDetector::~CLineIntersectionDetector()
{

}

bool CLineIntersectionDetector::Intersects( const GeoBase::CGeoPoint& point) const
{
  if ( tLineType::eOther == m_lineType)
  {

  }

  return ( point.getLat() >= m_latBegin && point.getLat() <= m_latEnd );

}

}