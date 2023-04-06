#pragma once
#include <string>

namespace osmMachine
{

struct OSMConfiguration
{
std::string osmMapFile;

int geoBucketingFactor = { 13 };

int mapMatcherNeighbourhoodSize = { 2 };

int mapMatcherRecomendationSize = { 5 };

double mapMatchingTolerance = { -1 };
};

}