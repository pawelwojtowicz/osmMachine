#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <GeoJSON/CGeoJSONFeature.h>

bool CompareRescaled( const GeoBase::CGeoPoint& p1 , const GeoBase::CGeoPoint& p2 )
{
  int coordsRescaler = 1000000;

  return ( static_cast<int>(p1.getLat()*coordsRescaler) == static_cast<int>(p2.getLat() * coordsRescaler) ) &&
          ( static_cast<int>(p1.getLon()*coordsRescaler) == static_cast<int>(p2.getLon() * coordsRescaler) );
}

TEST( CGeoJSON, Construction_Empty ) 
{
  GeoJSON::CGeoJSONFeature feature;

  EXPECT_FALSE( feature.IsValid() );
  EXPECT_EQ( feature.getType(), GeoJSON::tGeometryType::eInvalid );
}



TEST( CGeoJSON, Construction ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeometryType::ePoint, geometry );

  EXPECT_TRUE( point.IsValid() );
  EXPECT_EQ( point.getType() , GeoJSON::tGeometryType::ePoint );
}

TEST( CGeoJSON, Point_SerializeDeserializeBasic ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeometryType::ePoint, geometry );
  point.AddProperty( "Test", "Property");

  std::string jsonString = point.ToJSON();

  GeoJSON::CGeoJSONFeature pointDeserialized;

  EXPECT_FALSE( pointDeserialized.IsValid() );
  EXPECT_TRUE( pointDeserialized.Parse(jsonString));
  EXPECT_TRUE( pointDeserialized.IsValid() );

  EXPECT_TRUE( CompareRescaled( *point.getGeometry().begin(), *pointDeserialized.getGeometry().begin() ) );
  EXPECT_EQ( point.GetProperty("Test"), pointDeserialized.GetProperty("Test"));
}


TEST( CGeoJSON, MultiPoint_SerializeDeserialize ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeometryType::eMultipoint, geometry );
  point.AddProperty( "Test", "Property");

  std::string jsonString = point.ToJSON();

  GeoJSON::CGeoJSONFeature pointDeserialized;

  EXPECT_FALSE( pointDeserialized.IsValid() );
  EXPECT_TRUE( pointDeserialized.Parse(jsonString));
  EXPECT_TRUE( pointDeserialized.IsValid() );

  auto geometryIter = point.getGeometry().begin();
  auto deserializedGeometryIter = pointDeserialized.getGeometry().begin();
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_EQ( point.GetProperty("Test"), pointDeserialized.GetProperty("Test"));
}

TEST( CGeoJSON, LineString_SerializeDeserialize ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeometryType::eLineString, geometry );
  point.AddProperty( "Test", "Property");

  std::string jsonString = point.ToJSON();

  GeoJSON::CGeoJSONFeature pointDeserialized;

  EXPECT_FALSE( pointDeserialized.IsValid() );
  EXPECT_TRUE( pointDeserialized.Parse(jsonString));
  EXPECT_TRUE( pointDeserialized.IsValid() );

  auto geometryIter = point.getGeometry().begin();
  auto deserializedGeometryIter = pointDeserialized.getGeometry().begin();
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_EQ( point.GetProperty("Test"), pointDeserialized.GetProperty("Test"));
}

TEST( CGeoJSON, Polygon_SerializeDeserialize ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(45.50539065737886 ), DEG2RAD( 10.730993854520705 )));
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(47.68089434017784 ), DEG2RAD( 8.617075451932875 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeometryType::ePolygon, geometry );
  point.AddProperty( "Test", "Property");

  std::string jsonString = point.ToJSON();

  GeoJSON::CGeoJSONFeature pointDeserialized;

  EXPECT_FALSE( pointDeserialized.IsValid() );
  EXPECT_TRUE( pointDeserialized.Parse(jsonString));
  EXPECT_TRUE( pointDeserialized.IsValid() );

  auto geometryIter = point.getGeometry().begin();
  auto deserializedGeometryIter = pointDeserialized.getGeometry().begin();
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_TRUE( CompareRescaled( *(geometryIter++), *(deserializedGeometryIter++) ) );
  EXPECT_EQ( point.GetProperty("Test"), pointDeserialized.GetProperty("Test"));
}
