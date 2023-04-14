#pragma once
#include <string>
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
  using tPropertyMap = std::map<std::string, std::string>;

  COSMWay( const int64_t wayId);
  virtual ~COSMWay();

  void MarkNotUsed();

  void AddWaySegment( const CWaySegment& waySegment );

  void Print();

  void AddProperty( const std::string& key, const std::string& value );

  inline int64_t GetId() const { return m_wayId; } ;

  inline bool IsUsed() const { return m_isUsed; };

  inline bool IsOneWay() const { return m_isOneWay; };

  inline const tWaySegments& GetWaySegments() const { return m_waySegments; };
  
  inline const tOSMNodeShPtr GetBeginNode() const { return m_wayBegin; } ;

  inline const tOSMNodeShPtr GetEndNode() const { return m_wayEnd; } ;

  inline const tPropertyMap GetProperties() const { return m_wayProperties; };

private:
  //osm way id
  int64_t m_wayId;

  // should this way be used in the map matching, routing algorithms?
  bool m_isUsed;

  // the way can be enter only from the beginning.
  bool m_isOneWay;

  //the vector of all of the shapepoints
  tWaySegments m_waySegments;

  //the length of the OSM Way is calculated on the basis of all the way segments
  double m_length;

  //storing the TAG properties
  tPropertyMap m_wayProperties;

  tOSMNodeShPtr m_wayBegin;

  tOSMNodeShPtr m_wayEnd;
};

using tWayShPtr = std::shared_ptr<COSMWay>;

}