#include <COSMModelBuilder.h>
#include <iostream>
#include <COSMNode.h>

using namespace std;

int main( int argc, char** argv)
{
  osmMachine::OSMRoutingNetwork routingNetwork;
  osmMachine::COSMModelBuilder modelBuilder(routingNetwork);
  modelBuilder.ReadOSMData("/home/ibisdev/swietokrzyskie-latest.osm.pbf");
  cout << "Done" << endl;
  while(1) {};
  return 0;
}