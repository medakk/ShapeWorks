#include "PSMProjectWriter.h"
#include <fstream>



PSMProjectWriter::PSMProjectWriter()
{

}

void PSMProjectWriter::Update()
{
  std::ofstream out;
  out.open(this->GetFileName());
  if (!out) 
    {
      itkExceptionMacro( "Could not open the file " + m_FileName + " for output.");
    }
  else
    {
      m_Input->Stream(out);
      out.close();
    }
}


