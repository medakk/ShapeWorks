#ifndef __PSMNeighborhood_h
#define __PSMNeighborhood_h

#include <itkDataObject.h>
#include <itkPoint.h>
#include <itkWeakPointer.h>
#include "PSMDomain.h"
#include "PSMContainer.h"
#include "PSMPointIndexPair.h"
#include <vector>

//using namespace itk;


/** \class PSMNeighborhood
 *
 * A PSMNeighborhood is responsible for computing neighborhoods of
 * particles.  Given a point position in a domain, and a neighborhood radius,
 * the PSMNeighborhood returns a list of points that are neighbors of that
 * point.  The base class, PSMNeighborhood, must be subclassed to provide
 * functionality; the base class will throw an exception when
 * FindNeighborhoodPoints is called.
 *
 * \ingroup PSM
 *
 */
template <unsigned int VDimension>
class PSMNeighborhood : public itk::DataObject
{
public:
  /** Standard class typedefs */
  typedef PSMNeighborhood Self;
  typedef itk::DataObject Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMNeighborhood, itk::DataObject);
  
  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);
  
  /** Point type used to store particle locations. */
  typedef itk::Point<double, VDimension> PointType;
  
  /** Domain type.  The Domain object provides bounds and distance
      information. */
  typedef PSMDomain<VDimension> DomainType;
  
  /** Container type for points.  This matches the itkPSMParticleSystem container
      type. */
  typedef PSMContainer<PointType> PointContainerType;
  
  /** Point list (vector) type.  This is the type of list returned by
      FindNeighborhoodPoints. */
  typedef std::vector<PSMPointIndexPair<VDimension> > PointVectorType;
  
  /** Set/Get the point container.  These are the points parsed by the
      Neighborhood class when FindNeighborhoodPoints is called. */
  itkSetObjectMacro(PointContainer, PointContainerType);
  itkGetConstObjectMacro(PointContainer, PointContainerType);
  
  /** Compile a list of points that are within a specified radius of a
      given point.  The default implementation will throw an
      exception. */
  virtual PointVectorType FindNeighborhoodPoints(const PointType &, double) const
  {
    itkExceptionMacro("No algorithm for finding neighbors has been specified.");
  }
  /** This method finds neighborhood points as in the previous method,
      but also computes a vector of weights associated with each of
      those points. */
  virtual PointVectorType FindNeighborhoodPointsWithWeights(const PointType &, std::vector<double> &,
                                                 double) const
  {
    itkExceptionMacro("No algorithm for finding neighbors has been specified.");
  }
//  virtual unsigned int  FindNeighborhoodPoints(const PointType &, double, PointVectorType &) const
//  {
//    itkExceptionMacro("No algorithm for finding neighbors has been specified.");
//    return 0;
//  }
  
  /** Set the Domain that this neighborhood will use.  The Domain
      object is important because it defines bounds and distance
      measures. */
  itkSetObjectMacro(Domain, DomainType);
  itkGetConstObjectMacro(Domain, DomainType);
  
  /**  For efficiency, itkNeighborhoods are not necessarily observers
       of itkPSMParticleSystem, but have specific methods invoked for
       various events.  AddPosition is called by itkPSMParticleSystem
       when a particle location is added.  SetPosition is called when
       a particle location is set.  RemovePosition is called when a
       particle location is removed.*/
  virtual void AddPosition(const PointType &, unsigned int, int ) {}
  virtual void SetPosition(const PointType &, unsigned int, int) {}
  virtual void RemovePosition(unsigned int, int) {}
  
protected:
  PSMNeighborhood() {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }
  virtual ~PSMNeighborhood() {};
  
private:
  PSMNeighborhood(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  typename PointContainerType::Pointer m_PointContainer;
  typename DomainType::Pointer m_Domain;
};



#endif
