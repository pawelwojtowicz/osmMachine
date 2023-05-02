#include "CGeometry.h"
#include "CGeoJSONUtils.h"

namespace GeoJSON
{
CGeometry::CGeometry()
: m_geometryType( tGeometryType::eInvalid )
{

}

CGeometry::CGeometry( const tGeometryType type )
: m_geometryType(type)
{

}


CGeometry::~CGeometry()
{

}


const GeoBase::CGeoPoint& CGeometry::GetPoint() const
{
  return {};
}

const tGeometry& CGeometry::GetPoints() const
{
  return {};
}

const tMultiGeometry& CGeometry::GetMultiGeometry() const
{
  return {};
}

bool CGeometry::RebuildFromJSON( const json& jsonTree )
{
  if ( jsonTree.contains( sTxtType ) )
  {
    m_geometryType = CGeoJSONUtils::GeoJSONElementTypeString2EnumType( jsonTree[sTxtType] );
  }
  return ( tGeometryType::eInvalid != m_geometryType ); 
}

json CGeometry::BuildJSONTree()
{
  json geometry ({});

  geometry[sTxtType] = CGeoJSONUtils::GeoJSONElementTypeEnum2String(m_geometryType); 

  return geometry;
}


}
