#ifndef __PSMMeanCurvatureAttribute_hxx
#define __PSMMeanCurvatureAttribute_hxx
#include "PSMMeanCurvatureAttribute.h"

#include <itkZeroCrossingImageFilter.h>
#include <itkImageRegionConstIteratorWithIndex.h>

//using namespace itk;


template <class TNumericType, unsigned int VDimension>
void
PSMMeanCurvatureAttribute<TNumericType, VDimension>::
ComputeCurvatureStatistics(const ParticleSystemType *system, unsigned int d)
{
  typedef PSMImageDomainWithCurvature<TNumericType, VDimension> DomainType;
  typedef typename DomainType::ImageType ImageType;

  // Loop through a zero crossing image, project all the zero crossing points
  // to the surface, and use those points to comput curvature stats.  
  typedef itk::ZeroCrossingImageFilter<ImageType, ImageType> ZeroCrossingImageFilterType;
  typename ZeroCrossingImageFilterType::Pointer zc = ZeroCrossingImageFilterType::New() ;
  zc->SetInput( dynamic_cast<const DomainType *>(system->GetDomain(d))->GetImage() );
  zc->Update();
  
  itk::ImageRegionConstIteratorWithIndex<ImageType> it(zc->GetOutput(),
                                                       zc->GetOutput()->GetRequestedRegion());
  std::vector<double> datalist;
  m_MeanCurvatureList[d] = 0.0;
  m_CurvatureStandardDeviationList[d] = 0.0;
  const DomainType *domain = static_cast<const DomainType *>(system->GetDomain(d));
  
  for (; ! it.IsAtEnd(); ++it)
    {
      if (it.Get() == 1.0)
        {
          // Find closest pixel location to surface.
          PointType pos;
          domain->GetImage()->TransformIndexToPhysicalPoint(it.GetIndex(), pos);
          
          // Project point to surface.
          // Make sure constraints are enabled
          //      bool c = domain->GetConstraintsEnabled();
          //      domain->EnableConstraints();
          domain->ApplyConstraints(pos);
          //      domain->SetConstraintsEnabled(c);
          
          // Compute curvature at point.
          double mc = domain->GetCurvature(pos);      
          m_MeanCurvatureList[d] += mc;
          datalist.push_back(mc);
        }
    }
  double n = static_cast<double>(datalist.size());
  m_MeanCurvatureList[d] /= n;
  
  // Compute std deviation using point list
  for (unsigned int i = 0; i < datalist.size(); i++)
    {
      m_CurvatureStandardDeviationList[d] += (datalist[i] - m_MeanCurvatureList[d]) * (datalist[i] - m_MeanCurvatureList[d]);
    }
  m_CurvatureStandardDeviationList[d] = sqrt(m_CurvatureStandardDeviationList[d] / (n-1));
}
  

#endif
