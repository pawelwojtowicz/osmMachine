#include <OSMRoutingNetwork.h>
#include <COSMModelBuilder.h>
#include <iostream>
#include <COSMNode.h>

using namespace std;

int main( int argc, char** argv)
{
  osmMachine::OSMRoutingNetwork routingNetwork;
  osmMachine::COSMModelBuilder modelBuilder(routingNetwork);
  modelBuilder.ReadOSMData("mapaZlotoryja.osm");
  return 0;
}