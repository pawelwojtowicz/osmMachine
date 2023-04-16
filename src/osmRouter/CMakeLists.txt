add_library( osmRouter SHARED
  COSMRoutingPointSet.cpp 
  COSMRoutingPointSet.h
  COSMRouter.cpp
  COSMRouter.h
  COSMRoutePoint.cpp
  COSMRoutePoint.h
  IOSMRouter.h
  IOSMRoutingUtilityFunction.h
  CSimpleDistanceUtilityFunction.cpp
  CSimpleDistanceUtilityFunction.h
)

target_link_libraries( osmRouter PUBLIC GeoBase osmCore )