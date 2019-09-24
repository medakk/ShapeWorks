#include "PSMProjectReader.h"



PSMProjectReader::PSMProjectReader()
{
}

void PSMProjectReader::Update()
{
  // Have the parent class parse the XML file
  Superclass::Update();

  DOMNodeType* dom = this->GetDOMNode();

  if (dom == 0)
    {
      itkExceptionMacro( "Failed to parse the XML file." );
    }
  else
    { 
      // Allocate a new PSM Project.
      m_Output = PSMProject::New();
      m_Output->SetDOMNode(dom);
    }
}


