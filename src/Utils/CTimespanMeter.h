#pragma once
#include <string>
#include <chrono>

namespace Utils
{
class CTimespanMeter
{
public:
  CTimespanMeter( const std::string& topic );
  ~CTimespanMeter();

  void ResetTimeBaseline();
  void CatchTimestampToBaseline( const std::string& );

private:
  std::string m_timeMeasurementTopic;

  
  std::chrono::high_resolution_clock::time_point m_timeBaseline;
};
}
