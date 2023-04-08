#initialize the OSM HTML renderer
import folium

map = folium.Map() #location=[mapCenterLat, mapCenterLong])

 

 

geoZonePoints = []

 

geoZonePoints.append( tuple([51.1497334937856, 17.03222834471153]) )

geoZonePoints.append( tuple([51.14954666823577, 17.03670407222367]) )

geoZonePoints.append( tuple([51.1488253069317, 17.037399009582302]) )

geoZonePoints.append( tuple([51.14855025252997, 17.034619260147778]) )

geoZonePoints.append( tuple([51.147564194976354, 17.034412433552948]) )

geoZonePoints.append( tuple([51.14737217079148, 17.037423828773683]) )

geoZonePoints.append( tuple([51.14711267738047, 17.036728891415052]) )

geoZonePoints.append( tuple([51.14728394319542, 17.032592359518432]) )

geoZonePoints.append( tuple([51.1497334937856, 17.03222834471153]) )

 

folium.PolyLine(geoZonePoints, color="blue", weight=2.5, opacity=1).add_to(map)

 

 

 

folium.Marker( [51.1470, 17.0340], popup=("RefPoint1"), tooltip= str("P1") ).add_to(map)

folium.Marker( [51.1475, 17.0345], popup=("RefPoint2"), tooltip= str("P2") ).add_to(map)

folium.Marker( [51.1478, 17.0350], popup=("RefPoint3"), tooltip= str("P3") ).add_to(map)

folium.Marker( [51.1490, 17.0370], popup=("RefPoint4"), tooltip= str("P4") ).add_to(map)

folium.Marker( [51.1490, 17.0325], popup=("RefPoint5"), tooltip= str("P5") ).add_to(map)

folium.Marker( [51.1480, 17.0315], popup=("RefPoint6"), tooltip= str("P6") ).add_to(map)

folium.Marker( [51.1500, 17.0350], popup=("RefPoint7"), tooltip= str("P7") ).add_to(map)

map.save("GeoZoneMonitorTests.html") 