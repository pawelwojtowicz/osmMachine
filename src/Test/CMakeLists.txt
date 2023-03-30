find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable( osmMachineTests
  GeoBase_CGeoPoint.cpp
  GeoBase_CGeoUtils.cpp
  GeoBase_CTileUtils.cpp
  osmCore_CGeoBucket.cpp
  tileTestHelper.h
  tileTestHelper.cpp
  )

target_link_libraries(osmMachineTests GeoBase ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread )
add_dependencies( osmMachineTests GeoBase )

add_executable( pbfReader
  pbfreader.cpp)

target_link_libraries(pbfReader osmReader )
add_dependencies( pbfReader osmReader )


add_executable( osmParser
  osmReader.cpp)

target_link_libraries(osmParser osmReader )
add_dependencies( osmParser osmReader )

add_executable( tileSizeTable
  tileSizeTable.cpp
)
target_link_libraries( tileSizeTable GeoBase osmCore)

add_executable( geobucketTuner
  geoBucketTuner.cpp
)
target_link_libraries( geobucketTuner GeoBase osmCore osmReader )