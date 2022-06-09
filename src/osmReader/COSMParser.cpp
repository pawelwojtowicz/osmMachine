#include "COSMParser.h"
#include <COSMNode.h>
#include <iostream>
#include <iomanip>


namespace osmMachine
{

static const char s_OSMNodeXMLNode[] = { "node" };
static const char s_OSMWayXMLNode[] = { "way" };
static const char s_osmTagXMLNode[] = { "tag"};
static const char s_idXMLPropertyName[] = { "id"};
static const char s_latXmlPropertyName[]  = { "lat"}; 
static const char s_lonXmlPropertyName[]  = { "lon"};
static const char s_keyXmlProperty[] = {"k"};
static const char s_valueXmlProperty[] = {"v"};
static const char s_osmWayNdElement[] = {"nd"};
static const char s_osmWayNdRefPropertyName[] = {"ref"};


COSMParser::COSMParser(IOSMModelBuilder& osmModemBuilder)
: m_xmlDocument()
, m_rootElement(nullptr)
, m_osmModelBuilder(osmModemBuilder)
{

}

COSMParser::~COSMParser()
{

}

bool COSMParser::OpenFile( const std::string& filename )
{
  if (m_xmlDocument.LoadFile( filename ) )
  {
    m_rootElement = m_xmlDocument.RootElement(); 
  }
  return false;
}

bool COSMParser::ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead )
{
  if ( nullptr != m_rootElement )
  {
	  TiXmlHandle hRoot(m_rootElement);

    auto bboxNode = hRoot.FirstChild( "bounds" ).Element();
    if ( nullptr != bboxNode )
    {
      double bottom(0);
      double top(0);
      double left(0);
      double right(0);

      bboxNode->QueryDoubleAttribute("minlat", &bottom);
      bboxNode->QueryDoubleAttribute("minlon", &left);
      bboxNode->QueryDoubleAttribute("maxlat", &top);
      bboxNode->QueryDoubleAttribute("maxlon", &right);

      m_osmModelBuilder.NotifyBoundingBox(left, top, right, bottom);
    }

    if ( eNodes & primitivesToRead )
    {
      auto osmNodeElement(hRoot.FirstChild( s_OSMNodeXMLNode ).Element());
      while ( nullptr != osmNodeElement)
      {
        int osmNodeId(0);
        double lat(0);
        double lon(0);

        osmNodeElement->QueryIntAttribute(s_idXMLPropertyName, &osmNodeId);
        osmNodeElement->QueryDoubleAttribute(s_latXmlPropertyName, &lat);
        osmNodeElement->QueryDoubleAttribute(s_lonXmlPropertyName, &lon);

        tOSMNodeShPtr ptrNode = std::make_shared<COSMNode>(osmNodeId, lat,lon);

        TiXmlHandle nodeHandle(osmNodeElement);
        auto osmTagElement(nodeHandle.FirstChild( s_osmTagXMLNode ).Element());
        while( nullptr !=  osmTagElement )
        {
          std::string key( osmTagElement->Attribute( s_keyXmlProperty ) );
          std::string value ( osmTagElement->Attribute( s_valueXmlProperty ) );
          ptrNode->addOSMNodeProperty(key, value);

          osmTagElement = osmTagElement->NextSiblingElement( s_osmTagXMLNode );
        }

        m_osmModelBuilder.AddNode( ptrNode);
        osmNodeElement = osmNodeElement->NextSiblingElement(  s_OSMNodeXMLNode );
      }
    }

    if ( eWays & primitivesToRead )
    {
      auto osmWayElement(hRoot.FirstChild( s_OSMWayXMLNode ).Element());
      while ( nullptr != osmWayElement )
      {
        TiXmlHandle wayHandle( osmWayElement );
        int wayId(0);

        osmWayElement->QueryIntAttribute(s_idXMLPropertyName, &wayId);

        tWayShPtr ptrWay = std::make_shared<COSMWay>(wayId);

        auto osmTagElement(wayHandle.FirstChild( s_osmTagXMLNode ).Element());
        while( nullptr !=  osmTagElement )
        {
          std::string key( osmTagElement->Attribute( s_keyXmlProperty ) );
          std::string value ( osmTagElement->Attribute( s_valueXmlProperty ) );

          ptrWay->AddProperty(key, value);
          osmTagElement = osmTagElement->NextSiblingElement( s_osmTagXMLNode );
        }

        m_osmModelBuilder.AddWay(ptrWay);

        auto osmWayNdElement(wayHandle.FirstChild( s_osmWayNdElement ).Element());
        while( nullptr !=  osmWayNdElement )
        {
          int osmWayNodeId(0);
          osmWayNdElement->QueryIntAttribute(s_osmWayNdRefPropertyName, &osmWayNodeId);

          m_osmModelBuilder.AddWaypoint( wayId, osmWayNodeId );

          osmWayNdElement = osmWayNdElement->NextSiblingElement( s_osmWayNdElement );
        }
        
        osmWayElement = osmWayElement->NextSiblingElement( s_OSMWayXMLNode );
      }


    }
  }
  return true;
}

}