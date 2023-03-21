#include "COSMModelBuilder.h"
#include "CPBFReader.h"
#include "COSMParser.h"
#include "COSMNetworkValidator.h"
#include <set>
#include <iostream>
#include <algorithm>

namespace osmMachine
{

static const std::string osmFilenamePostfix(".osm");
static const std::string pbfFilenamePostfix(".osm.pbf");

COSMModelBuilder::COSMModelBuilder()
: m_helperWayId(0)
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

tWayShPtr COSMModelBuilder::AddHelperWay( int64_t masterWayId, const tPropertyMap& properties )
{
  tWayShPtr ptrWay = std::make_shared<COSMWay>(++m_helperWayId);

  for ( const auto& propertyPair : properties )
  {
    ptrWay->AddProperty( propertyPair.first, propertyPair.second);
  }
  ptrWay->AddProperty("osmWayMasterId", std::to_string(masterWayId) );

  m_routingNetwork.helperWayId2MapWay.insert( tWayId2WayMap::value_type( ptrWay->GetId(), ptrWay));

  m_currentWay = ptrWay;
  m_prevGeoPoint.reset();

  return ptrWay;
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
  //will store the ways, and their geonodes, tha
  std::map<int64_t, std::set<int64_t>> wayId2dividingNodeIds;

  for ( const auto& nodeWayPair : m_node2wayListsMap )
  {
    const auto nodeId = nodeWayPair.first;
    const auto& wayList = nodeWayPair.second;

    if (wayList.size() > 1 )
    {
      for ( const auto& way : wayList )
      {
        if ( ( way->GetBeginNode()->getId() ) != nodeId && ( way->GetEndNode()->getId() != nodeId ) )
        {
          auto wayIter = wayId2dividingNodeIds.find( way->GetId() );
          if ( wayId2dividingNodeIds.end() != wayIter )
          {
            wayIter->second.insert( nodeId );
          }
          else
          {
            wayId2dividingNodeIds[ way->GetId() ] = { nodeId }; 
          }
        }
      }
    }
  }

  for ( const auto& wayId2SplittingNodes : wayId2dividingNodeIds)
  {
    const auto wayId = wayId2SplittingNodes.first;

    const auto& splittingNodes = wayId2SplittingNodes.second;

    const auto& wayToSplit = m_routingNetwork.id2WayMap[wayId]; 
    
    tWayShPtr helperWay = AddHelperWay( wayId, wayToSplit->GetProperties() );
    for ( const auto& waySegment : wayToSplit->GetWaySegments() )
    {
      helperWay->AddWaySegment( waySegment );

      if ( splittingNodes.find (waySegment.getEndNode()->getId() ) != splittingNodes.end() )
      {
        helperWay = AddHelperWay( wayId, wayToSplit->GetProperties() );
      }
    }
  }

  for ( auto wayIter : m_routingNetwork.id2WayMap )
  {
    auto wayPtr = wayIter.second;
    addWayToNodeRecord( wayPtr->GetBeginNode()->getId(), wayPtr );
    if ( !wayPtr->IsOneWay() )
    {
      addWayToNodeRecord( wayPtr->GetEndNode()->getId(), wayPtr );
    }
  }

  for ( auto wayIter : m_routingNetwork.helperWayId2MapWay )
  {
    auto wayPtr = wayIter.second;
    addWayToNodeRecord( wayPtr->GetBeginNode()->getId(), wayPtr );
    if ( !wayPtr->IsOneWay() )
    {
      addWayToNodeRecord( wayPtr->GetEndNode()->getId(), wayPtr );
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