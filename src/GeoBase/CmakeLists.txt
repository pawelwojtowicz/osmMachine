add_library( GeoBase SHARED 
  GeoDefs.h
  CGeoIndex.cpp
  CGeoIndex.h
  CGeoPoint.cpp
  CGeoPoint.h
  GeoUtils.cpp
  GeoUtils.h
  CTileUtils.cpp
  CTileUtils.h
)

target_link_libraries( GeoBase PUBLIC )