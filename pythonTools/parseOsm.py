import xml.etree.ElementTree as ET

def isOfInterest( highwayType ):
  if ( "motorway" == highwayType or "trunk" == highwayType or "primary" == highwayType or "secondary" == highwayType or "tertiary" == highwayType or "residential" == highwayType or "motorway_link" == highwayType or "trunk_link" == highwayType or "primary_link" == highwayType or "secondary_link" == highwayType or "tertiary_link" == highwayType or "give_way" == highwayType):
    return True
  return False

def findBoundingBox( ):
  mapTree = ET.parse('mapData/map.osm')
  myroot = mapTree.getroot()

  #<bounds minlat="51.1154400" minlon="15.9002400" maxlat="51.1213000" maxlon="15.9170900"/>
  boundBoxNode = myroot.find('bounds')
  boundingBox = {}  
  boundingBox["minlat"] = float(boundBoxNode.get('minlat'))
  boundingBox["minlon"] = float(boundBoxNode.get('minlon'))
  boundingBox["maxlat"] = float(boundBoxNode.get('maxlat'))
  boundingBox["maxlon"] = float(boundBoxNode.get('maxlon'))
  return boundingBox
  
def readNodes( root ):
  nodes = {}
  for node in root.findall('node'):
    point = {}
    point["lat"] = float( node.get('lat') )
    point["lon"] = float( node.get('lon') )
    nodes[int( node.get('id') ) ] = point
  return nodes
  
def readWays( root, nodes ):
  ways = {}
  for way in root.findall('way'):
    roadSegment = {}
    waypoints = []
    for tag in way.findall('tag'):
      key = tag.get('k')
      value = tag.get('v')
      if ( ( key == "highway" ) and ( isOfInterest(value) ) ):
        for segment in way.findall('nd'):
          ndId = int( segment.get('ref') )
          waypoints.append( nodes.get( ndId ) )
        roadSegment["waypoints"] = waypoints
        wayId = int( way.get("id") )
        roadSegment["id"] = wayId
        ways[wayId] = roadSegment
  
  return ways  

def initMap():
  mapTree = ET.parse('mapData/map.osm')
  myroot = mapTree.getroot()
  nodes = readNodes(myroot)
  ways = readWays(myroot,nodes)
  return ways
