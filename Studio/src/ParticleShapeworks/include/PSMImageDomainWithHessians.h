#ifndef __PSMImageDomainWithHessians_h
#define __PSMImageDomainWithHessians_h

#include <itkImage.h>
#include "PSMImageDomainWithGradients.h"
#include <itkLinearInterpolateImageFunction.h>
#include <itkGradientImageFilter.h>
#include <itkFixedArray.h>
#include <itkImageDuplicator.h>
#include <itkDiscreteGaussianImageFilter.h>
#include <itkDerivativeImageFilter.h>
#include <vnl/vnl_matrix_fixed.h>

//using namespace itk;


/** \class PSMImageDomainWithHessians
 *
 * An image domain that extends PSMImageDomainWithHessianGradients with Hessian
 * information.  Hessian values are interpolated with the SampleHessians(point)
 * method.  Hessians may be smoothed by specifying a sigma for Gaussian
 * blurring of the image prior to initialization.
 *
 * \sa PSMImageDomain
 * \sa ParticleClipRegionDomain
 * \sa PSMDomain
 */
template <class T, unsigned int VDimension>
class PSMImageDomainWithHessians
  : public PSMImageDomainWithGradients<T, VDimension>
{
public:
  /** Standard class typedefs */
  typedef PSMImageDomainWithHessians Self;
  typedef PSMImageDomainWithGradients<T, VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

    /** Point type of the domain (not necessarily of the image). */
  typedef typename Superclass::PointType PointType;
  
  typedef typename Superclass::ImageType ImageType;
  typedef typename Superclass::ScalarInterpolatorType ScalarInterpolatorType;
  typedef vnl_matrix_fixed<T, VDimension, VDimension> VnlMatrixType;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMImageDomainWithHessians, PSMImageDomainWithGradients);

  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);

  /** Set/Get the itk::Image specifying the particle domain.  The set method
      modifies the parent class LowerBound and UpperBound. */
  void SetImage(ImageType *I)
  {
    Superclass::SetImage(I);
    
    typename DiscreteGaussianImageFilter<ImageType, ImageType>::Pointer
      gaussian = DiscreteGaussianImageFilter<ImageType, ImageType>::New();
    gaussian->SetVariance(m_Sigma * m_Sigma);
    gaussian->SetInput(this->GetImage());
    gaussian->SetUseImageSpacingOn();
    gaussian->Update();
    
    // Compute the second derivatives and set up the interpolators
    for (unsigned int i = 0; i < VDimension; i++)
      {
      typename itk::DerivativeImageFilter<ImageType, ImageType>::Pointer
        deriv = itk::DerivativeImageFilter<ImageType, ImageType>::New();
      deriv->SetInput(gaussian->GetOutput());
      deriv->SetDirection(i);
      deriv->SetOrder(2);
      deriv->SetUseImageSpacingOn();
      deriv->Update();

      m_PartialDerivatives[i] = deriv->GetOutput();

      m_Interpolators[i] = ScalarInterpolatorType::New();
      m_Interpolators[i]->SetInputImage(m_PartialDerivatives[i]);
      }

    // Compute the cross derivatives and set up the interpolators
    unsigned int k = VDimension;
    for (unsigned int i = 0; i < VDimension; i++)
      {
      for (unsigned int j = i+1; j < VDimension; j++, k++)
        {
        typename itk::DerivativeImageFilter<ImageType, ImageType>::Pointer
          deriv1 = itk::DerivativeImageFilter<ImageType, ImageType>::New();
        deriv1->SetInput(gaussian->GetOutput());
        deriv1->SetDirection(i);
        deriv1->SetUseImageSpacingOn();
        deriv1->SetOrder(1);
        deriv1->Update();

        typename itk::DerivativeImageFilter<ImageType, ImageType>::Pointer
          deriv2 = itk::DerivativeImageFilter<ImageType, ImageType>::New();
        deriv2->SetInput(deriv1->GetOutput());
        deriv2->SetDirection(j);
        deriv2->SetUseImageSpacingOn();
        deriv2->SetOrder(1);
        
        deriv2->Update();
        
        m_PartialDerivatives[k] = deriv2->GetOutput();
        m_Interpolators[k] = ScalarInterpolatorType::New();
        m_Interpolators[k]->SetInputImage(m_PartialDerivatives[k]);
        }
      }
  } // end setimage
  
  /** Sample the Hessian at a point.  This method performs no bounds checking.
      To check bounds, use IsInsideBuffer.  SampleHessiansVnl returns a vnl
      matrix of size VDimension x VDimension. */
  inline VnlMatrixType SampleHessianVnl(const PointType &p) const
  {
    VnlMatrixType ans;
    for (unsigned int i = 0; i < VDimension; i++)
      {      ans[i][i] = m_Interpolators[i]->Evaluate(p);      }
    
    // Cross derivatives
    unsigned int k = VDimension;
    for (unsigned int i =0; i < VDimension; i++)
      {
      for (unsigned int j = i+1; j < VDimension; j++, k++)
        {
        ans[i][j] = ans[j][i] = m_Interpolators[k]->Evaluate(p);
        }
      }
    return ans;
  }
  
  /** Set /Get the standard deviation for blurring the image prior to
      computation of the Hessian derivatives.  This value must be set prior to
      initializing this class with an input image pointer and cannot be changed
      once the class is initialized.. */
  itkSetMacro(Sigma, double);
  itkGetMacro(Sigma, double);

  /** Access interpolators and partial derivative images. */
  typename ScalarInterpolatorType::Pointer *GetInterpolators()
  { return m_Interpolators; }
  typename ImageType::Pointer *GetPartialDerivatives()
  { return m_PartialDerivatives; }
  
protected:
  PSMImageDomainWithHessians() : m_Sigma(0.0)
  {  }

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }
  virtual ~PSMImageDomainWithHessians() {};

  void DeletePartialDerivativeImages()
  {
    for (unsigned int i = 0; i < VDimension + ((VDimension * VDimension) - VDimension) / 2; i++)
      {
      m_PartialDerivatives[i]=0;
      m_Interpolators[i]=0;
      }
  }
  
private:
  double m_Sigma;
  
  PSMImageDomainWithHessians(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  // Partials are stored:
  //     0: dxx  3: dxy  4: dxz
  //                 1: dyy  5: dyz
  //                            2: dzz
  //
  typename ImageType::Pointer  m_PartialDerivatives[ VDimension + ((VDimension * VDimension) - VDimension) / 2];

  typename ScalarInterpolatorType::Pointer m_Interpolators[VDimension + ((VDimension * VDimension) - VDimension) / 2];
};



#endif
