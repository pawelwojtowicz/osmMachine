import distHelper
import folium

#initialize the OSM HTML renderer
map = folium.Map(location=[45.504409, 10.731823])

shapeBegin = {}
shapeBegin["lat"] = 45.504503 
shapeBegin["lon"] = 10.731498

shapeEnd = {}
shapeEnd["lat"] = 45.504554 
shapeEnd["lon"] = 10.732161

point= {}
point["lat"] = 45.505391 
point["lon"] = 10.732967

#point["lat"] = 45.504350
#point["lon"] = 10.731823


#put the reference point
#folium.Marker( [point["lat"], point["lon"]], popup=("point"), tooltip= str("POintToProject") ).add_to(map)

result = distHelper.distanceFromShape( point , shapeBegin, shapeEnd)

dist = result["dist"]

points = []
points.append( tuple([shapeBegin["lat"],shapeBegin["lon"] ]))
points.append( tuple([shapeEnd["lat"],shapeEnd["lon"] ]))

folium.PolyLine(points, color="red", weight=2.5, opacity=1).add_to(map)

#folium.Marker( [45.5045266, 10.7318046], popup=("projection"), tooltip= str("Projected") ).add_to(map)

points = []
points.append( tuple([point["lat"],point["lon"] ]))
points.append( tuple([result["lat"],result["lon" ]]))
folium.PolyLine(points, color="blue", weight=2.5, opacity=1).add_to(map)

print( round( result["lon"] * 10000) )
print( round( result["lat"] * 10000 ) )

map.save("offShape2.html") 


