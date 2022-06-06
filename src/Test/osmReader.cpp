#include <COSMParser.h>
#include <IOSMModelBuilder.h>
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
    cout << "id=" << wayId <<"-waypoint-" <<  nodeId << endl;
  };



};

int main( int argc, char** argv)
{
  CModelBuilder modelBuilder;
  osmMachine::COSMParser reader(modelBuilder);

  reader.ReadFile("/home/ibisdev/map.osm");
  return 0;
}