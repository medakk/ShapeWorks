#ifndef __PSMRegionNeighborhood_h
#define __PSMRegionNeighborhood_h

#include "PSMNeighborhood.h"
#include "PSMPointTree.h"

//using namespace itk;


/** \class PSMRegionNeighborhood
 *
 * PSMRegionNeighborhood is a general purpose neighborhood object that
 * computes neighborhoods based on distance from a point.  It requires a domain
 * that provides bounds information and a distance metric.  This class uses a
 * PSMPointTree to cache point and index values so that
 * FindNeighborhoodPoints is somewhat optimized. 
 */
template <unsigned int VDimension>
class PSMRegionNeighborhood : public PSMNeighborhood<VDimension>
{
public:
  /** Standard class typedefs */
  typedef PSMRegionNeighborhood Self;
  typedef PSMNeighborhood<VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMRegionNeighborhood, PSMNeighborhood);
  
  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);
  
  /** Inherited typedefs from parent class. */
  typedef typename Superclass::PointType PointType;
  typedef typename Superclass::PointContainerType PointContainerType;
  typedef typename Superclass::DomainType DomainType;
  typedef typename Superclass::PointVectorType PointVectorType;
  
  /** PSMTree type used to sort points according to location. */
  typedef PSMPointTree<VDimension> PointTreeType;
  
  /** Compile a list of points that are within a specified radius of a given
      point.  This implementation uses a PSMTree to sort points
      according to location. */
  virtual PointVectorType FindNeighborhoodPoints(const PointType &, double) const;
  
  /** Override SetDomain so that we can grab the region extent info and
      construct our tree. */
  virtual void SetDomain( DomainType *p);
  
  /** Set/Get the number of levels in the sorting tree.  */
  itkSetMacro(TreeLevels, unsigned int);
  itkGetMacro(TreeLevels, unsigned int);

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    os << indent << "m_TreeLevels = " << m_TreeLevels << std::endl;
    m_Tree->PrintSelf(os, indent);
    Superclass::PrintSelf(os, indent);
  }

  /**For efficiency, itkNeighborhoods are not necessarily observers of
     itkPSMParticleSystem, but have specific methods invoked for various events.
     AddPosition is called by itkPSMParticleSystem when a particle location is
     added.  SetPosition is called when a particle location is set.
     RemovePosition is called when a particle location is removed.*/
  void AddPosition(const PointType &p, unsigned int idx, int threadId = 0);
  void SetPosition(const PointType &p, unsigned int idx, int threadId = 0);
  void RemovePosition(unsigned int idx, int threadId = 0);
  
protected:
  PSMRegionNeighborhood() : m_TreeLevels(3)
  {
    m_Tree = PointTreeType::New();
    m_IteratorMap = IteratorMapType::New();
  }
  virtual ~PSMRegionNeighborhood() {};

  /** Map for direct reference of PointIndexPairs and Tree nodes from the
      PointTree.  This is used for fast removal or modification of point
      values. */
  struct IteratorNodePair
  {
    typedef typename PointTreeType::NodePointerType NodePointerType;
    typedef typename PointTreeType::PointListType::iterator IteratorType;

    IteratorNodePair() {}
    ~IteratorNodePair() {}
    IteratorNodePair(const IteratorType &p, const NodePointerType &n)
    {
      Iterator = p;
      NodePointer = n;
    }
   
    IteratorNodePair(const IteratorNodePair &o)
    { this->operator=(o); }
    const IteratorNodePair &operator=(const IteratorNodePair &o)
    {
      Iterator = o.Iterator;
      NodePointer = o.NodePointer;
      return *this;
    }

    IteratorType Iterator;
    NodePointerType NodePointer;
 };
  
  typedef PSMContainer<IteratorNodePair> IteratorMapType;

protected:
  typename PointTreeType::Pointer m_Tree;
  typename IteratorMapType::Pointer m_IteratorMap;
  unsigned int m_TreeLevels;

 
private:
  PSMRegionNeighborhood(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};



#ifndef ITK_MANUAL_INSTANTIATION
#include "PSMRegionNeighborhood.hxx"
#endif

#endif
