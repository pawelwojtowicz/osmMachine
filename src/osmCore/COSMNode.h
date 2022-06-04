#pragma once
#include <CGeoPoint.h>
#include <memory>
#include <map>

namespace osmMachine
{

class COSMNode : public CGeoPoint
{
  using tPropertyMap = std::map<std::string, std::string>;
public:
  COSMNode( const int osmNodeId, const double lat, const double lon );
  virtual ~COSMNode();

  inline int getId() const { return m_nodeId; };

  void addOSMNodeProperty( const std::string& name, const std::string& value);

  void Print() const;

private:
  int m_nodeId;

  tPropertyMap m_nodeProperties;
};

using tOSMNodeShPtr = std::shared_ptr<COSMNode>;
}