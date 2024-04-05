#include "COSMNode.h"

namespace osmMachine
{

class CWaySegment
{
public:
  CWaySegment(  tOSMNodeShPtr beginNode, tOSMNodeShPtr endNode );
  virtual ~CWaySegment();

  void UpdateGeometry();

  inline double getLength() const { return m_length;};
  inline int getHeading() const { return m_heading;};


  tOSMNodeShPtr getBeginNode() const;
  tOSMNodeShPtr getEndNode() const;

private:
  double m_length;

  int m_heading;

  tOSMNodeShPtr m_beginNode;
  tOSMNodeShPtr m_endNode;
};

}