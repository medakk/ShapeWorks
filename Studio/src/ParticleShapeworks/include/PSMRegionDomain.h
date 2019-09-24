#ifndef __PSMRegionDomain_h
#define __PSMRegionDomain_h

#include <itkDataObject.h>
#include "PSMDomain.h"
#include <itkPoint.h>
#include <itkWeakPointer.h>
#include <itkExceptionObject.h>

//using namespace itk;


/** \class PSMRegionDomain
 *  \brief 
 */
template <unsigned int VDimension>
class PSMRegionDomain : public PSMDomain<VDimension>
{
public:
  /** Standard class typedefs */
  typedef PSMRegionDomain Self;
  typedef PSMDomain<VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMRegionDomain, PSMDomain);

  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);

  /** Point type used to store particle locations. */
  typedef itk::Point<double, VDimension> PointType;

  /** Apply any constraints to the given point location.  This method may, for
      example, implement boundary conditions or restrict points to lie on a
      surface.  This class will throw an exception if the point is outside of
      the region.  To specify other behaviors, create a subclass and override
      this method. */
  virtual bool ApplyConstraints(PointType &p) const
  {
    for (unsigned int i = 0; i < VDimension; i++)
      {
        if ( p[i] < m_LowerBound[i]  || p[i] > m_UpperBound[i])
          {
            itkExceptionMacro(<< "Point " << p << " is outside of the specified Domain,  with bounding box "
                              <<  m_LowerBound << " - " << m_UpperBound
                              << std::endl;);
            
          }
      }
    return false;
  }

  /** Set the lower/upper bound of the bounded region. */
  itkSetMacro(LowerBound, PointType);
  itkSetMacro(UpperBound, PointType);
  virtual const PointType &GetUpperBound() const
  { return m_UpperBound; }
  virtual const PointType &GetLowerBound() const
  { return m_LowerBound; }
  
  /** Specify the lower and upper bounds (1st and 2nd parameters, respectively)
      of the region. */
  void SetRegion(const PointType &l, const PointType &u)
  {
    this->SetLowerBound(l);
    this->SetUpperBound(u);
  }
  
protected:
  PSMRegionDomain() {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
    os << "LowerBound = " << m_LowerBound << std::endl;
    os << "UpperBound = " << m_UpperBound << std::endl;
  }
  virtual ~PSMRegionDomain() {};
  
private:
  PSMRegionDomain(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  PointType m_LowerBound;
  PointType m_UpperBound;

};

#endif
