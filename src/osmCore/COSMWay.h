#pragma once
#include <vector>
#include <map>
#include <memory>
#include "COSMNode.h"
#include "CWaySegment.h"
namespace osmMachine
{

class COSMWay
{
  using tWaySegments = std::vector<CWaySegment>;
  using tPropertyMap = std::map<std::string, std::string>;
public:
  COSMWay( const int64_t wayId);
  virtual ~COSMWay();

  void AddWaySegment( const CWaySegment& waySegment );

  void Print();

  void AddProperty( const std::string& key, const std::string& value );

  inline int64_t GetId() const { return m_wayId; } ;

private:
  //osm way id
  int64_t m_wayId;

  //the vector of all of the shapepoints
  tWaySegments m_waySegments;

  //the length of the OSM Way is calculated on the basis of all the way segments
  double m_length;

  //storing the TAG properties
  tPropertyMap m_wayProperties;

  std::shared_ptr<COSMNode> m_wayBegin;

  std::shared_ptr<COSMNode> m_wayEnd;
};

using tWayShPtr = std::shared_ptr<COSMWay>;

}