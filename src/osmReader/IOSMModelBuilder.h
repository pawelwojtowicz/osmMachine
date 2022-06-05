#pragma once
#include <COSMNode.h>
#include <COSMWay.h>

namespace osmMachine
{

class IOSMModelBuilder
{
public:
    IOSMModelBuilder() = default;
    virtual ~IOSMModelBuilder() = default;

    virtual void NotifyBoundingBox( const double left, const double top, const double right, const double bottom ) = 0;

    virtual void AddNode( tOSMNodeShPtr& ptrNode ) = 0;

    virtual void AddWay( tWayShPtr& ptrWay ) = 0;
    virtual void AddWaypoint( const int64_t& wayId, const int64_t& nodeId ) = 0;
};

}