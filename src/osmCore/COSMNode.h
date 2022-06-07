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
  COSMNode( const int64_t osmNodeId, const double lat, const double lon );
  virtual ~COSMNode();

  inline int64_t getId() const { return m_nodeId; };

  void addOSMNodeProperty( const std::string& name, const std::string& value);

  void Print() const;

private:
  int64_t m_nodeId;

  tPropertyMap m_nodeProperties;
};

using tOSMNodeShPtr = std::shared_ptr<COSMNode>;
}