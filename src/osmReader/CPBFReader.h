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
    void ExtractNodes( const Nodes& nodes, const int64_t& latOffset, const int64_t& lonOffset, const int64_t&granularity );

private:
    IOSMModelBuilder& m_osmModelBuilder;
};
}