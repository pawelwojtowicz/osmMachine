cmake_minimum_required(VERSION 3.10)
project( osmMachine VERSION 0.0.1 DESCRIPTION "Open Street Maps toolkit")

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src/GeoBase )

add_subdirectory( src/GeoBase )
add_subdirectory( src/Test )