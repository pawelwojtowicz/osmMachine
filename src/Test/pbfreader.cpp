#include <CPBFReader.h>
#include <COSMModelBuilder.h>
#include <iostream>
#include <COSMNode.h>

using namespace std;

class CModelBuilder : public osmMachine::IOSMModelBuilder
{
public:
  CModelBuilder() 
  {
      
  }
private:
  virtual void NotifyBoundingBox( const double left, const double top, const double right, const double bottom ) override
  {
    cout << "left=" << left << endl << "top="<< top << endl << "right=" << right << endl << "bottm=" << bottom << endl; 
  }

  virtual void AddNode( osmMachine::tOSMNodeShPtr& ptrNode )
  {
    ptrNode->Print();
  }

  virtual void AddWay( osmMachine::tWayShPtr& ptrWay )
  {
    ptrWay->Print();
  }

  virtual void AddWaypoint( const int64_t& wayId, const int64_t& nodeId )
  {

  };



};

int main( int argc, char** argv)
{
  osmMachine::COSMModelBuilder modelBuilder;
  osmMachine::CPBFReader reader(modelBuilder);

  reader.ReadMapFile("/home/ibisdev/swietokrzyskie-latest.osm.pbf", osmMachine::eNodes );
  reader.ReadMapFile("/home/ibisdev/swietokrzyskie-latest.osm.pbf", osmMachine::eWays );
  cout << "Done" << endl;
  modelBuilder.CleanNodes();
  while(1) {};
  return 0;
}