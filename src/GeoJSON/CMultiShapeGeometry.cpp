#include "CMultiShapeGeometry.h"

namespace GeoJSON
{
CMultiShapeGeometry::CMultiShapeGeometry()
: CGeometry()
{

}

CMultiShapeGeometry::CMultiShapeGeometry( const tGeometryType type, const tMultiGeometry& geometry )
: CGeometry(type)
, m_geometry(geometry)
{

}

CMultiShapeGeometry::~CMultiShapeGeometry()
{

}

const tMultiGeometry& CMultiShapeGeometry::GetMultiGeometry() const
{
  return m_geometry;
}

bool CMultiShapeGeometry::RebuildFromJSON( const json& jsonTree )
{
  m_geometry.clear();

  if ( CGeometry::RebuildFromJSON(jsonTree) )
  {
    if ( jsonTree.contains( sTxtCoordinates) )
    {
      const auto& coordinates =  jsonTree[sTxtCoordinates];
      for ( const auto& shapePoints : coordinates )
      {
        tGeometry geometryPoints;
        for ( const auto& point : shapePoints)
        {
          geometryPoints.push_back( GeoBase::CGeoPoint(DEG2RAD(point[1].get<double>()) , DEG2RAD(point[0].get<double>()) ));
        }      
        m_geometry.push_back(geometryPoints);
      }
      return true;
    }
  }

  return false;
}

json CMultiShapeGeometry::BuildJSONTree()
{
  json multiPointJSONStructure = CGeometry::BuildJSONTree();
  json jsonCoordinates( json::value_t::array );
  for ( const auto& shape : m_geometry)
  {
    json shapeJsonArray(json::value_t::array );
    for ( const auto& geoPoint : shape)
    {
      shapeJsonArray.push_back( { RAD2DEG(geoPoint.getLon() ), RAD2DEG(geoPoint.getLat()) } );
    }
    jsonCoordinates.push_back(shapeJsonArray);
  }
  multiPointJSONStructure[sTxtCoordinates] = jsonCoordinates;

  return multiPointJSONStructure;
}


}