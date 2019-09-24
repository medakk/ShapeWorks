/*=========================================================================
  Program:   ShapeWorks: Particle-based Shape Correspondence & Visualization
  Module:    $RCSfile: itkParticleContainerArrayAttribute.h,v $
  Date:      $Date: 2011/03/24 01:17:33 $
  Version:   $Revision: 1.2 $
  Author:    $Author: wmartin $

  Copyright (c) 2009 Scientific Computing and Imaging Institute.
  See ShapeWorksLicense.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/
#ifndef _ParticleContainerArrayAttribute_h
#define _ParticleContainerArrayAttribute_h

#include <itkDataObject.h>
#include <itkWeakPointer.h>
#include "ParticleAttribute.h"
#include "ParticleContainer.h"
#include <vector>

//using namespace itk;

/** \class ParticleContainerArrayAttribute
 *  \brief 
 */
template <class T, unsigned int VDimension>
class ParticleContainerArrayAttribute
  : public std::vector<typename ParticleContainer<T>::Pointer >, public ParticleAttribute<VDimension>
{
public:
  /** Standard class typedefs */
  typedef T DataType;
  typedef ParticleContainerArrayAttribute Self;
  typedef ParticleAttribute<VDimension> Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ParticleContainer, ParticleAttribute);

  /** Callbacks that may be defined by a subclass.  If a subclass defines one
      of these callback methods, the corresponding flag in m_DefinedCallbacks
      should be set to true so that the ParticleSystem will know to register
      the appropriate event with this method. */
  virtual void DomainAddEventCallback(Object *, const itk::EventObject &)
  {
    this->resize( this->size() +1);
    this->operator[](this->size() -1) = ParticleContainer<T>::New();
  }

  virtual void PositionAddEventCallback(Object *o, const itk::EventObject &e) 
  {
    const ParticlePositionAddEvent &event
      = dynamic_cast<const ParticlePositionAddEvent &>(e);
    this->operator[](event.GetDomainIndex())->operator[](event.GetPositionIndex()) = 0.0;    
  }

  virtual void PositionRemoveEventCallback(Object *, const itk::EventObject &) 
  {
    // NEED TO IMPLEMENT THIS
  }

  void ZeroAllValues()
  {
    for (unsigned d = 0; d < this->size(); d++)
      {
      for (unsigned int i = 0; i < this->operator[](d)->GetSize(); i++)
        {
        this->operator[](d)->operator[](i) = 0.0;
        }
      
      }
  }

protected:
  ParticleContainerArrayAttribute()
  {
    this->m_DefinedCallbacks.DomainAddEvent = true;
    this->m_DefinedCallbacks.PositionAddEvent = true;
    this->m_DefinedCallbacks.PositionRemoveEvent = true;
  }
  virtual ~ParticleContainerArrayAttribute() {};

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {  Superclass::PrintSelf(os,indent);  }
  
 private:
  ParticleContainerArrayAttribute(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
};



#endif
