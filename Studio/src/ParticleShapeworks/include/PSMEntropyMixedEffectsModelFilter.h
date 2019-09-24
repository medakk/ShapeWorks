#ifndef __PSMEntropyMixedEffectsModelFilter_h
#define __PSMEntropyMixedEffectsModelFilter_h

#include "PSMEntropyModelFilter.h"
#include "PSMMixedEffectsShapeMatrixAttribute.h"

//using namespace itk;


  
/** \class PSMEntropyMixedEffectsModelFilter
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
template <class TImage, class TShapeMatrix = PSMMixedEffectsShapeMatrixAttribute<double, TImage::ImageDimension> >
class PSMEntropyMixedEffectsModelFilter
  : public PSMEntropyModelFilter<TImage,TShapeMatrix>
{
 public:
 /** Standard class typedefs. */
 typedef PSMEntropyMixedEffectsModelFilter  Self;
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
 itkTypeMacro(PSMEntropyMixedEffectsModelFilter, PSMEntropyModelFilter);
 
 /** Type of the input/output image. */
 typedef typename Superclass::ImageType ImageType;

  /** Expose the point type */
 typedef typename Superclass::PointType PointType;

  /** Type of the optimizer */
 typedef typename Superclass::OptimizerType OptimizerType;

 /** Set/Get the explanatory variables */
 void SetVariables(const std::vector<double> &v)
 {
   this->GetShapeMatrix()->SetExplanatory(v);
 }
 const std::vector<double> &GetVariables() const
 {
   return this->GetShapeMatrix()->GetExplanatory();
 }

 /** Set/Get time point variables */
 void SetTimePointsPerIndividual(const vnl_vector<int> &v)
 {
   this->GetShapeMatrix()->SetTimePointsPerIndividual(v);
 }
 const vnl_vector<int> &GetTimePointsPerIndividual() const
 {
   return this->GetShapeMatrix()->GetTimePointsPerIndividual();
 }

 /** Set/Get num individuals */
 void SetNumIndividuals(int n)
 {
   this->GetShapeMatrix()->SetNumIndividuals(n);
 }
 int GetNumIndividuals()
 {
   return this->GetShapeMatrix()->GetNumIndividuals();
 }

 protected:
 PSMEntropyMixedEffectsModelFilter() {}
 virtual ~PSMEntropyMixedEffectsModelFilter() {}
 
 void PrintSelf(std::ostream& os, itk::Indent indent) const
 {
   Superclass::PrintSelf(os, indent);
  }

private:
  PSMEntropyMixedEffectsModelFilter(const Self&); //purposely not implemented
  void operator=(const Self&);        //purposely not implemented
};



#endif
