#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <GeoJSON/CGeoJSONFeature.h>

TEST( CGeoJSON, Construction_Empty ) 
{
  GeoJSON::CGeoJSONFeature feature;

  EXPECT_FALSE( feature.IsValid() );
  EXPECT_EQ( feature.getType(), GeoJSON::tGeoJsonElementType::eInvalid );
}



TEST( CGeoJSON, Construction ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeoJsonElementType::ePoint, geometry );

  EXPECT_TRUE( point.IsValid() );
  EXPECT_EQ( point.getType() , GeoJSON::tGeoJsonElementType::ePoint );
}

TEST( CGeoJSON, SerializeDeserializeBasic ) 
{
  GeoJSON::tGeometry geometry;
  geometry.push_back( GeoBase::CGeoPoint( DEG2RAD(44.49123846721492 ), DEG2RAD( 12.291511428168814 )));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeoJsonElementType::ePoint, geometry );
  point.AddProperty( "Test", "Property");

  std::string jsonString = point.ToJSON();

  GeoJSON::CGeoJSONFeature newEntry;

  EXPECT_FALSE( newEntry.IsValid() );
  EXPECT_TRUE( newEntry.Parse(jsonString));
  EXPECT_TRUE( newEntry.IsValid() );

  int coordsRescaler = 1000000;

  int geometry1Lat = point.getGeometry().begin()->getLat() * coordsRescaler;
  int geometry1Lon = point.getGeometry().begin()->getLon() * coordsRescaler;
  int geometry2Lat = newEntry.getGeometry().begin()->getLat() * coordsRescaler;
  int geometry2Lon = newEntry.getGeometry().begin()->getLon() * coordsRescaler;

  EXPECT_EQ( geometry1Lat, geometry2Lat);
  EXPECT_EQ( geometry1Lon, geometry2Lon);
  EXPECT_EQ( point.GetProperty("Test"), newEntry.GetProperty("Test"));
}

