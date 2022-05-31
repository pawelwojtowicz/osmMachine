#pragma once
#include <string>

namespace osmMachine
{
class CPBFReader
{
public:
CPBFReader();
virtual ~CPBFReader();

bool ReadFile( const std::string& fileName );

};
}