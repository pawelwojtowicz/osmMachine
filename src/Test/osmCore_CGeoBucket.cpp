#include <gtest/gtest.h>
#include <tuple>
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

using tTestParameters = std::tuple<int, int, int, osmMachine::CGeoBucket<int>::tEntitySet>;

class ExtractingValuesFixture : public ::testing::TestWithParam<tTestParameters>
{
public:
  void InitializeGeoBucket( ) 
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

  int _zoomLevel = 15;
  int32_t _xOffset = 100;
  int32_t _yOffset = 100;


  osmMachine::CGeoBucket<int> m_geoBuckets;
};

TEST_P( ExtractingValuesFixture , ReturningObjectsFromAreas )
{
  InitializeGeoBucket(); 
  auto testParameters = GetParam();

  int x = std::get<0>(testParameters);
  int y = std::get<1>(testParameters);
  int radius = std::get<2>(testParameters);
  osmMachine::CGeoBucket<int>::tEntitySet expectedOutput = std::get<3>(testParameters);

  auto latLonPair = returnCenterOfATile( _xOffset + x, _yOffset + y, _zoomLevel);

  osmMachine::CGeoPoint point(DEG2RAD(latLonPair.first), DEG2RAD(latLonPair.second));

  auto geoBucketOutput = m_geoBuckets.getAllAround(point, radius);
  
  EXPECT_TRUE( expectedOutput == geoBucketOutput );
}

INSTANTIATE_TEST_CASE_P(
        GeoBucketTesting , 
        ExtractingValuesFixture,
        ::testing::Values(
                tTestParameters({3, 7, 0, { 74 } } ),
                tTestParameters({3, 7, 1, osmMachine::CGeoBucket<int>::tEntitySet{ 63, 64, 65, 73, 74, 75, 83, 84, 85 } } ),
                tTestParameters({3, 7, 2, osmMachine::CGeoBucket<int>::tEntitySet{ 52, 53, 54, 55, 56, 62, 63, 64, 65, 66, 72, 73, 74, 75, 76, 82, 83, 84, 85, 86, 92, 93, 94, 95, 96} } ),
                tTestParameters({8, 8, 0, osmMachine::CGeoBucket<int>::tEntitySet{ 89 } } ),
                tTestParameters({8, 8, 1, osmMachine::CGeoBucket<int>::tEntitySet{ 78, 79, 80, 88, 89, 90, 98, 99, 100} } ),
                tTestParameters({8, 8, 2, osmMachine::CGeoBucket<int>::tEntitySet{ 67, 68, 69, 70, 77, 78, 79, 80, 87, 88, 89, 90, 97,  98, 99, 100 } } ),
                tTestParameters({-1, -1, 0, osmMachine::CGeoBucket<int>::tEntitySet{ } } ),
                tTestParameters({-1, -1, 1, osmMachine::CGeoBucket<int>::tEntitySet{ 1 } } ),
                tTestParameters({-1, -1, 2, osmMachine::CGeoBucket<int>::tEntitySet{ 1, 2, 11, 12 } } )
        ));