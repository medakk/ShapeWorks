#ifndef __PSMPointIndexPair_h
#define __PSMPointIndexPair_h

#include <itkPoint.h>

//using namespace itk;

/**  
 * \class PSMPointIndexPair
 * \brief
 * Struct containing a Point and an index value associated with a
 * point.  This object is used mainly by PSMNeighborhood classes and
 * the PowerOfTwoPointTree.
 * 
 * \ingroup PSM
 *
*/
template <unsigned int VDimension>
struct PSMPointIndexPair
{
  typedef itk::Point<double, VDimension> PointType;
  PSMPointIndexPair() {}
  PSMPointIndexPair(const PointType &p, unsigned int i=0)
  {
    Point = p;
    Index = i;
  }
  PSMPointIndexPair(const PSMPointIndexPair &o)
  { this->operator=(o); }
  const PSMPointIndexPair &operator=(const PSMPointIndexPair &o)
  {
    Point = o.Point;
    Index = o.Index;
	return *this;
  }
  PointType Point;
  unsigned int Index;
};

#endif

