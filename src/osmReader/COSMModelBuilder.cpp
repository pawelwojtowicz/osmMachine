#include "COSMModelBuilder.h"
#include "CPBFReader.h"
#include "COSMParser.h"
#include <iostream>

namespace osmMachine
{

COSMModelBuilder::COSMModelBuilder()
{

}
COSMModelBuilder::~COSMModelBuilder()
{

}

bool COSMModelBuilder::ReadOSMData( const std::string& filename)
{
  std::unique_ptr<IOSMMapFileReader> reader = std::make_unique<CPBFReader>(*this);

  reader->ReadMapFile(filename, eAll );

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
  m_id2NodeMap.insert(tNodeId2NodeMap::value_type( ptrNode->getId(), ptrNode ) ) ;
}

void COSMModelBuilder::AddWay( tWayShPtr& ptrWay )
{
  m_id2WayMap.insert( tWayId2WayMap::value_type( ptrWay->GetId(), ptrWay));

  m_currentWay = ptrWay;
  m_prevGeoPoint.reset();
  std::cout << std::endl << "NewWay-";

}

void COSMModelBuilder::AddWaypoint( const int64_t& wayId, const int64_t& nodeId )
{
  if ( m_currentWay && ( wayId == m_currentWay->GetId() ) )
  {
    auto waypointIter = m_id2NodeMap.find( nodeId );
    if ( m_id2NodeMap.end() != waypointIter )
    {
      if ( m_prevGeoPoint )
      {
        std::cout << "X";
        m_currentWay->AddWaySegment( CWaySegment( m_prevGeoPoint, waypointIter->second ) );
      }
      m_prevGeoPoint = waypointIter->second;
    }
    else
    {
      std::cout << "O";
    }
  }
  else
  {
    std::cout << std::endl;
  }
}


}