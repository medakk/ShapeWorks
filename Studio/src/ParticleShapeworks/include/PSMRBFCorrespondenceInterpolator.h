#ifndef __PSMRBFCorrespondenceInterpolator_h
#define __PSMRBFCorrespondenceInterpolator_h

#include <vector>
#include <vnl/vnl_vector.h>
#include <vnl/vnl_matrix.h>
#include <vnl/algo/vnl_svd.h>

//using namespace itk;

#include <itkFunctionBase.h>
#include <itkPoint.h>
#include <itkMacro.h>



/** \class PSMRBFCorrespondenceInterpolator
 * \brief 
 *
 *
 * \ingroup 
 */
template <unsigned int VDimension>
class PSMRBFCorrespondenceInterpolator :
  public FunctionBase itk::Point<double,VDimension>, itk::Point<double,VDimension> >
{
public:
  /** Dimensionality of the points. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);

  /** Standard class typedefs. */
  typedef PSMRBFCorrespondenceInterpolator    Self;
  typedef itk::Point<double,VDimension>            PointType;
  typedef FunctionBase <PointType, PointType> Superclass;
  typedef itk::SmartPointer<Self>                  Pointer;
  typedef itk::SmartPointer<const Self>            ConstPointer;

  /** Method to create through the object factory. */
  itkNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  itkTypeMacro( PSMRBFCorrespondenceInterpolator, FunctionBase );

  /** Set/Get the first point set "A".  This is the point set that
      defines the domain from which points will be mapped by the
      function. */
  void SetPointSetA(const std::vector<PointType> &v)
    {      
      m_PointSetA = v;
    }
  const std::vector<PointType> & GetPointSetA() const
  {
    return m_PointSetA;
  }

  /** Set/Get the second point set "B".  This is the point set surface
      that defines the domain into which points will be mapped by the
      function. */
  void SetPointSetB(const std::vector<PointType> &v)
    {      
      m_PointSetB = v;
    }
  const std::vector<PointType> & GetPointSetB() const
  {
    return m_PointSetB;
  }

  /** Compute the interpolation function.*/
  void Initialize();

  /** Returns true if the interpolation function has been computed.*/
  itkGetMacro(Initialized, bool);

  /** Map a point from the surface domain defined by PointSetA to the
      domain defined by PointSetB. */
  virtual PointType Evaluate( const PointType& pt ) const;

protected:
  PSMRBFCorrespondenceInterpolator();
  virtual ~PSMRBFCorrespondenceInterpolator() {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os,indent);
  }

private:
  PSMRBFCorrespondenceInterpolator(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  bool m_Initialized;

  std::vector<PointType> m_PointSetA;
  std::vector<PointType> m_PointSetB;

  /** Parameter matrices */
  vnl_matrix<double> m_P;
  vnl_matrix<double> m_C;
  
};



#ifndef ITK_MANUAL_INSTANTIATION
#include "PSMRBFCorrespondenceInterpolator.hxx"
#endif

#endif
