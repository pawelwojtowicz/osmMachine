#include "COSMModelBuilder.h"
#include "CPBFReader.h"
#include "COSMParser.h"
#include "COSMNetworkValidator.h"
#include <iostream>
#include <algorithm>

namespace osmMachine
{

static const std::string osmFilenamePostfix(".osm");
static const std::string pbfFilenamePostfix(".osm.pbf");

COSMModelBuilder::COSMModelBuilder()
{

}
COSMModelBuilder::~COSMModelBuilder()
{

}

bool COSMModelBuilder::ReadOSMData( const std::string& filename)
{
  std::unique_ptr<COSMMapFileReader> mapReader;

  if ( std::equal( osmFilenamePostfix.rbegin(), osmFilenamePostfix.rend(), filename.rbegin() ) )
  {
    mapReader = std::make_unique<COSMParser>(*this);
  } 
  else if ( std::equal( pbfFilenamePostfix.rbegin(), pbfFilenamePostfix.rend(), filename.rbegin() ) )
  {
    mapReader = std::make_unique<CPBFReader>(*this);
  }

  if (mapReader)
  {
    COSMMapFileReader::tFilterSettings wayFilterSettings;

    //https://wiki.openstreetmap.org/wiki/Key:highway
    wayFilterSettings.push_back( std::make_pair("highway", "motorway"));
    wayFilterSettings.push_back( std::make_pair("highway", "trunk"));
    wayFilterSettings.push_back( std::make_pair("highway", "primary"));
    wayFilterSettings.push_back( std::make_pair("highway", "secondary"));
    wayFilterSettings.push_back( std::make_pair("highway", "tertiary"));
    wayFilterSettings.push_back( std::make_pair("highway", "residential"));
    wayFilterSettings.push_back( std::make_pair("highway", "motorway_link"));
    wayFilterSettings.push_back( std::make_pair("highway", "trunk_link"));
    wayFilterSettings.push_back( std::make_pair("highway", "primary_link"));
    wayFilterSettings.push_back( std::make_pair("highway", "secondary_link"));
    wayFilterSettings.push_back( std::make_pair("highway", "tertiary_link"));
    wayFilterSettings.push_back( std::make_pair("highway", "give_way"));

    mapReader->ConfigureWayFilter(wayFilterSettings);

    mapReader->OpenFile(filename);

    std::cout << "Reading Ways" << std::endl;
    mapReader->ReadOSMPrimitives( eWays );

    std::cout << "Reading nodes" << std::endl;
    mapReader->ReadOSMPrimitives( eNodes );

    std::cout << "Done reading" << std::endl;

    BuildRoutingNetwork();
  }


  COSMNetworkValidator validator(m_routingNetwork);

  return validator.Validate();
}

void COSMModelBuilder::NotifyBoundingBox( const double left, const double top, const double right, const double bottom )
{

}

void COSMModelBuilder::CleanNodes()
{
  m_routingNetwork.id2NodeMap.clear();
  m_routingNetwork.id2WayMap.clear();
}



void COSMModelBuilder::AddNode( tOSMNodeShPtr& ptrNode )
{
  auto storedNodeObjectIter = m_routingNetwork.id2NodeMap.find( ptrNode->getId() );

  if ( m_routingNetwork.id2NodeMap.end() != storedNodeObjectIter )
  {
    *(storedNodeObjectIter->second) = *(ptrNode);
  }
}

void COSMModelBuilder::AddWay( tWayShPtr& ptrWay )
{
  m_routingNetwork.id2WayMap.insert( tWayId2WayMap::value_type( ptrWay->GetId(), ptrWay));

  m_currentWay = ptrWay;
  m_prevGeoPoint.reset();
}

void COSMModelBuilder::AddWaypoint( const int64_t& wayId, const int64_t& nodeId )
{
  if ( m_currentWay && ( wayId == m_currentWay->GetId() ) )
  {
    tOSMNodeShPtr nodePtr;
    auto waypointIter = m_routingNetwork.id2NodeMap.find( nodeId );
    if ( m_routingNetwork.id2NodeMap.end() != waypointIter )
    {
      nodePtr = waypointIter->second;
    }
    else
    {
      nodePtr = std::make_shared<COSMNode>(nodeId );

      m_routingNetwork.id2NodeMap.insert( tNodeId2NodeMap::value_type( nodeId, nodePtr) );
    }

    if ( m_prevGeoPoint )
    {
      m_currentWay->AddWaySegment( CWaySegment( m_prevGeoPoint, nodePtr ) );
    }
    m_prevGeoPoint = nodePtr;

    auto nodeIter = m_node2wayListsMap.find(nodeId );
    if ( m_node2wayListsMap.end() != nodeIter )
    {
      nodeIter->second.push_back( m_currentWay );
    }
    else
    {
      m_node2wayListsMap.insert(tNodeId2WayListsMap::value_type(nodeId, { m_currentWay }));
    }
  }
}

void COSMModelBuilder::BuildRoutingNetwork()
{
  for ( auto wayIter : m_routingNetwork.id2WayMap )
  {
    auto wayPtr = wayIter.second;
    addWayToNodeRecord( wayPtr->GetBeginNode()->getId(), wayPtr );
    addWayToNodeRecord( wayPtr->GetEndNode()->getId(), wayPtr );
  }

  std::cout << "Building the rest" << std::endl;

  for ( auto nodeWayListIter : m_routingNetwork.nodeId2Ways)
  {
    auto nodeId = nodeWayListIter.first;
    auto wayLists = nodeWayListIter.second;

    int wayListsSize = wayLists.size();
    if (  1 == wayListsSize  )
    {
      std::cout << nodeId << " -- It looks, there is only one way in this node" << std::endl;
      auto way = *(wayLists.begin());
      
      auto iterToContainingWay = m_node2wayListsMap.find( nodeId );
      if ( m_node2wayListsMap.end() != iterToContainingWay )
      {
        auto nodesWays = iterToContainingWay->second;
        std::cout << "there's containing way " << nodesWays.size() << std::endl;
        for ( auto way : nodesWays )
        {
          way->Print();
          auto segments = way->GetWaySegments();

          int sizeSegment( segments.size() );
          for ( int i = 0 ; i < sizeSegment ; ++i)
          {
            auto segment = segments[i];
            if ( (i !=0 )&&(i != sizeSegment-1) && ( segment.getEndNode()->getId() == nodeId || segment.getBeginNode()->getId() == nodeId ))
            {
              std::cout << "The nodeId " << nodeId << " is in the middle " << i << "++"<< std::endl;
            }
          }
        }

      }
    }

  }

}


void COSMModelBuilder::addWayToNodeRecord( const int64_t& nodeId, tWayShPtr wayPtr)
{
  auto nodeWaysListIter = m_routingNetwork.nodeId2Ways.find(nodeId);

  if ( m_routingNetwork.nodeId2Ways.end() == nodeWaysListIter )
  {
    m_routingNetwork.nodeId2Ways.insert( tNodeId2WayListsMap::value_type(nodeId, { wayPtr }) );
  }
  else
  {
    nodeWaysListIter->second.push_back( wayPtr) ;
  }
}

}