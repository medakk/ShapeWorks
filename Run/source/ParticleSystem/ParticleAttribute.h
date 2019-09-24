/*=========================================================================
  Program:   ShapeWorks: Particle-based Shape Correspondence & Visualization
  Module:    $RCSfile: itkParticleAttribute.h,v $
  Date:      $Date: 2011/03/24 01:17:33 $
  Version:   $Revision: 1.2 $
  Author:    $Author: wmartin $

  Copyright (c) 2009 Scientific Computing and Imaging Institute.
  See ShapeWorksLicense.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/
#ifndef _ParticleAttribute_h
#define _ParticleAttribute_h

#include <itkDataObject.h>
#include <itkPoint.h>
#include <itkWeakPointer.h>
#include <itkCommand.h>
#include "ParticleEvents.h"

//using namespace itk;


#ifndef _ParticleSystem_h
template<unsigned int VDimension> class ParticleSystem;
#endif

/** \class ParticleAttribute
 *  \brief 
 */
template< unsigned int VDimension>
class ParticleAttribute : public itk::DataObject
{
public:
  /** Standard class typedefs */
  typedef ParticleAttribute Self;
  typedef itk::DataObject Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ParticleAttribute, itk::DataObject);

  /** Data structure indicating which callback functions are defined by a
      subclass.  The ParticleSystem class will reference this structure to
      determine which callbacks to register.  This is just a list of every
      event defined in itkParticleEvent.h */
  struct DefinedCallbacksStruct
  {
    DefinedCallbacksStruct() : Event(false),
                               EventWithIndex(false),
                               DomainAddEvent(false),
                               TransformSetEvent(false),
                               PrefixTransformSetEvent(false),
                               NeighborhoodSetEvent(false),
                               PositionSetEvent(false),
                               PositionAddEvent(false),
                               PositionRemoveEvent(false) {}
    bool Event;
    bool EventWithIndex;
    bool DomainAddEvent;
    bool TransformSetEvent;
    bool PrefixTransformSetEvent;
    bool NeighborhoodSetEvent;
    bool PositionSetEvent;
    bool PositionAddEvent;
    bool PositionRemoveEvent;
  };
  
  DefinedCallbacksStruct  m_DefinedCallbacks;

  /** Callbacks that may be defined by a subclass.  If a subclass defines one
      of these callback methods, the corresponding flag in m_DefinedCallbacks
      should be set to true so that the ParticleSystem will know to register
      the appropriate event with this method. */
//   virtual void EventCallback(ParticleSystem<VDimension> *, const ParticleEvent &) {}
//   virtual void EventWithIndexCallback(ParticleSystem<VDimension> *, const ParticleEventWithIndex &) {}
//   virtual void DomainAddEventCallback(ParticleSystem<VDimension> *, const ParticleDomainAddEvent &) {}

//   virtual void TransformSetEventCallback(ParticleSystem<VDimension> *, const ParticleTransformSetEvent &) {}
//   virtual void NeighborhoodSetEventCallback(ParticleSystem<VDimension> *, const ParticleNeighborhoodSetEvent &) {}
//   virtual void PositionSetEventCallback(ParticleSystem<VDimension> *, const ParticlePositionSetEvent &) {}
//   virtual void PositionAddEventCallback(ParticleSystem<VDimension> *, const ParticlePositionAddEvent &) {}
//   virtual void PositionRemoveEventCallback(ParticleSystem<VDimension> *,
//   const ParticlePositionRemoveEvent &) {}

  virtual void EventCallback(Object *, const itk::EventObject &) {}
  virtual void EventWithIndexCallback(Object *, const itk::EventObject &) {}
  virtual void DomainAddEventCallback(Object *, const itk::EventObject &) {}
  virtual void TransformSetEventCallback(Object *, const itk::EventObject &) {}
  virtual void PrefixTransformSetEventCallback(Object *, const itk::EventObject &) {}
  virtual void NeighborhoodSetEventCallback(Object *, const itk::EventObject &) {}
  virtual void PositionSetEventCallback(Object *, const itk::EventObject &) {}
  virtual void PositionAddEventCallback(Object *, const itk::EventObject &) {}
  virtual void PositionRemoveEventCallback(Object *, const itk::EventObject &) {}

protected:
  ParticleAttribute() {}
  virtual ~ParticleAttribute() {};

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {  Superclass::PrintSelf(os,indent);  }

private:
  ParticleAttribute(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};




//#if ITK_TEMPLATE_EXPLICIT
//# include "Templates/itkParticleAttribute+-.h"
//#endif

//#if ITK_TEMPLATE_TXX
//# include "ParticleAttribute.txx"
//#endif

#endif
