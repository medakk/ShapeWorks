#ifndef __PSMEntropyRegressionModelFilter_h
#define __PSMEntropyRegressionModelFilter_h

#include "PSMEntropyModelFilter.h"
#include "PSMRegressionShapeMatrixAttribute.h"

//using namespace itk;


  
/** \class PSMEntropyRegressionModelFilter
 *
 * \brief
 *
 * This class decorates the base PSMEntropyModelFilter class with some
 * additional methods for setting explanatory variables for the
 * regression computation and retrieving regression model paramters.
 * 
 * \ingroup PSM 
 * \ingroup PSMModelingFilters
 * \author Josh Cates
 */
template <class TImage, class TShapeMatrix = PSMRegressionShapeMatrixAttribute<double, TImage::ImageDimension> >
class PSMEntropyRegressionModelFilter
  : public PSMEntropyModelFilter<TImage,TShapeMatrix>
{
 public:
 /** Standard class typedefs. */
 typedef PSMEntropyRegressionModelFilter  Self;
 typedef PSMEntropyModelFilter<TImage, TShapeMatrix> Superclass;
 typedef itk::SmartPointer<Self>   Pointer;
 typedef itk::SmartPointer<const Self>  ConstPointer;
 
 /** Dimensionality of the domain of the particle system. */
 itkStaticConstMacro(Dimension, unsigned int, TImage::ImageDimension);
 
 /** Type of the particle system */
 typedef typename Superclass::ParticleSystemType ParticleSystemType;
 
 /** The type of the Shape Matrix, which defines optimization behavior. */
 typedef TShapeMatrix ShapeMatrixType;

 /** Method for creation through the object factory. */
 itkNewMacro(Self);
 
 /** Run-time type information (and related methods). */
 itkTypeMacro(PSMEntropyRegressionModelFilter, PSMEntropyModelFilter);
 
 /** Type of the input/output image. */
 typedef typename Superclass::ImageType ImageType;

  /** Expose the point type */
 typedef typename Superclass::PointType PointType;

  /** Type of the optimizer */
 typedef typename Superclass::OptimizerType OptimizerType;

 /** Set/Get the explanatory variables */
 void SetVariables(const std::vector<double> &v)
 {
   this->GetShapeMatrix()->SetVariables(v);
 }
 const std::vector<double> &GetVariables() const
 {
   return this->GetShapeMatrix()->GetVariables();
 }

protected:
 PSMEntropyRegressionModelFilter() {}
 virtual ~PSMEntropyRegressionModelFilter() {}
 
 void PrintSelf(std::ostream& os, itk::Indent indent) const
 {
   Superclass::PrintSelf(os, indent);
  }

private:
  PSMEntropyRegressionModelFilter(const Self&); //purposely not implemented
  void operator=(const Self&);        //purposely not implemented
};



#endif
