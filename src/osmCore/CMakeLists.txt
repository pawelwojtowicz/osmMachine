add_library( osmCore SHARED 
  COSMNode.cpp
  COSMNode.h
  COSMWay.cpp
  COSMWay.h
  CWaySegment.cpp
  CWaySegment.h
)

target_link_libraries( osmCore PUBLIC GeoBase )