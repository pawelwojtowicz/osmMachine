#pragma once
#include "OSMCore.h"
#include <CGeoPoint.h>
#include <memory>

namespace osmMachine
{

class COSMNode : public CGeoPoint
{
public:
  COSMNode( const int64_t osmNodeId );
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