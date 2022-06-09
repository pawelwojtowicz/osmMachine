#pragma once
#include "COSMMapFileReader.h"
#include "IOSMModelBuilder.h"
#include <memory>


class Nodes;

namespace osmMachine
{

class CPBFReader : public COSMMapFileReader
{
public:
  CPBFReader( IOSMModelBuilder& osmModelBuilder);
  virtual ~CPBFReader();  

  virtual bool OpenFile( const std::string& filename ) override;

  virtual bool ReadOSMPrimitives( const tOSMPrimitiveType primitivesToRead ) override;

private:
  std::unique_ptr<std::ifstream> m_pbfFilestreamPtr;

  char* m_fileBuffer;
  char* m_zlibBuffer;

  IOSMModelBuilder& m_osmModelBuilder;
};
}