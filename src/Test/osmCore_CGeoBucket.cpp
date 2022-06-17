#include <gtest/gtest.h>
#include <CGeoBucket.h>
#include <algorithm>

using tTestSubject = osmMachine::CGeoBucket<int, int>; 

TEST( osmCore_CGeoBucket , Empty )
{
  tTestSubject::tEntityList expected;

  //initialize the empty test subject
  tTestSubject geoBucket; 

  int index(5);

  auto output = geoBucket.getInArea(index);

  ASSERT_TRUE( std::equal( expected.begin(), expected.end(), output.begin() ) );
}

TEST( osmCore_CGeoBucket , OneElement )
{
  tTestSubject::tEntityList expected = { 1 };

  //initialize the empty test subject
  tTestSubject geoBucket; 

  int index(5);

  geoBucket.addEntityToArea(5, 1 );

  auto output = geoBucket.getInArea(index);

  ASSERT_TRUE( std::equal( expected.begin(), expected.end(), output.begin() ) );
}

TEST( osmCore_CGeoBucket , ThreeElement )
{
  tTestSubject::tEntityList expected = { 3, 2, 100 };

  //initialize the empty test subject
  tTestSubject geoBucket; 

  geoBucket.addEntityToArea(5, 3 );
  geoBucket.addEntityToArea(2, 13 );
  geoBucket.addEntityToArea(5, 2 );
  geoBucket.addEntityToArea(1, 1 );
  geoBucket.addEntityToArea(5, 100 );


  auto output = geoBucket.getInArea(5);

  ASSERT_TRUE( std::equal( expected.begin(), expected.end(), output.begin() ) );
}
