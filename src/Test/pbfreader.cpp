#include <COSMModelBuilder.h>
#include <iostream>
#include <COSMNode.h>

using namespace std;

int main( int argc, char** argv)
{
  osmMachine::COSMModelBuilder modelBuilder;
  modelBuilder.ReadOSMData("/home/ibisdev/swietokrzyskie-latest.osm.pbf");
  cout << "Done" << endl;
  while(1) {};
  return 0;
}