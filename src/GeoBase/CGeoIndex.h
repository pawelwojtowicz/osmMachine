#pragma once

namespace osmMachine
{
using tGeoIndex = unsigned int;

class CGeoIndex
{
public:
    CGeoIndex();
    virtual ~CGeoIndex();

    int Initialize( double latBegin, double lonBegin, double latEnd, double lonEnd, int zoomLevel );

    tGeoIndex CalculateIndex( double lat, double lon ) const;
private:
    int m_zoomLevel;
    int m_xMin;
    int m_yMin;
    int m_dx;
    int m_dy;
};
}