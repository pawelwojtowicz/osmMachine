#pragma once
#include <string>

namespace osmMachine
{

struct OSMConfiguration
{
std::string osmMapFile;

int geoBucketingFactor;

int mapMatcherNeighbourhoodSize;
};

}