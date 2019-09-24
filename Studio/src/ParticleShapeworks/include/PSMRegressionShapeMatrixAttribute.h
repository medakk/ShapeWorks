#ifndef __PSMRegressionShapeMatrixAttribute_h
#define __PSMRegressionShapeMatrixAttribute_h

#include "PSMShapeMatrixAttribute.h"
#include "PSMParticleSystem.h"
#include <vnl/vnl_vector.h>

//using namespace itk;


/** \class PSMRegressionShapeMatrixAttribute
 *
 *
 *
 */
template <class T, unsigned int VDimension>
class PSMRegressionShapeMatrixAttribute
  : public PSMShapeMatrixAttribute<T,VDimension>
{
public:
  /** Standard class typedefs */
  typedef T DataType;
  typedef PSMRegressionShapeMatrixAttribute Self;
  typedef PSMShapeMatrixAttribute<T,VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMRegressionShapeMatrixAttribute, PSMShapeMatrixAttribute);
  
  /** */
  virtual void UpdateMeanMatrix();
  
  /** Return the mean value for a given explanatory variable. */
  inline vnl_vector<double> ComputeMean(double k) const
  {
    return m_Intercept + m_Slope * k;    
  }

  /** */  
  void ResizeParameters(unsigned int n);
  
  /** */
  virtual void ResizeMeanMatrix(int rs, int cs);
  
  /** */
  void ResizeExplanatory(unsigned int n);
  
  /** Callbacks that may be defined by a subclass.  If a subclass defines one
      of these callback methods, the corresponding flag in m_DefinedCallbacks
      should be set to true so that the PSMParticleSystem will know to register
      the appropriate event with this method. */
  virtual void DomainAddEventCallback(Object *, const itk::EventObject &e);
  virtual void PositionAddEventCallback(Object *o, const itk::EventObject &e);
  virtual void PositionSetEventCallback(Object *o, const itk::EventObject &e);
  
  /** Unimplemented.  Reserved for future. */
  virtual void PositionRemoveEventCallback(Object *, const itk::EventObject &) 
  {
    itkExceptionMacro("Method has not been implemented");
  }
  
  /** Set/Get the number of domains per shape.  This can only be safely done
      before shapes are initialized with points! */
  void SetDomainsPerShape(int i)
  { this->m_DomainsPerShape = i; }
  int GetDomainsPerShape() const
  { return this->m_DomainsPerShape; }

  /** Set/Get the explanatory variables (e.g. time). There should be one
      variable per domain. */
  void SetVariables(const std::vector<double> &v)
  {
    this->SetExplanatory(v);
  }
  void SetExplanatory(const std::vector<double> &v);
  void SetExplanatory(unsigned int i, double q)
  { m_Explanatory[i] = q; }
  const vnl_vector<double> &GetVariables() const
  { return m_Explanatory; }
  const vnl_vector<double> &GetExplanatory() const
  { return m_Explanatory; }
  vnl_vector<double> &GetExplanatory()
  { return m_Explanatory; }
  const double &GetExplanatory(unsigned int i) const
  { return m_Explanatory[i]; }
  double &GetExplanatory(unsigned int i)
  { return m_Explanatory[i]; }

  /** */
  const vnl_matrix<double> &GetMeanMatrix() const
  {
    return m_MeanMatrix;
  }
  vnl_matrix<double> &GetMeanMatrix() 
  {
    return m_MeanMatrix;
  }

  /** Returns the slope (in shape space) of the regression line. */
  const vnl_vector<double> &GetSlope() const
  { return m_Slope; }
  vnl_vector<double> &GetSlope()
  { return m_Slope; }

  /** Returns the intercept (in shape space) of the regression line. */
  const vnl_vector<double> &GetIntercept() const
  { return m_Intercept; }
  vnl_vector<double> GetIntercept()
  { return m_Intercept; }

  /** Sets the slope (in shape space) of the regression line. */  
  void SetSlope(const std::vector<double> &v);
  void SetSlope(const vnl_vector<double> &v)
  {
    m_Slope = v;
  }
  
  /** Sets the intercept (in shape space) of the regression line. */
  void SetIntercept(const std::vector<double> &v);
  void SetIntercept(const vnl_vector<double> &v)
  {
    m_Intercept = v;
  }

  /** Estimates the linear regression parameters (slope and intercept)
      in shape space. */
  virtual void EstimateParameters();
  
  /** Initialize some parameters.  This method should be invoked
      before any optimization is run that depends on this class. */
  virtual void Initialize();

  /** Invoked before an iteration of an optimization that depends on
      this class. */  
  virtual void BeforeIteration();

  /** Set / Get the interval between estimations of the regression
      model.  The units are number of optimizer iterations. For
      example, if you are running an optimization in which you only
      want this class to update every 10 iterations, then you would
      set this value to 10.  */ 
  void SetRegressionInterval( int i)
  {    m_RegressionInterval = i;  }
  int GetRegressionInterval() const
  { return m_RegressionInterval; }
  
protected:
  PSMRegressionShapeMatrixAttribute() 
  {
    this->m_DefinedCallbacks.DomainAddEvent      = true;
    this->m_DefinedCallbacks.PositionAddEvent    = true;
    this->m_DefinedCallbacks.PositionSetEvent    = true;
    this->m_DefinedCallbacks.PositionRemoveEvent = true;
    m_UpdateCounter = 0;
    m_RegressionInterval = 1;
  }
  virtual ~PSMRegressionShapeMatrixAttribute() {};

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  { Superclass::PrintSelf(os,indent);  }

private:
  PSMRegressionShapeMatrixAttribute(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  int m_UpdateCounter;
  int m_RegressionInterval;

  // Parameters for the linear model
  vnl_vector<double> m_Intercept;
  vnl_vector<double> m_Slope;

  // The explanatory variable value for each sample (matrix column)
  vnl_vector<double> m_Explanatory;

  // A matrix to store the mean estimated for each explanatory variable (each sample)
  vnl_matrix<double> m_MeanMatrix;
};



#ifndef ITK_MANUAL_INSTANTIATION
#include "PSMRegressionShapeMatrixAttribute.hxx"
#endif

#endif
