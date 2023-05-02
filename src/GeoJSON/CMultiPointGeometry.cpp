#include "CMultiPointGeometry.h"

namespace GeoJSON
{
CMultiPointGeometry::CMultiPointGeometry()
: CGeometry()
{

}

CMultiPointGeometry::CMultiPointGeometry( const tGeometryType type, const tGeometry& geometry )
: CGeometry(type)
, m_geometry(geometry)
{

}

CMultiPointGeometry::~CMultiPointGeometry()
{

}

const tGeometry& CMultiPointGeometry::GetPoints() const
{
  return m_geometry;
}

bool CMultiPointGeometry::RebuildFromJSON( const json& jsonTree )
{
  m_geometry.clear();

  if ( CGeometry::RebuildFromJSON(jsonTree) )
  {
    if ( jsonTree.contains( sTxtCoordinates) )
    {
      const auto& coordinates =  jsonTree[sTxtCoordinates];

      for ( const auto& point : coordinates )
      {
        m_geometry.push_back( GeoBase::CGeoPoint(DEG2RAD(point[1].get<double>()) , DEG2RAD(point[0].get<double>())  ));
      }

      return true;
    }
  }

  return false;
}

json CMultiPointGeometry::BuildJSONTree()
{
  json multiPointJSONStructure = CGeometry::BuildJSONTree();
  json jsonCoordinates( json::value_t::array );
  for ( const auto& geoPoint : m_geometry)
  {
    jsonCoordinates.push_back( { RAD2DEG(geoPoint.getLon() ) , RAD2DEG(geoPoint.getLat()) } );
  }
  multiPointJSONStructure[sTxtCoordinates] = jsonCoordinates;

  return multiPointJSONStructure;
}


}