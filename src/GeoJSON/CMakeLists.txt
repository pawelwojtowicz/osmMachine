add_library( GeoJSON SHARED
    CGeoJSONFeature.cpp
    CGeoJSONFeature.h
    CGeoJSON.cpp
    CGeoJSON.h
    GeoJSON.h 
    GeoJSONTypes.h
)

target_link_libraries( GeoJSON PUBLIC GeoBase)
add_dependencies( GeoJSON GeoBase )