#include "COSMNOde.h"

namespace osmMachine
{

COSMNode::COSMNode( const int osmNodeId, const double lat, const double lon )
: CGeoPoint( lat, lon )
, m_nodeId( osmNodeId )
{

}

COSMNode::~COSMNode()
{

}

};
