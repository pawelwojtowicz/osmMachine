#include <gtest/gtest.h>
#include <osmRouter/COSMRoutingPointSet.h>
#include <osmCore/COSMNode.h>

TEST( COSMRoutingPointSetTest, AddExistsRemoveExists ) 
{
  osmMachine::COSMRoutingPointSet geoPointSet;

  osmMachine::tOSMNodeShPtr geoNode = std::make_shared<osmMachine::COSMNode>(1);

  osmMachine::tPtrRoutingPoint routingPoint1( new osmMachine::COSMRoutePoint({},{},geoNode,0,1) );

  geoPointSet.AddRoutingPoint(routingPoint1);

  ASSERT_TRUE( geoPointSet.Contains(1) );
  ASSERT_TRUE( geoPointSet.NotEmpty() );

  geoPointSet.RemoveRoutingPoint(1);

  ASSERT_FALSE( geoPointSet.Contains(1) );
  ASSERT_FALSE( geoPointSet.NotEmpty() );
}

TEST( COSMRoutingPointSetTest, GetByRoutingPointById ) 
{
  osmMachine::COSMRoutingPointSet geoPointSet;

  for (int i = 0 ; i < 3 ; ++i)
  {
    osmMachine::tOSMNodeShPtr geoNode = std::make_shared<osmMachine::COSMNode>(i);
    osmMachine::tPtrRoutingPoint routingPoint( new osmMachine::COSMRoutePoint({},{},geoNode,i,i) );
    geoPointSet.AddRoutingPoint(routingPoint);
  }

  auto routingPointPtr = geoPointSet.GetRoutingPointById( 2 );

  EXPECT_TRUE( routingPointPtr );
  EXPECT_EQ( routingPointPtr->GetFinalScoreHeuristics(), 4 );

}

TEST( COSMRoutingPointSetTest, GetBestRouting ) 
{
  osmMachine::COSMRoutingPointSet geoPointSet;

  for (int i = 0 ; i < 3 ; ++i)
  {
    osmMachine::tOSMNodeShPtr geoNode = std::make_shared<osmMachine::COSMNode>(i);
    osmMachine::tPtrRoutingPoint routingPoint( new osmMachine::COSMRoutePoint({},{},geoNode,6/(i+1),0) );
    geoPointSet.AddRoutingPoint(routingPoint);
  }


  auto routingPointPtrId2 = geoPointSet.GetBestRoutingPoint();
  EXPECT_EQ( routingPointPtrId2->GetId() , 2 );
  geoPointSet.RemoveRoutingPoint( 2 );

  auto routingPointPtrId1 = geoPointSet.GetBestRoutingPoint();
  EXPECT_EQ( routingPointPtrId1->GetId() , 1 );
  geoPointSet.RemoveRoutingPoint( 1 );

  auto routingPointPtrId0 = geoPointSet.GetBestRoutingPoint();
  EXPECT_EQ( routingPointPtrId0->GetId() , 0 );
  geoPointSet.RemoveRoutingPoint( 0 );

  auto routingPointPtrOut = geoPointSet.GetBestRoutingPoint();
  EXPECT_FALSE( geoPointSet.NotEmpty() );
  EXPECT_FALSE( routingPointPtrOut );
}
