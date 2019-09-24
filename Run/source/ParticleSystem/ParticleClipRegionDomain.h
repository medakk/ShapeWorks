/*=========================================================================
  Program:   ShapeWorks: Particle-based Shape Correspondence & Visualization
  Module:    $RCSfile: itkParticleClipRegionDomain.h,v $
  Date:      $Date: 2009/05/06 21:49:15 $
  Version:   $Revision: 1.1.1.1 $
  Author:    $Author: cates $

  Copyright (c) 2009 Scientific Computing and Imaging Institute.
  See ShapeWorksLicense.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/
#ifndef _ParticleClipRegionDomain_h
#define _ParticleClipRegionDomain_h

#include <itkDataObject.h>
#include "ParticleRegionDomain.h"
#include <itkPoint.h>
#include <itkWeakPointer.h>
#include <itkExceptionObject.h>

//using namespace itk;



/** \class ParticleClipRegionDomain
 *  \brief 
 */
template <unsigned int VDimension=3>
class ParticleClipRegionDomain : public ParticleRegionDomain<VDimension>
{
public:
  /** Standard class typedefs */
  typedef ParticleClipRegionDomain Self;
  typedef ParticleRegionDomain<VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ParticleClipRegionDomain, itk::DataObject);

  /** Dimensionality of the domain of the particle system. */
  itkStaticConstMacro(Dimension, unsigned int, VDimension);

  /** Point type used to store particle locations. */
  typedef itk::Point<double, VDimension> PointType;

  /** Apply any constraints to the given point location.  This method may, for
      example, implement boundary conditions or restrict points to lie on a
      surface.  This class will clip the point to the boundaries. */
  virtual bool ApplyConstraints(PointType &p) const
  {
    bool flag = false;
    for (unsigned int i = 0; i < VDimension; i++)
      {
      if ( p[i] < this->GetLowerBound()[i] )
        {
        p[i] = this->GetLowerBound()[i];
        flag = true;
        }
      else if ( p[i] >= this->GetUpperBound()[i])
        {
        p[i] = this->GetUpperBound()[i];
        flag = true;
        }
      }

    return flag;
  }

protected:
  ParticleClipRegionDomain() {}
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }
  virtual ~ParticleClipRegionDomain() {};
  
private:
  ParticleClipRegionDomain(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};




#if ITK_TEMPLATE_EXPLICIT
//# include "Templates/itkParticleClipRegionDomain+-.h"
#endif

#if ITK_TEMPLATE_TXX
//# include "ParticleClipRegionDomain.txx"
#endif

#endif
