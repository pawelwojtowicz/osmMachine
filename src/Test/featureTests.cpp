#include <gtest/gtest.h>
#include <iostream>
#include <GeoJSON/CGeoJSONFeature.h>

TEST( CGeoJSON, Construction ) 
{
  GeoJSON::tGeometry points;
  points.push_back( GeoBase::CGeoPoint( DEG2RAD(123), DEG2RAD(32)));
  GeoJSON::CGeoJSONFeature point(GeoJSON::tGeoJsonElementType::ePoint, points, {} );
  point.AddProperty("Test", "Value");

  std::cout << point.ToJSON() << std::endl;
}


