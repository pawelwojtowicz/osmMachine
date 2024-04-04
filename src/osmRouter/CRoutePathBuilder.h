#pragma once
#include "COSMRoutePoint.h"
#include <osmCore/CShapePoint.h>
#include <osmCore/COSMPosition.h>


namespace osmMachine
{

class CRoutePathBuilder
{
public:
  static void ConvertEntryToBegin( const COSMPosition& originOsmPosition, tOSMShapePath& path);
  static void ConvertEntryToEnd( const COSMPosition& originOsmPosition , tOSMShapePath& path );

  static void ConvertWayFromBegin2End( tPtrRoutingPoint& routingSegment, tOSMShapePath& path );
  static void ConvertWayFromEnd2Begin( tPtrRoutingPoint& routingSegment, tOSMShapePath& path );

  static void ConvertExitFromBegin( const COSMPosition& destinationOsmPosition , tOSMShapePath& path );
  static void ConvertExitFromEnd( const COSMPosition& destinationOsmPosition ,tOSMShapePath& path );
};

}