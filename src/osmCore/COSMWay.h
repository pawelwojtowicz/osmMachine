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
  COSMWay( const int wayId);
  virtual ~COSMWay();

  void AddWaySegment( const CWaySegment& waySegment );

private:
  //osm way id
  int m_wayId;

  //the vector of all of the shapepoints
  tWaySegments m_waySegments;

  //the length of the OSM Way is calculated on the basis of all the way segments
  double m_length;

  //storing the TAG properties
  tPropertyMap m_wayProperties;

  std::shared_ptr<COSMNode> m_wayBegin;

  std::shared_ptr<COSMNode> m_wayEnd;
};

}