add_library( osmRouter SHARED
  COSMRouter.cpp
  COSMRouter.h
  COSMRoutePoint.cpp
  COSMRoutePoint.h
  IOSMRouter.h
)

target_link_libraries( osmRouter PUBLIC GeoBase osmCore )