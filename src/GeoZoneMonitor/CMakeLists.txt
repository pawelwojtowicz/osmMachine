add_library( GeoZoneMonitor SHARED
  CGeoZoneMonitor.cpp
  CGeoZoneMonitor.h
  IGeoZoneMonitor.h
  CLineIntersectionDetector.cpp 
  CLineIntersectionDetector.h
  CPolylineZoneMonitor.cpp 
  CPolylineZoneMonitor.h
  CSimpleZoneMonitor.cpp
  CSimpleZoneMonitor.h
)

target_link_libraries( GeoZoneMonitor PUBLIC GeoBase )