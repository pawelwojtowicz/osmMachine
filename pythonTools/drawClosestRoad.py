import parseOsm
import distHelper
import xml.etree.ElementTree as ET
import folium


def findClosestWay( point, ways):
  minDist = 0
  wayId = -1
  for id, way in ways.items():
    cursor = 0
    segmentSize = len(way["waypoints"])
    while ( cursor + 1 < segmentSize ):
      dist = distHelper.distanceFromShape( point , way["waypoints"][cursor], way["waypoints"][cursor+1])["dist"]
      if ( ( wayId == -1 ) or ( dist < minDist ) ):
        wayId = id
        minDist = dist
        print ( "wayId="+ str(wayId)+ " "+ str(minDist))
      cursor = cursor + 1
  return wayId

def drawAllRoads( myMap, ways ):
  for id, way in ways.items():
    waySegments = way["waypoints"]
    points = []
    for segment in waySegments:
      points.append( tuple([segment["lat"], segment["lon"]]))
      folium.PolyLine(points, color="blue", weight=2.5, opacity=1).add_to(myMap)

  
#define reference point
refPoint = {}
refPoint["lat"] = 51.121398 
refPoint["lon"] = 15.906612

#read the OSM
ways = parseOsm.initMap()

#find the closes osm shape
wayId = findClosestWay(refPoint,ways)
way = ways.get(wayId)
#extract the shapes for the closest road
waySegments = way["waypoints"]

#get the center of the OSM bounding box
boundingBox = parseOsm.findBoundingBox()
mapCenterLat = (boundingBox["maxlat"] + boundingBox["minlat"])/2
mapCenterLong = (boundingBox["maxlon"] + boundingBox["minlon"])/2

#initialize the OSM HTML renderer
map = folium.Map(location=[mapCenterLat, mapCenterLong])

#put the reference point
folium.Marker( [refPoint["lat"], refPoint["lon"]], popup=("RefPint"), tooltip= str("Testowy") ).add_to(map)

#draw all the roads from the OSM bounding box
drawAllRoads( map, ways)

#draw the closest segment
points = []
for segment in waySegments:
  points.append( tuple([segment["lat"], segment["lon"]]))
folium.PolyLine(points, color="red", weight=2.5, opacity=1).add_to(map)

#close the file
map.save("test.html") 

refPoint1 = {}
refPoint1["lat"] = 51.1550319553372
refPoint1["lon"] = 16.900309450461428

refPoint2 = {}
refPoint2["lat"] = 51.11419090729167
refPoint2["lon"] = 16.846014389863328


print( "------------" + str( distHelper.twoPointDistR( refPoint1["lon"], refPoint1["lat"], refPoint2["lon"], refPoint2["lat"])) )