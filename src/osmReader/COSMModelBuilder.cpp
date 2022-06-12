#include "COSMModelBuilder.h"
#include "CPBFReader.h"
#include "COSMParser.h"
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

    wayFilterSettings.push_back( std::make_pair("highway", ""));
    mapReader->ConfigureWayFilter(wayFilterSettings);

    mapReader->OpenFile(filename);

    std::cout << "Reading Ways" << std::endl;
    mapReader->ReadOSMPrimitives( eWays );

    std::cout << "Reading nodes" << std::endl;
    mapReader->ReadOSMPrimitives( eNodes );

    std::cout << "Done reading" << std::endl;


    for ( auto wayIter : m_id2WayMap )
    {
      auto wayPtr = wayIter.second;

      for ( const auto& waySegment : wayPtr->GetWaySegments() )
      {
        if ( waySegment.getBeginNode()->isValid() )
        {
          std::cout << "+";
        }
        else
        {
          std::cout << "-";
        }
        if ( waySegment.getEndNode()->isValid() )
        {
          std::cout << "+";
        }
        else
        {
          std::cout << "-";
        }
      }
      std::cout << std::endl;
    }
  }


}

void COSMModelBuilder::NotifyBoundingBox( const double left, const double top, const double right, const double bottom )
{

}

void COSMModelBuilder::CleanNodes()
{
  m_id2NodeMap.clear();
  m_id2WayMap.clear();
}



void COSMModelBuilder::AddNode( tOSMNodeShPtr& ptrNode )
{
  auto storedNodeObjectIter = m_id2NodeMap.find( ptrNode->getId() );

  if ( m_id2NodeMap.end() != storedNodeObjectIter )
  {
    *(storedNodeObjectIter->second) = *(ptrNode);
  }
}

void COSMModelBuilder::AddWay( tWayShPtr& ptrWay )
{
  m_id2WayMap.insert( tWayId2WayMap::value_type( ptrWay->GetId(), ptrWay));

  m_currentWay = ptrWay;
  m_prevGeoPoint.reset();
}

void COSMModelBuilder::AddWaypoint( const int64_t& wayId, const int64_t& nodeId )
{
  if ( m_currentWay && ( wayId == m_currentWay->GetId() ) )
  {
    tOSMNodeShPtr nodePtr;
    auto waypointIter = m_id2NodeMap.find( nodeId );
    if ( m_id2NodeMap.end() != waypointIter )
    {
      nodePtr = waypointIter->second;
    }
    else
    {
      nodePtr = std::make_shared<COSMNode>(nodeId );

      m_id2NodeMap.insert( tNodeId2NodeMap::value_type( nodeId, nodePtr) );
    }

    if ( m_prevGeoPoint )
    {
      m_currentWay->AddWaySegment( CWaySegment( m_prevGeoPoint, nodePtr ) );
    }
    m_prevGeoPoint = nodePtr;
  }
}


}