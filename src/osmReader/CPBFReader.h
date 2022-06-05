#pragma once
#include <string>
#include "IOSMModelBuilder.h"

class Nodes;

namespace osmMachine
{

class CPBFReader
{
public:
    CPBFReader( IOSMModelBuilder& osmModelBuilder);
    virtual ~CPBFReader();

    bool ReadFile( const std::string& fileName );

private:
    IOSMModelBuilder& m_osmModelBuilder;
};
}