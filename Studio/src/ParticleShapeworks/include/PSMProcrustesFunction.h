#ifndef __PSMProcrustesFunction_h
#define __PSMProcrustesFunction_h

#include <vector>
#include <vnl/vnl_matrix.h>
#include <vnl/vnl_vector_fixed.h>
#include <vnl/vnl_matrix_fixed.h>
#include <itkSmartPointer.h>
#include <itkMacro.h>
#include <itkObject.h>
#include <itkObjectFactory.h>
#include <itkPoint.h>

//using namespace itk;


  /** \class PSMProcrustesFunction
   *  \brief Generalized Procrustes Analysis is the rigid registration between 
   * different input shapes represented by point correspondences to produce an
   * optimal mean shape. One transformation per shape is computed using the 
   * PSMProcrustesFunction. The point sets are registered by translation, rotation 
   * and uniform scaling. Scaling can be turned off if required.
   *  \ingroup PSM
   */
template <unsigned int VDimension>
class PSMProcrustesFunction : public itk::Object
{
  /** This struct stores the transformation per input shape. It consists of a
   rotation, scale and translation component. */
  struct SimilarityTransform3D
  {
    vnl_matrix_fixed<double, VDimension, VDimension> rotation;
    double scale;
    vnl_vector_fixed<double, VDimension> translation;
  };
    
public:
  typedef double                                RealType;
  typedef vnl_vector_fixed<double, VDimension>  PointType;
  typedef std::vector<PointType>                ShapeType;
  typedef typename ShapeType::iterator          ShapeIteratorType;
  typedef std::vector<ShapeType>                ShapeListType;
  typedef typename ShapeListType::iterator      ShapeListIteratorType;
  typedef std::vector<SimilarityTransform3D>    SimilarityTransformListType;
  typedef typename SimilarityTransformListType::iterator SimilarityTransformListIteratorType;
  
  /** Standard class typedefs. */
  typedef PSMProcrustesFunction                 Self;
  typedef Object                                Superclass;
  typedef itk::SmartPointer< Self >                  Pointer;
  typedef itk::SmartPointer< const Self >            ConstPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMProcrustesFunction, Object);

  /** Align a list of shapes using Generalized Procrustes Analysis */
  void RunGeneralizedProcrustes(SimilarityTransformListType & transform,
                                ShapeListType & shapes);

  /** Calculate the sum of squares of the discrepancies between the 
   registered input shapes and the reference shape points. This yields the 
   maximum likelihood estimate. */
  RealType ComputeSumOfSquares(ShapeListType & shapes);

  /** Helper function to transform a shape by a similarity transform */
  ShapeType TransformShape(ShapeType shape, SimilarityTransform3D & transform);
  
private:        
  /** Check if shapes are the same */
  bool CheckDegenerateCase(PointType ssqShape, PointType ssqMean, PointType muShape,
                           PointType muMean, int rows);

  /** Compute mean of all shapes except one */
  void LeaveOneOutMean(ShapeType & mean, ShapeListType & shapeList,
                       ShapeListIteratorType & leaveOutIt);

  /** Compute mean of all shapes */
  void ComputeMean(ShapeType & mean, ShapeListType & shapeList);

  /** Align two shapes (translation, rotation & scale) using ordinary Procrustes
      Analysis */
  ShapeType RunProcrustes(SimilarityTransform3D & transform, ShapeType mean,
                          ShapeListIteratorType & leaveOutIt);
};

#endif
