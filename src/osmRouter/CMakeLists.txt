add_library( osmRouter SHARED
  COSMRoutingPointSet.cpp 
  COSMRoutingPointSet.h
  COSMRouter.cpp
  COSMRouter.h
  COSMRoutePoint.cpp
  COSMRoutePoint.h
  IOSMRouter.h
  IRoutingUtilityFunction.h
  IExpectedScoreHeuristics.h
  CSimpleDistanceUtilityFunction.cpp
  CSimpleDistanceUtilityFunction.h
  CSimpleDistanceHeuristics.cpp
  CSimpleDistanceHeuristics.h
)

target_link_libraries( osmRouter PUBLIC GeoBase osmCore )