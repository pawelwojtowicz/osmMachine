#pragma once
#include "GeoDefs.h"

namespace osmMachine
{

class CGeoPoint
{
public:
  CGeoPoint();
  CGeoPoint( const double& lon, const double& lat);
  virtual ~CGeoPoint();
  
  inline const double getLon() const { return m_lon; };
  inline const double getLat() const { return m_lat; };
  inline const bool isValid() const {return m_valid; };
  
  CGeoPoint( const CGeoPoint& geoPoint ) = default;
  CGeoPoint& operator=( const CGeoPoint& geoPoint ) = default;
  
  inline bool operator==( const CGeoPoint& right ) { return ( this->m_lon == right.m_lon ) && ( this->m_lat == right.m_lat); };

private:
  bool m_valid;
  double m_lon;
  double m_lat;
};

}