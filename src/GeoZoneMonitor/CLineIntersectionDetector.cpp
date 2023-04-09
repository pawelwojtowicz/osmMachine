#include "CLineIntersectionDetector.h"
#include <GeoBase/CGeoPoint.h>
#include <iostream>

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
    m_lonBegin = begin.getLon();
    m_latBegin = std::min(begin.getLat(), end.getLat() );
    m_latEnd = std::max(begin.getLat(), end.getLat() );

  }
  else if ( begin.getLat() == end.getLat() )
  {
    m_lineType = tLineType::eHorizontal;
    m_lonBegin = std::min(begin.getLon(), end.getLon());
    m_lineDefinitionB = begin.getLat();
  }
  else
  {
    if ( begin.getLon() < end.getLon())
    {
      m_lonBegin = begin.getLon();
      m_lonEnd = end.getLon(); 
      m_lineDefinitionA = ( begin.getLat() - end.getLat() )/( begin.getLon() - end.getLon() );  
    }
    else
    {
      m_lonBegin = end.getLon();
      m_lonEnd = begin.getLon(); 
      m_lineDefinitionA = ( end.getLat() - begin.getLat() )/( end.getLon() - begin.getLon() );
    }
    m_lineDefinitionB = begin.getLat() - m_lineDefinitionA * begin.getLon();
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
      return ( point.getLon() <= m_lonBegin );
    }
  };break;
  case tLineType::eVertical:
  {
    return (  ( point.getLat() >= m_latBegin ) && 
              ( point.getLat() <= m_latEnd) && 
              ( point.getLon() <= m_lonBegin ) );
  };break;
  default:
  {
    double lonIntersection = (point.getLat() - m_lineDefinitionB)/m_lineDefinitionA;
    if ( lonIntersection >= point.getLon() && lonIntersection <= m_lonEnd )
    {
      return true;
    }
  };
  }
  return false;
}

}