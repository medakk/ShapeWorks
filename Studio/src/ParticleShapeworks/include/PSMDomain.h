#ifndef __PSMDomain_h
#define __PSMDomain_h

#include <itkDataObject.h>
#include <itkObjectFactory.h>
#include <itkPoint.h>
#include <itkWeakPointer.h>

//using namespace itk;


/** \class PSMDomain 
 * 
 *  \brief Base class for defining the domain in which a particle
 *  system exists.
 *
 *  The PSMDomain class is an abstract base class for defining
 *  the domain in which a particle system exists.  It is intended to
 *  be subclassed to fully define the domain characteristics.
 *
 *  A domain defines a distance metric between two points.  By
 *  default, distance is defined in this base class as a Euclidean
 *  distance. PSMDomain subclasses may also define constraints on
 *  particle positions, such as constraints forcing particles to lie
 *  on a surface (submanifold of the domain).  PSMDomain
 *  subclasses may also define boundaries using the BoundingBox
 *  methods.
 * 
 *  \ingroup ParticleShapeModeling
 */
template <unsigned int VDimension>
class PSMDomain : public itk::DataObject
{
public:
  /** Standard class typedefs */
  typedef PSMDomain Self;
  typedef itk::DataObject Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMDomain, itk::DataObject);

  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);

  /** Point type used to store particle locations. */
  typedef itk::Point<double, VDimension> PointType;

  /** Apply any constraints to the given point location.  This method may, for
      example, implement boundary conditions or restrict points to lie on a
      surface.  Default behavior does nothing.  Returns true if the value of
      the point was modified and false otherwise. */
  virtual bool ApplyConstraints(PointType &) const
  {  return false; }

  /** A Domain may define a distance calculation.  This is useful in cases
      such as geodesic distance, where distance depends on some information
      contained in the Domain.  The default implementation is Euclidean
      distance. */
  virtual double Distance(const PointType &a, const PointType &b) const
  {
    double sum = 0.0;
    for (unsigned int i = 0; i < VDimension; i++)
      {      
        sum += (b[i]-a[i]) * (b[i]-a[i]);      
      }
    return sqrt(sum);
  }
  
  /** A Domain may optionally return a bounding box.  The lower bound method
      gives the upper-left-hand corner of the domain.  The upper bound method
      gives the lower-right-hand-corner of the domain.  If a domain does not
      define boundaries, these methods will throw an exceptions  */
  virtual const PointType &GetLowerBound() const
  {
    itkExceptionMacro("This Domain does not define a lower bound.");
  }
  virtual const PointType &GetUpperBound() const
  {
    itkExceptionMacro("This Domain does not define an upper bound.");
  }

 /** Enable/Disable constraints on particle positions imposed by a domain. */
  void DisableConstraints()  { m_ConstraintsEnabled = false; }
  void EnableConstraints()   { m_ConstraintsEnabled = true; }    
  bool GetConstraintsEnabled() const  { return m_ConstraintsEnabled; }
  void SetConstraintsEnabled( bool g )  { m_ConstraintsEnabled = g; }

  
protected:
  PSMDomain();
  void PrintSelf(std::ostream& os, itk::Indent indent) const;
  virtual ~PSMDomain() {}

  bool m_ConstraintsEnabled;
  
private:
  PSMDomain(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};



#ifndef ITK_MANUAL_INSTANTIATION
#include "PSMDomain.hxx"
#endif

#endif
