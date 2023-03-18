#include <COSMModelBuilder.h>
#include <iostream>
#include <COSMNode.h>

using namespace std;

int main( int argc, char** argv)
{
  osmMachine::COSMModelBuilder modelBuilder;
  modelBuilder.ReadOSMData("mapaZlotoryja.osm");
  return 0;
}