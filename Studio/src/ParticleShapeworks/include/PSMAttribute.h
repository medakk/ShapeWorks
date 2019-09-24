#ifndef __PSMAttribute_h
#define __PSMAttribute_h

#include <itkDataObject.h>
#include <itkPoint.h>
#include <itkWeakPointer.h>
#include <itkCommand.h>
#include "PSMEvents.h"

//using namespace itk;

/** \class PSMAttribute
 *  \brief Base class for PSMParticleSystem attribute classes.
 * \ingroup ParticleShapeModeling
 */
template< unsigned int VDimension>
class PSMAttribute : public itk::DataObject
{
public:
  /** Standard class typedefs */
  typedef PSMAttribute Self;
  typedef itk::DataObject Superclass;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMAttribute, itk::DataObject);

  /** Data structure indicating which callback functions are defined by a
      subclass.  The PSMParticleSystem class will reference this structure to
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
      should be set to true so that the PSMParticleSystem will know to register
      the appropriate event with this method. */
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
  PSMAttribute() {}
  virtual ~PSMAttribute() {};

  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {  Superclass::PrintSelf(os,indent);  }

private:
  PSMAttribute(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

#endif
