#pragma once
#include <CGeoPoint.h>
#include <memory>

namespace osmMachine
{

class COSMNode : public CGeoPoint
{
public:
  COSMNode( const int osmNodeId, const double lat, const double lon );
  virtual ~COSMNode();

  inline int getId() const { return m_nodeId; };

private:
  int m_nodeId;
};

using tCOSMNodeShPtr = std::shared_ptr<COSMNode>;
}