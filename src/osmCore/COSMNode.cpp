#include "COSMNode.h"
#include <iostream>
#include <iomanip>

namespace osmMachine
{
COSMNode::COSMNode( const int64_t osmNodeId )
: CGeoPoint( )
, m_nodeId( osmNodeId )
{

}


COSMNode::COSMNode( const int64_t osmNodeId, const double lat, const double lon )
: CGeoPoint( lat, lon )
, m_nodeId( osmNodeId )
{
}

COSMNode::~COSMNode()
{

}

void COSMNode::addOSMNodeProperty( const std::string& name, const std::string& value)
{
  m_nodeProperties.insert( tPropertyMap::value_type( name, value ));
}

void COSMNode::Print() const
{
  std::cout << m_nodeId << " - lat/lon=" << std::setprecision(9) << RAD2DEG(getLat()) << "/" << RAD2DEG(getLon()) << std::endl;
}


};
