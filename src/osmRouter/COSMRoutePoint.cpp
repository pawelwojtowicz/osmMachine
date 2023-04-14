#include "COSMRoutePoint.h"

namespace osmMachine
{
COSMRoutePoint::COSMRoutePoint()
: m_originRoutingPoint()
, m_originWay()
, m_geoPoint()
, m_score(0)
, m_toGoHeuristics(0)
{

}


COSMRoutePoint::COSMRoutePoint(tPtrRoutingPoint originPoint, tWayShPtr originWay, tOSMNodeShPtr geoPoint, double score, double toGoHeuristics)
: m_originRoutingPoint(originPoint)
, m_originWay(originWay)
, m_geoPoint(geoPoint)
, m_score(score)
, m_toGoHeuristics(toGoHeuristics)
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
}

}