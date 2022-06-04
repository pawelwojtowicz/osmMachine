#include "COSMNode.h"

namespace osmMachine
{

class CWaySegment
{
public:
  CWaySegment(  tOSMNodeShPtr beginNode, tOSMNodeShPtr endNode );
  virtual ~CWaySegment();

  inline double getLength() const { return m_length;};

  tOSMNodeShPtr getBeginNode() const;
  tOSMNodeShPtr getEndNode() const;

private:
  double m_length;

  tOSMNodeShPtr m_beginNode;
  tOSMNodeShPtr m_endNode;
};

}