#ifndef __PSMDomain_hxx
#define __PSMDomain_hxx
#include "PSMDomain.h"


template <unsigned int VDimension>
PSMDomain<VDimension>::PSMDomain()  : m_ConstraintsEnabled(true)
{
}

template <unsigned int VDimension>
void PSMDomain<VDimension>::PrintSelf(std::ostream& os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}


#endif //__PSMDomain_hxx
