#pragma once
#include "IOSMModelBuilder.h"
#include <OSMRoutingNetwork.h>

namespace osmMachine
{

class COSMModelBuilder : public IOSMModelBuilder
{
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

  tWayShPtr AddHelperWay( int64_t masterWayId, const tPropertyMap& properties );

  void BuildRoutingNetwork();
  void addWayToNodeRecord( const int64_t& nodeId, tWayShPtr wayPtr );


private:
  COSMModelBuilder(const COSMModelBuilder&) = delete;
  COSMModelBuilder& operator=(const COSMModelBuilder&) = delete;

  OSMRoutingNetwork m_routingNetwork;

  tNodeId2WayListsMap m_node2wayListsMap;

  tWayShPtr m_currentWay;
  tOSMNodeShPtr m_prevGeoPoint;

  int64_t m_helperWayId;
};

}