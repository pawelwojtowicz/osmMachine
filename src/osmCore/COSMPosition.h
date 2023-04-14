#pragma once
#include <stdint.h>
#include <GeoBase/CGeoPoint.h>
#include "COSMWay.h"

namespace osmMachine
{
class COSMPosition
{
public:
  COSMPosition();
  COSMPosition( const tWayShPtr ptrWay,
                const int waySegmentIdex, 
                const double m_distanceOnSegment, 
                const double rawFromProjectionDistance,
                const GeoBase::CGeoPoint& rawGeoPoint, 
                const GeoBase::CGeoPoint& snappedToMap);

  COSMPosition(const COSMPosition& ) = default;
  COSMPosition& operator=(const COSMPosition& ) = default;

  bool IsValid() const;

  inline int64_t GetWayId() const { return m_ptrWay->GetId(); };
  inline tWayShPtr GetWay() const { return m_ptrWay;};

  inline double GetDistanceOnSegment() const { return m_distanceOnSegment; };

  inline double GetRaw2ProjectionDistance() const { return m_rawFromProjectionDistance;} ;

  inline bool operator<( const COSMPosition& rhs ) const { return (m_rawFromProjectionDistance < rhs.m_rawFromProjectionDistance); };
  inline bool operator>( const COSMPosition& rhs ) const { return (m_rawFromProjectionDistance > rhs.m_rawFromProjectionDistance); };

  const GeoBase::CGeoPoint& GetPositionSnapped2OSM() const { return m_snappedToMap;};

private:
  tWayShPtr m_ptrWay;

  int m_waySegmentIdex;

  double m_distanceOnSegment;

  double m_rawFromProjectionDistance;

  GeoBase::CGeoPoint m_rawGeoPoint;

  GeoBase::CGeoPoint m_snappedToMap;
};
}