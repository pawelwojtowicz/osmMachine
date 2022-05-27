find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable( osmMachineTests
  Test_CGeoPoint.cpp
  Test_GeoUtils.cpp )

target_link_libraries(osmMachineTests GeoBase ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread )
add_dependencies( osmMachineTests GeoBase )