import folium
import distHelper

shapeBegin = {}
shapeBegin["lat"] = 45.504503 
shapeBegin["lon"] = 10.731498

shapeEnd = {}
shapeEnd["lat"] = 45.504554 
shapeEnd["lon"] = 10.732161

e2eDistance = distHelper.twoPointDistR(shapeBegin["lon"],shapeBegin["lat"],shapeEnd["lon"],shapeEnd["lat"])
print(e2eDistance)
position = distHelper.CalculatePointFromBegin( shapeBegin, shapeEnd, 3 )


map = folium.Map(location=[45.504503, 10.731498])

points = []
points.append( tuple([shapeBegin["lat"],shapeBegin["lon"] ]))
points.append( tuple([shapeEnd["lat"],shapeEnd["lon"] ]))
folium.PolyLine(points, color="red", weight=2.5, opacity=1).add_to(map)

points = []
points.append( tuple([shapeBegin["lat"],shapeBegin["lon"] ]))
points.append( tuple([position["lat"],position["lon" ]]))
folium.PolyLine(points, color="blue", weight=2.5, opacity=1).add_to(map)

map.save("pointStuff.html") 
