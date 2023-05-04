#include <gtest/gtest.h>
#include <GeoJSON/CPointGeometry.h>
#include <GeoJSON/CMultiPointGeometry.h>
#include <GeoJSON/CMultiShapeGeometry.h>

bool RescaleAndCompare( const GeoBase::CGeoPoint& p1 , const GeoBase::CGeoPoint& p2 )
{
  int coordsRescaler = 1000000;

  return ( static_cast<int>(p1.getLat()*coordsRescaler) == static_cast<int>(p2.getLat() * coordsRescaler) ) &&
          ( static_cast<int>(p1.getLon()*coordsRescaler) == static_cast<int>(p2.getLon() * coordsRescaler) );
}


TEST( GeoJSON_GeometryTests, CPointGeometry ) 
{
  GeoJSON::CPointGeometry point( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )) );

  json pointJsonTree = point.BuildJSONTree();

  GeoJSON::CPointGeometry deserializedPoint;

  deserializedPoint.RebuildFromJSON(pointJsonTree);

  EXPECT_EQ( point.GetType() , deserializedPoint.GetType() );
  EXPECT_TRUE( RescaleAndCompare(point.GetPoint(), deserializedPoint.GetPoint() ) );
}

TEST( GeoJSON_GeometryTests, CMultiPointGeometry ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));

  GeoJSON::CMultiPointGeometry multipointGeometry( GeoJSON::tGeometryType::eLineString, geometry);

  json jsonTree = multipointGeometry.BuildJSONTree();
  GeoJSON::CMultiPointGeometry deserializedMultiPointGeometry;

  EXPECT_TRUE(deserializedMultiPointGeometry.RebuildFromJSON(jsonTree) );
  EXPECT_EQ( multipointGeometry.GetType() , deserializedMultiPointGeometry.GetType() );

  auto geometryIter = multipointGeometry.GetPoints().begin();
  auto deserializedGeometryIter = deserializedMultiPointGeometry.GetPoints().begin();

  EXPECT_TRUE( RescaleAndCompare( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );
}

TEST( GeoJSON_GeometryTests, CMultiShapeGeometry ) 
{
  GeoJSON::tMultiGeometry multigeometry;
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));
  multigeometry.push_back(geometry);

  geometry.clear();

  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  multigeometry.push_back(geometry);


  GeoJSON::CMultiShapeGeometry multiShapeGeometry( GeoJSON::tGeometryType::ePolygon, multigeometry);

  json jsonTree = multiShapeGeometry.BuildJSONTree();
  GeoJSON::CMultiShapeGeometry deserializedMultiShapeGeometry;

  EXPECT_TRUE(deserializedMultiShapeGeometry.RebuildFromJSON(jsonTree) );
  EXPECT_EQ( multiShapeGeometry.GetType() , deserializedMultiShapeGeometry.GetType() );

  auto multiGeometryIter = multiShapeGeometry.GetMultiGeometry().begin();
  auto deserializedMultiGeometryIter = deserializedMultiShapeGeometry.GetMultiGeometry().begin();

  auto geometryIter = (*multiGeometryIter++).begin();
  auto deserializedGeometryIter = (*deserializedMultiGeometryIter++).begin();

  EXPECT_TRUE( RescaleAndCompare( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );

  geometryIter = (*multiGeometryIter).begin();
  deserializedGeometryIter = (*deserializedMultiGeometryIter).begin();

  EXPECT_TRUE( RescaleAndCompare( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( RescaleAndCompare(*(geometryIter++), *(deserializedGeometryIter++) ) );

}
