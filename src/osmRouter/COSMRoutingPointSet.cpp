#include "COSMRoutingPointSet.h"

namespace osmMachine
{
COSMRoutingPointSet::COSMRoutingPointSet()
{

}
COSMRoutingPointSet::~COSMRoutingPointSet()
{

}

bool COSMRoutingPointSet::NotEmpty()
{
  return false;
}

void COSMRoutingPointSet::AddRoutingPoint( tPtrRoutingPoint)
{

}

bool COSMRoutingPointSet::Contains( const int64_t routingPointId )
{

  return false;
}

tPtrRoutingPoint COSMRoutingPointSet::GetBestRoutingPoint()
{

  return {};
}

tPtrRoutingPoint GetRoutingPointById( const int64_t routingPointId)
{
  return {};
}

void COSMRoutingPointSet::RemoveRoutingPoint( const int64_t routingPointId )
{
}

}
