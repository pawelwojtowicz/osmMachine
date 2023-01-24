import math

R = 6373000.0

xIdx = "lon"
yIdx = "lat"

def twoPointDistR( lon1, lat1, lon2, lat2):
  dlon = math.radians(lon2) - math.radians(lon1);
  dlat = math.radians(lat2) - math.radians(lat1);
  a = math.sin(dlat / 2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2)**2
  c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
  return R*c

  
def distanceFromLine( xx0, yy0, xx1, yy1, xx2, yy2 ):
  dist = -1
  
  dCosineSquared = math.cos( yy0 )
  dCosineSquared *= dCosineSquared
  
  u0 = dCosineSquared * ( xx0 - xx1 ) * ( xx2 - xx1 ) + ( yy0 - yy1 ) * ( yy2 - yy1 );
  u1 = dCosineSquared * ( xx2 - xx1 ) * ( xx2 - xx1 ) + ( yy2 - yy1 ) * ( yy2 - yy1 );
  
  u = float(-1);

  if u1 != 0:
    u = u0/u1 # u1
  else:
    u = 0  #p1 = p2, line segment is a point
    
  if ( u >= 0.0 and u <= 1.0 ):
    # there is a coinciding location on the line
    rc = 0
    x = xx1 + u * ( xx2 - xx1 )
    y = yy1 + u * ( yy2 - yy1 )
    
    print("lat"+ str(math.degrees(y)) )
    print("lon" + str(math.degrees(x)) )
    dist = twoPointDistR( x, y, xx0, yy0 )
  else:
    # there is no coinciding location on the line
    rc = -8;

    # distance to both end points of line segment p1, p2
    d1  = twoPointDistR( xx1, yy1, xx0, yy0 )
    d2  = twoPointDistR( xx2, yy2, xx0, yy0 )

    if ( d1 < d2 ):
      dist = d1
      x = xx1
      y = yy1
    else:
      dist = d2
      x = xx2
      y = yy2
      
  result = {}
  result["dist"] = dist;
  result["lon"] = math.degrees(x)
  result["lat"] = math.degrees(y)
  
  return result
  
  
def distanceFromShape( point, linePoint1, linePoint2 ):
  x0 = math.radians(point[xIdx])
  y0 = math.radians(point[yIdx])
  x1 = math.radians(linePoint1[xIdx])
  y1 = math.radians(linePoint1[yIdx])
  x2 = math.radians(linePoint2[xIdx])
  y2 = math.radians(linePoint2[yIdx])

  return distanceFromLine( x0,y0,x1,y1,x2,y2 ) 
