#include "COSMNode.h"

namespace osmMachine
{

class CWaySegment
{
public:
  CWaySegment(  tCOSMNodeShPtr beginNode, tCOSMNodeShPtr endNode );
  virtual ~CWaySegment();

  double getLength() const;

  tCOSMNodeShPtr getBeginNode() const;
  tCOSMNodeShPtr getEndNode() const;

private:
  double m_length;

  tCOSMNodeShPtr m_beginNode;
  tCOSMNodeShPtr m_endNode;
};

}