#include "COSMRoutePoint.h"

namespace osmMachine
{

COSMRoutePoint::COSMRoutePoint(tPtrRoutingPoint originPoint, tWayShPtr originWay, tOSMNodeShPtr geoPoint, double score, double toGoHeuristics)
: m_originRoutingPoint(originPoint)
, m_originWay(originWay)
, m_geoPoint(geoPoint)
, m_score(score)
, m_toGoHeuristics(toGoHeuristics)
, m_finalScoreHeuristics( m_score + m_toGoHeuristics)
{
}

COSMRoutePoint::~COSMRoutePoint()
{
}

void COSMRoutePoint::UpdateScore( tPtrRoutingPoint& originPoint, tWayShPtr originWay, double score )
{
  m_originRoutingPoint = originPoint;
  m_originWay = originWay;
  m_score = score;
  m_finalScoreHeuristics = m_score + m_toGoHeuristics;
}

}