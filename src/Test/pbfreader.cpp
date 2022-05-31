#include <CPBFReader.h>

int main( char** argv, int argc)
{
    osmMachine::CPBFReader reader;

    reader.ReadFile("/home/ibisdev/dolnoslaskie-latest.osm.pbf");
    return 0;
}