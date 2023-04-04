add_library( osmEngine SHARED
    COSMEngine.cpp
    COSMEngine.h
    COSMMapMatcher.cpp
    COSMMapMatcher.h
    COSMPosition.cpp
    COSMPosition.h
    OSMConfiguration.h
)

target_link_libraries( osmEngine PUBLIC osmCore osmReader Logger)