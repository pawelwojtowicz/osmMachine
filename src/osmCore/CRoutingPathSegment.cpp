#include "CRoutingPathSegment.h"

namespace osmMachine
{
CRoutingPathSegment::CRoutingPathSegment( tWayShPtr osmWay, bool consistent )
: m_osmWay(osmWay)
, m_pathDirection( consistent ? tPathSegmentDirection::eConsistent : tPathSegmentDirection::eOpposite)
{

}

CRoutingPathSegment::~CRoutingPathSegment()
{

}


  
}