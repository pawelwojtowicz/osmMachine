import folium
#initialize the OSM HTML renderer

map = folium.Map(location=[51.1497, 17.0322])

 

 

geoZonePoints = []
geoZonePoints.append( tuple([51.1490, 17.0307]) )
geoZonePoints.append( tuple([51.1499, 17.0307]) )
folium.PolyLine(geoZonePoints, color="blue", weight=2.5, opacity=1).add_to(map)

geoZonePoints = []
geoZonePoints.append( tuple([51.1497, 17.0332]) )
geoZonePoints.append( tuple([51.1500, 17.0332]) )
folium.PolyLine(geoZonePoints, color="green", weight=2.5, opacity=1).add_to(map)

geoZonePoints = []
geoZonePoints.append( tuple([51.1493, 17.0372]) )
geoZonePoints.append( tuple([51.1499, 17.0372]) )
folium.PolyLine(geoZonePoints, color="yellow", weight=2.5, opacity=1).add_to(map)



geoZonePoints = [] 
geoZonePoints.append( tuple([51.1496, 17.0322]) )
geoZonePoints.append( tuple([51.1496, 17.1367]) )
folium.PolyLine(geoZonePoints, color="red", weight=2.5, opacity=1).add_to(map)
 

map.save("lineIntersection-Vertical.html") 