#pragma once
#include <osmCore/COSMNode.h>
#include <osmCore/COSMWay.h>

namespace osmMachine
{
class COSMRoutingPoint;
using tPtrRoutingPoint = std::shared_ptr<COSMRoutingPoint>; 

class COSMRoutePoint
{
public:
  COSMRoutePoint();
  COSMRoutePoint(tPtrRoutingPoint originPoint, tWayShPtr originWay, tOSMNodeShPtr geoPoint, double score, double toGoHeuristics);
  ~COSMRoutePoint();

  void UpdateScore( tPtrRoutingPoint& originPoint, tWayShPtr originWay, double score );

  inline double GetCurrentScore() const { return m_score; };

private:
  tPtrRoutingPoint m_originRoutingPoint;

  tWayShPtr m_originWay;

  tOSMNodeShPtr m_geoPoint;

  /* current value of the utility function */
  double m_score;

  double m_toGoHeuristics;
};

}