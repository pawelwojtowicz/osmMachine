#include "CTimespanMeter.h"
#include <Logger/Logger.h>

namespace Utils
{
CTimespanMeter::CTimespanMeter( const std::string& topic )
: m_timeMeasurementTopic(topic)
{
  ResetTimeBaseline();
}
  
CTimespanMeter::~CTimespanMeter()
{
  
}

void CTimespanMeter::ResetTimeBaseline()
{
  LOG(PERF,("[%s] - Reset", m_timeMeasurementTopic.c_str()));
  m_timeBaseline = std::chrono::high_resolution_clock::now() ;

}

void CTimespanMeter::CatchTimestampToBaseline( const std::string& referenceLabel)
{
  auto timeSpanInMiliseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_timeBaseline);
  LOG(PERF,("[%s] - %s - span=%d[ms]", m_timeMeasurementTopic.c_str(), referenceLabel.c_str(), timeSpanInMiliseconds));
}

}