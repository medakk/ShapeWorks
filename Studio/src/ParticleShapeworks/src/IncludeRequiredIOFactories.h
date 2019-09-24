#ifndef __TestDriverIncludeRequiredIOFactories_h
#define __TestDriverIncludeRequiredIOFactories_h
#include <itkGDCMImageIOFactory.h>
#include <itkMetaImageIOFactory.h>
#include <itkObjectFactoryBase.h>
#include <itkNrrdImageIOFactory.h>

/** Fixed ITK runtime error where image format is not recognized. */
void RegisterRequiredFactories(){
  itk::ObjectFactoryBase::RegisterFactory( itk::MetaImageIOFactory::New() );
  itk::ObjectFactoryBase::RegisterFactory( itk::GDCMImageIOFactory::New() );
  itk::ObjectFactoryBase::RegisterFactory( itk::NrrdImageIOFactory::New() );
}

#endif
