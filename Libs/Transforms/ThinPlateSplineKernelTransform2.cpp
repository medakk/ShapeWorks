#ifndef _ThinPlateSplineKernelTransform2_hxx
#define _ThinPlateSplineKernelTransform2_hxx

#include "ThinPlateSplineKernelTransform2.h"


/**
 * ******************* Constructor *******************
 */

template< class TScalarType, unsigned int NDimensions >
void
ThinPlateSplineKernelTransform2< TScalarType, NDimensions >
::ComputeG( const InputVectorType & x, GMatrixType & GMatrix ) const
{
  const TScalarType r = x.GetNorm();
  GMatrix.fill( itk::NumericTraits< TScalarType >::Zero );
  GMatrix.fill_diagonal( r );

} // end ComputeG()


/**
 * ******************* ComputeDeformationContribution *******************
 */

template< class TScalarType, unsigned int NDimensions >
void
ThinPlateSplineKernelTransform2< TScalarType, NDimensions >
::ComputeDeformationContribution(
  const InputPointType & thisPoint, OutputPointType & opp ) const
{
  const unsigned long numberOfLandmarks = this->m_SourceLandmarks->GetNumberOfPoints();
  PointsIterator      sp                = this->m_SourceLandmarks->GetPoints()->Begin();

  for( unsigned long lnd = 0; lnd < numberOfLandmarks; lnd++ )
  {
    InputVectorType   position = thisPoint - sp->Value();
    const TScalarType r        = position.GetNorm();

    for( unsigned int odim = 0; odim < NDimensions; odim++ )
    {
      opp[ odim ] += r * this->m_DMatrix( odim, lnd );
    }
    ++sp;
  }

} // end ComputeDeformationContribution()


#endif
