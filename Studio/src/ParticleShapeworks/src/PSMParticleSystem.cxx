#include "PSMParticleSystem.h"

//using namespace itk;

/** For efficiency, we specialize for 3D and 2D */
template<>
PSMParticleSystem<3>::PointType
PSMParticleSystem<3>
::TransformPoint(const PointType &p, const TransformType &T) const
{
  PointType ans;

  ans[0] = T[0][0] * p[0] + T[0][1] * p[1] + T[0][2] * p[2] + T[0][3];
  ans[1] = T[1][0] * p[0] + T[1][1] * p[1] + T[1][2] * p[2] + T[1][3];
  ans[2] = T[2][0] * p[0] + T[2][1] * p[1] + T[2][2] * p[2] + T[2][3];

  return ans;
}

/** For efficiency, we specialize for 3D and 2D */
template<>
PSMParticleSystem<2>::PointType
PSMParticleSystem<2>
::TransformPoint(const PointType &p, const TransformType &T) const
{
  PSMParticleSystem<2>::PointType ans;

  ans[0] = T[0][0] * p[0] + T[0][1] * p[1] + T[0][2];
  ans[1] = T[1][0] * p[0] + T[1][1] * p[1] + T[1][2];

  return ans;
}

/** For efficiency, we specialize for 3D and 2D */
template<>
PSMParticleSystem<3>::VectorType
PSMParticleSystem<3>
::TransformVector(const VectorType &p, const TransformType &T) const
{
  VectorType ans;

  ans[0] = T[0][0] * p[0] + T[0][1] * p[1] + T[0][2] * p[2];
  ans[1] = T[1][0] * p[0] + T[1][1] * p[1] + T[1][2] * p[2];
  ans[2] = T[2][0] * p[0] + T[2][1] * p[1] + T[2][2] * p[2];

  return ans;
}

/** For efficiency, we specialize for 3D and 2D */
template<>
PSMParticleSystem<2>::VectorType
PSMParticleSystem<2>
::TransformVector(const VectorType &p, const TransformType &T) const
{
  VectorType ans;

  ans[0] = T[0][0] * p[0] + T[0][1] * p[1];
  ans[1] = T[1][0] * p[0] + T[1][1] * p[1];

  return ans;
}

