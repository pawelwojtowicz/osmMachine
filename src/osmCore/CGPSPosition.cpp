#include "CGPSPosition.h"

namespace osmMachine
{
CGPSPosition::CGPSPosition()
: CGeoPoint()
, m_altitude(0)
, m_heading(0)
, m_speed(0)
{

}

CGPSPosition::CGPSPosition(double latDeg,double lonDeg)
: CGeoPoint(DEG2RAD(latDeg), DEG2RAD(lonDeg))
, m_altitude(0)
, m_heading(0)
, m_speed(0)
{

}


CGPSPosition::~CGPSPosition()
{

}

}