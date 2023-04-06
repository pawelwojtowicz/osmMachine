cmake_minimum_required(VERSION 3.10)
project( osmMachine VERSION 0.0.1 DESCRIPTION "Open Street Maps toolkit")

set( LOGGER_ENABLED true)

if ( LOGGER_ENABLED )
  add_compile_definitions(WITH_LOGGER)
endif()

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src )

add_subdirectory( src/GeoBase )
add_subdirectory( src/GeoZoneMonitor )
add_subdirectory( src/Logger )
add_subdirectory( src/osmCore )
add_subdirectory( src/osmEngine )
add_subdirectory( src/osmReader )
add_subdirectory( src/Test )
add_subdirectory( src/Utils )
