add_library( GeoJSON SHARED
    IGeoJSONElement.h
    CGeoJSONUtils.cpp
    CGeoJSONUtils.h
    CGeoJSONFeature.cpp
    CGeoJSONFeature.h
    CGeoJSON.cpp
    CGeoJSON.h
    GeoJSON.h 
    GeoJSONTypes.h
    CGeometry.cpp
    CGeometry.h
    CPointGeometry.cpp
    CPointGeometry.h
    CMultiPointGeometry.cpp
    CMultiPointGeometry.h
    CMultiShapeGeometry.cpp
    CMultiShapeGeometry.h
)

target_link_libraries( GeoJSON PUBLIC GeoBase)
add_dependencies( GeoJSON GeoBase )