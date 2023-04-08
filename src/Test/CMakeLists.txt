find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable( osmMachineTests
  GeoBase_CGeoPoint.cpp
  GeoBase_CGeoUtils.cpp
  GeoBase_CTileUtils.cpp
  GeoBase_BoundingBoxTests.cpp
  osmCore_CGeoBucket.cpp
  tileTestHelper.h
  tileTestHelper.cpp
  )

target_link_libraries(osmMachineTests GeoBase ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread )
add_dependencies( osmMachineTests GeoBase )

add_executable( geoZoneMonitorTests
  CSimpleZoneMonitorTests.cpp
  CPolylineZoneMonitorTests.cpp
  )

target_link_libraries(geoZoneMonitorTests GeoBase GeoZoneMonitor ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread )
add_dependencies( geoZoneMonitorTests GeoBase GeoZoneMonitor)


add_executable( fullStackMatcherTest
   fullStackMatcherTest.cpp)

target_link_libraries(fullStackMatcherTest Logger osmReader osmEngine Utils)
add_dependencies( fullStackMatcherTest Logger osmReader osmEngine Utils)

add_executable( tileSizeTable
  tileSizeTable.cpp
)
target_link_libraries( tileSizeTable GeoBase osmCore)

add_executable( geobucketTuner
  geoBucketTuner.cpp
)
target_link_libraries( geobucketTuner GeoBase osmCore osmReader )