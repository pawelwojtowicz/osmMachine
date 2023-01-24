import distHelper
import folium
import math
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

prevLat = 0
prevLon = 0

distDriven = 0
error = 0

for index, geoPoint in gpsTraceData.iterrows():
    text = "spd=" + str(geoPoint['speed(m/s)'])
    if prevLat != 0:
      distToPrev = distHelper.twoPointDistR(prevLon,prevLat,
                                          geoPoint['longitude'],geoPoint['latitude'])
      distDriven = distDriven + distToPrev;
      error = error + abs(geoPoint['speed(m/s)'] - distToPrev)
      text += " dd=" + str(distToPrev) + "d=" + str(geoPoint['speed(m/s)'] - distToPrev)
    prevLon = geoPoint['longitude']
    prevLat = geoPoint['latitude']

    folium.Marker( [geoPoint['latitude'], geoPoint['longitude']], popup=(str(index)), tooltip= text ).add_to(map)

map.save("gpsTrace.html") 

print( "Driven distance =" + str(distDriven)+ "m")
print( "Error during the driving=" + str(error) + "m, in percent:" + str((error/distDriven)*100))