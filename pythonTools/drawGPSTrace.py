import distHelper
import folium
import pandas as pd

LAT = 2
LON = 3
SPD = 7
ALT = 5
ACC = 4

filename = "20230120-190416.txt"

gpsTraceData = pd.read_csv(filename)


mapCenterLat = gpsTraceData['latitude'].mean()
mapCenterLon = gpsTraceData['longitude'].mean()
#initialize the OSM HTML renderer
map = folium.Map(location=[mapCenterLat, mapCenterLon])

prevGeoPoint = None

for index, geoPoint in gpsTraceData.iterrows():
    text = "spd=" + str(geoPoint['speed(m/s)'])

    print(index)
#    if ( prevGeoPoint != None):
#      print ("temp")
#      distToPrev = distHelper.twoPointDistR(prevGeoPoint['longitude'],prevGeoPoint['latitude'],
#                                            geoPoint['longitude'],geoPoint['latitude']
#                                           )
 #     print ("temp")
 #     text += " dd=" + str(distToPrev)
    prevGeoPoint = geoPoint
    folium.Marker( [geoPoint['latitude'], geoPoint['longitude']], popup=(str(index)), tooltip= text ).add_to(map)

map.save("gpsTrace.html") 