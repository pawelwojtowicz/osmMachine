#pragma once
#include "IOSMMapFileReader.h"
#include "IOSMModelBuilder.h"
#include <memory>


class Nodes;

namespace osmMachine
{

class CPBFReader : public IOSMMapFileReader
{
public:
  CPBFReader( IOSMModelBuilder& osmModelBuilder);
  virtual ~CPBFReader();

  virtual void ConfigureWayFilter( const tFilterSettings& properties ) override;  

  virtual bool OpenFile( const std::string& filename ) override;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) override;

private:
  bool EvaluteWayProperty( const std::string& key, const std::string& value );

private:
  std::unique_ptr<std::ifstream> m_pbfFilestreamPtr;

  tFilterSettings m_wayFilterSettings;

  char* m_fileBuffer;
  char* m_zlibBuffer;

  IOSMModelBuilder& m_osmModelBuilder;
};
}