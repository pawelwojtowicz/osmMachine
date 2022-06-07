#pragma once
#include "IOSMMapFileReader.h"
#include "IOSMModelBuilder.h"


class Nodes;

namespace osmMachine
{

class CPBFReader : public IOSMMapFileReader
{
public:
  using tElementType = enum { 
    eNodes      = 0x01,
    eWays       = 0x02,
    eRelations  = 0x04,
    eAll        = eNodes | eWays | eRelations
  };

  CPBFReader( IOSMModelBuilder& osmModelBuilder);
  virtual ~CPBFReader();

  bool ReadMapFile( const std::string& fileName , const tOSMPrimitiveType primitivesToRead ) override;

private:
  IOSMModelBuilder& m_osmModelBuilder;
};
}