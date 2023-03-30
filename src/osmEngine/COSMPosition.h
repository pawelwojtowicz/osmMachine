#pragma once
#include <stdint.h>
#include <CGeoPoint.h>

namespace osmMachine
{
class COSMPosition
{
public:
  COSMPosition();
  COSMPosition(const COSMPosition& ) = default;
  COSMPosition& operator=(const COSMPosition& ) = default;

  bool IsValid() const;


private:
  int64_t m_wayId;

  int m_waySegmentIdex;

  double m_distanceOnSegment;

  CGeoPoint m_rawGeoPoint;

  CGeoPoint m_snappedToMap;
};
}