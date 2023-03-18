#pragma once
#include <vector>
#include <memory>
#include "COSMNode.h"
#include "CWaySegment.h"
namespace osmMachine
{

class COSMWay
{
  using tWaySegments = std::vector<CWaySegment>;

public:
  COSMWay( const int64_t wayId);
  virtual ~COSMWay();

  void AddWaySegment( const CWaySegment& waySegment );

  void Print();

  void AddProperty( const std::string& key, const std::string& value );

  inline int64_t GetId() const { return m_wayId; } ;

  inline const tWaySegments& GetWaySegments() const { return m_waySegments; };
  
  inline const tOSMNodeShPtr GetBeginNode() const { return m_wayBegin; };

  inline const tOSMNodeShPtr GetEndNode() const { return m_wayEnd; };

private:
  //osm way id
  int64_t m_wayId;

  //the vector of all of the shapepoints
  tWaySegments m_waySegments;

  //the length of the OSM Way is calculated on the basis of all the way segments
  double m_length;

  //storing the TAG properties
  tPropertyMap m_wayProperties;

  tOSMNodeShPtr m_wayBegin;

  tOSMNodeShPtr m_wayEnd;
};

}