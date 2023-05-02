#include "CPointGeometry.h"

namespace GeoJSON
{
CPointGeometry::CPointGeometry()
: CGeometry()
{

}

CPointGeometry::CPointGeometry( const GeoBase::CGeoPoint& point)
: CGeometry( tGeometryType::ePoint)
, m_point(point)
{

}


const GeoBase::CGeoPoint& CPointGeometry::GetPoint() const
{
  return m_point;
}

bool CPointGeometry::RebuildFromJSON( const json& jsonTree )
{
  if ( CGeometry::RebuildFromJSON(jsonTree) )
  {
    if (jsonTree.contains( sTxtCoordinates ) )
    {
      const auto& coordinates = jsonTree[sTxtCoordinates];
      m_point = GeoBase::CGeoPoint( GeoBase::CGeoPoint(DEG2RAD(coordinates[0].get<double>()), DEG2RAD(coordinates[1].get<double>())));
      return true;
    }
  }
  return false;
}

json CPointGeometry::BuildJSONTree()
{
  json pointJSONStructure = CGeometry::BuildJSONTree();
  json jsonCoordinates( { RAD2DEG( m_point.getLat() ), RAD2DEG( m_point.getLon() ) } );
  pointJSONStructure[sTxtCoordinates] = jsonCoordinates;

  return pointJSONStructure;
}


}