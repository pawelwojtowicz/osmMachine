#pragma once
#include <osmCore/COSMNode.h>
#include <osmCore/COSMWay.h>

namespace osmMachine
{
class COSMRoutePoint;
using tPtrRoutingPoint = std::shared_ptr<COSMRoutePoint>;

class COSMRoutePoint
{
public:
  COSMRoutePoint(tPtrRoutingPoint originPoint, tWayShPtr originWay, tOSMNodeShPtr geoPoint, double score, double toGoHeuristics);
  ~COSMRoutePoint();

  int64_t GetId() { return m_geoPoint->getId(); };

  tWayShPtr GetOriginWay() { return m_originWay;};

  void UpdateScore( tPtrRoutingPoint& originPoint, tWayShPtr originWay, double score );

  inline double GetScore() const { return m_score; };

  inline double GetFinalScoreHeuristics() const { return m_finalScoreHeuristics; };

  inline tPtrRoutingPoint GetPreviousRoutingPoint() const { return m_originRoutingPoint;}; 

private:
  tPtrRoutingPoint m_originRoutingPoint;

  tWayShPtr m_originWay;

  tOSMNodeShPtr m_geoPoint;

  /* current value of the utility function */
  double m_score;

  double m_toGoHeuristics;

  double m_finalScoreHeuristics;
};

}