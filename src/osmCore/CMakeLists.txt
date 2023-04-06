add_library( osmCore SHARED 
  CGPSPosition.cpp
  CGPSPosition.h
  COSMNode.cpp
  COSMNode.h
  COSMWay.cpp
  COSMWay.h
  CWaySegment.cpp
  CWaySegment.h
  OSMRoutingNetwork.h
)

target_link_libraries( osmCore PUBLIC GeoBase )