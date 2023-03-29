#include <gtest/gtest.h>
#include "tileTestHelper.h"
#include <CGeoBucket.h>
#include <algorithm>

//using testing::_;


/**      0  1  2  3  4  5  6  7  8  9
 *    + -----------------------------
 *  0 | 01 02 03 04 05 06 07 08 09 10 
 *  1 | 11 12 13 14 15 16 17 18 19 20
 *  2 | 21 22 23 24 25 26 27 28 29 30
 *  3 | 31 32 33 34 35 36 37 38 39 40
 *  4 | 41 42 43 44 45 46 47 48 49 50
 *  5 | 51 52 53 54 55 56 57 58 59 60
 *  6 | 61 62 63 64 65 66 67 68 69 70
 *  7 | 71 72 73 74 75 76 77 78 79 80
 *  8 | 81 82 83 84 85 86 87 88 89 90
 *  9 | 91 92 93 94 95 96 97 98 99 100
 * 
*/

class GeoBucketTesting : public ::testing::Test
{
public:
  void SetUp( ) 
  {
    m_geoBuckets.Initialize(_zoomLevel);

    int geoIndexedEntity = 0;

    for ( int y = 0 ; y < 10 ; ++y)
    {
      for (int x = 0 ; x < 10 ; ++x )
      {
        ++geoIndexedEntity;
        auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

        osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
        m_geoBuckets.addEntityToArea( point , geoIndexedEntity);
      }
    }

  }

  void TearDown( )
  { 
  }

  int _zoomLevel = 15;
  int32_t _xOffset = 100;
  int32_t _yOffset = 100;


  osmMachine::CGeoBucket<int> m_geoBuckets;

};

TEST_F( GeoBucketTesting , Basic_GetCompleteArea_Radius_0 )
{

  int x = 3;
  int y = 7;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));

  auto geoBucketOutput = m_geoBuckets.getAllAround(point);

  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 74 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_GetCompleteArea_Radius_1 )
{

  int x = 3;
  int y = 7;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 1);

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 63, 64, 65, 73, 74, 75, 83, 84, 85 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_GetCompleteArea_Radius_2 )
{
  int x = 3;
  int y = 7;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 2);
  geoBucketOutput.sort() ;

  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 52, 53, 54, 55, 56, 62, 63, 64, 65, 66, 72, 73, 74, 75, 76, 82, 83, 84, 85, 86, 92, 93, 94, 95, 96 };

  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_GetAreaInDaCorner_Radius_0 )
{

  int x = 8;
  int y = 8;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 0);

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 89 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_GetAreaInDaCorner_Radius_1 )
{

  int x = 8;
  int y = 8;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 1);

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 78, 79, 80, 88, 89, 90, 98, 99, 100 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_GetAreaInDaCorner_Radius_2 )
{

  int x = 8;
  int y = 8;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 2);

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = {67, 68, 69, 70, 77, 78, 79, 80, 87, 88, 89, 90, 97,  98, 99, 100 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_CenterOutOfArea_Radius_0 )
{

  int x = -1;
  int y = -1;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 0 );

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_CenterOutOfArea_Radius_1 )
{

  int x = -1;
  int y = -1;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 1 );

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 1 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}

TEST_F( GeoBucketTesting , Basic_CenterOutOfArea_Radius_2 )
{

  int x = -1;
  int y = -1;
  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));
  auto geoBucketOutput = m_geoBuckets.getAllAround(point, 2 );

  geoBucketOutput.sort() ;
  osmMachine::CGeoBucket<int>::tEntityList expectedOutput = { 1, 2, 11, 12 };
  
  EXPECT_TRUE( std::equal(  expectedOutput.begin(), expectedOutput.end(), 
                            geoBucketOutput.begin(), geoBucketOutput.end()) );
}