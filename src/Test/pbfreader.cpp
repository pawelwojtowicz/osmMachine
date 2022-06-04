#include <CPBFReader.h>
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

};

int main( int argc, char** argv)
{
    CModelBuilder modelBuilder;
    osmMachine::CPBFReader reader(modelBuilder);

    reader.ReadFile("/home/ibisdev/swietokrzyskie-latest.osm.pbf");
    return 0;
}