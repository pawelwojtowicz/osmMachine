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
    m_lineType = tLineType::eVertical;
    m_latBegin = std::min(m_latBegin, m_latEnd);
    m_latEnd = std::max(m_latBegin, m_latEnd);

  }
  else if ( begin.getLat() == end.getLat() )
  {
    m_lineType = tLineType::eHorizontal;
    m_lineDefinitionB = begin.getLat();
  }
  else
  {
    m_lineDefinitionA = ( begin.getLat() - end.getLat() )/( begin.getLon() - end.getLon() );
    if ( begin.getLon() > end.getLon() )
    {
      m_lineDefinitionA *= -1;
    }
    m_lineDefinitionB = begin.getLat() - m_lineDefinitionA * begin.getLon();

    m_lonBegin = std::min( begin.getLon(), end.getLon() );
    m_lonEnd = std::max( begin.getLon(), end.getLon() ); 
  }
}


CLineIntersectionDetector::~CLineIntersectionDetector()
{

}

bool CLineIntersectionDetector::Intersects( const GeoBase::CGeoPoint& point) const
{
  switch( m_lineType )
  {
  case tLineType::eHorizontal:
  {
    if ( m_lineDefinitionB == point.getLat() )
    {
      return ( point.getLon() >= m_lonBegin && point.getLon() <= m_lonEnd );
    }
  };break;
  case tLineType::eVertical:
  {
    return (point.getLat() >= m_latBegin && point.getLat() <= m_latEnd );
  };break;
  default:
  {
    double lonIntersection = (point.getLat() - m_lineDefinitionB)/m_lineDefinitionA;
    if ( lonIntersection >= point.getLon() && point.getLon() <= m_lonEnd )
    {
      return true;
    }
  };
  }
  return false;
}

}