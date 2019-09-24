#ifndef __PSMImplicitSurfaceImageFilter_hxx
#define __PSMImplicitSurfaceImageFilter_hxx

#include "PSMImplicitSurfaceImageFilter.h"
#include <itkAntiAliasBinaryImageFilter.h>
#include <itkReinitializeLevelSetImageFilter.h>
#include <itkDiscreteGaussianImageFilter.h>
#include <itkProgressAccumulator.h>

//using namespace itk;


template< class TInputImage, class TOutputImage >
void
PSMImplicitSurfaceImageFilter< TInputImage, TOutputImage >
::PrintSelf(std::ostream & os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "m_SmoothingSigma = "   << m_SmoothingSigma << std::endl;
  os << indent << "m_IsosurfaceValue = " << m_IsosurfaceValue << std::endl;
}

template< class TInputImage, class TOutputImage >
void 
PSMImplicitSurfaceImageFilter<TInputImage, TOutputImage>::GenerateData()
{
  // Allocate outputs
  typename TOutputImage::Pointer output = this->GetOutput();
  output->SetBufferedRegion( output->GetRequestedRegion() );
  output->Allocate();

  // Create a process accumulator for tracking the progress of minipipeline
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New();
  progress->SetMiniPipelineFilter(this);
  
  // Set up the mini-filter pipeline
  typename itk::AntiAliasBinaryImageFilter<InputImageType, OutputImageType>::Pointer anti
    = itk::AntiAliasBinaryImageFilter<InputImageType, OutputImageType>::New();
  anti->SetInput(this->GetInput());
  anti->SetNumberOfIterations(100);
  anti->SetMaximumRMSError(0.0);
  anti->SetIsoSurfaceValue(m_IsosurfaceValue);
  progress->RegisterInternalFilter(anti, 1.0f / 3.0f);

  typename itk::ReinitializeLevelSetImageFilter<OutputImageType>::Pointer filt
    = itk::ReinitializeLevelSetImageFilter<OutputImageType>::New();
  filt->SetInput(anti->GetOutput());
  filt->NarrowBandingOff();
  filt->SetLevelSetValue(0.0);
  progress->RegisterInternalFilter(filt, 1.0f / 3.0f);
    
  typename itk::DiscreteGaussianImageFilter<OutputImageType, OutputImageType>::Pointer blur
    = itk::DiscreteGaussianImageFilter<OutputImageType, OutputImageType>::New();
  blur->SetInput(filt->GetOutput());
  blur->SetVariance(m_SmoothingSigma * m_SmoothingSigma);
  blur->SetUseImageSpacingOn();
  progress->RegisterInternalFilter(blur, 1.0f / 3.0f);
  
  // pipe to the output image
  blur->GraftOutput(this->GetOutput());
  blur->Update();
  // also necessary for pipe to output
  // see itkImageSource for description
  this->GraftOutput(blur->GetOutput());
}

#endif
