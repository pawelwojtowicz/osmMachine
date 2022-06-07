#pragma once
#include "IOSMModelBuilder.h"

namespace osmMachine
{

class COSMModelBuilder : public IOSMModelBuilder
{
  using tNodeId2NodeMap = std::map< int64_t , tOSMNodeShPtr>;

  using tWayId2WayMap = std::map< int64_t, tWayShPtr >;
public:
  COSMModelBuilder();
  virtual ~COSMModelBuilder();

  bool ReadOSMData( const std::string& filename);

  void CleanNodes();
private:
  virtual void NotifyBoundingBox( const double left, const double top, const double right, const double bottom ) override;
  virtual void AddNode( tOSMNodeShPtr& ptrNode ) override;
  virtual void AddWay( tWayShPtr& ptrWay ) override;
  virtual void AddWaypoint( const int64_t& wayId, const int64_t& nodeId ) override;


private:
  COSMModelBuilder(const COSMModelBuilder&) = delete;
  COSMModelBuilder& operator=(const COSMModelBuilder&) = delete;

  tNodeId2NodeMap m_id2NodeMap;

  tWayId2WayMap m_id2WayMap;

  tWayShPtr m_currentWay;
  tOSMNodeShPtr m_prevGeoPoint;
};

}