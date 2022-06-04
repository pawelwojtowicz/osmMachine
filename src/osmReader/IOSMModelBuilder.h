#pragma once
#include <COSMNode.h>

namespace osmMachine
{

class IOSMModelBuilder
{
public:
    IOSMModelBuilder() = default;
    virtual ~IOSMModelBuilder() = default;

    virtual void NotifyBoundingBox( const double left, const double top, const double right, const double bottom ) = 0;

    virtual void AddNode( tOSMNodeShPtr& ptrNode ) = 0;


};

}