#pragma once
#include <stdint.h>
#include <GeoBase/CGeoPoint.h>

namespace osmMachine
{
class COSMPosition
{
public:
  COSMPosition();
  COSMPosition( const int64_t wayId,
                const int waySegmentIdex, 
                const double m_distanceOnSegment, 
                const double rawFromProjectionDistance,
                const GeoBase::CGeoPoint& rawGeoPoint, 
                const GeoBase::CGeoPoint& snappedToMap);

  COSMPosition(const COSMPosition& ) = default;
  COSMPosition& operator=(const COSMPosition& ) = default;

  bool IsValid() const;

  inline int64_t GetWayId() const { return m_wayId; };

  inline double GetDistanceOnSegment() const { return m_distanceOnSegment; };

  inline double GetRaw2ProjectionDistance() const { return m_rawFromProjectionDistance;} ;

  inline bool operator<( const COSMPosition& rhs ) const { return (m_rawFromProjectionDistance < rhs.m_rawFromProjectionDistance); };
  inline bool operator>( const COSMPosition& rhs ) const { return (m_rawFromProjectionDistance > rhs.m_rawFromProjectionDistance); };

private:
  int64_t m_wayId;

  int m_waySegmentIdex;

  double m_distanceOnSegment;

  double m_rawFromProjectionDistance;

  GeoBase::CGeoPoint m_rawGeoPoint;

  GeoBase::CGeoPoint m_snappedToMap;
};
}