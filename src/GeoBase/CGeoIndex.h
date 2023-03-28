#pragma once
#include <cstdint>

namespace osmMachine
{
class CGeoIndex
{
public:
    CGeoIndex();
    virtual ~CGeoIndex();

    int Initialize( double latBegin, double lonBegin, double latEnd, double lonEnd, int zoomLevel );

    int64_t CalculateIndex( double lat, double lon ) const;
private:
    int m_zoomLevel;
    uint32_t m_xMin;
    uint32_t m_yMin;
    uint32_t m_dx;
    uint32_t m_dy;
};
}