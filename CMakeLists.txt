cmake_minimum_required(VERSION 3.10)
project( osmMachine VERSION 0.0.1 DESCRIPTION "Open Street Maps toolkit")

set( LOGGER_ENABLED true)

if ( LOGGER_ENABLED )
  add_compile_definitions(WITH_LOGGER)
endif()

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -O3 -fPIC" )
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3 -fPIC" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

add_subdirectory( src/GeoBase )
add_subdirectory( src/GeoJSON )
add_subdirectory( src/GeoZoneMonitor )
add_subdirectory( src/Logger )
add_subdirectory( src/osmCore )
add_subdirectory( src/osmEngine )
add_subdirectory( src/osmReader )
add_subdirectory( src/osmRouter )
add_subdirectory( tests )
add_subdirectory( src/Utils )
