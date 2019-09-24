#ifndef __PSMContainerArrayAttribute_h
#define __PSMContainerArrayAttribute_h

#include <itkDataObject.h>
#include <itkWeakPointer.h>
#include "PSMAttribute.h"
#include "PSMContainer.h"
#include <vector>

//using namespace itk;


/** \class PSMContainerArrayAttribute
 * \brief 
 * \ingroup PSM
 * \ingroup PSMAttributes
 */
template <class T, unsigned int VDimension>
class PSMContainerArrayAttribute
  : public std::vector<typename PSMContainer<T>::Pointer >,
  public PSMAttribute<VDimension>
{
public:
  /** Standard class typedefs */
  typedef T DataType;
  typedef PSMContainerArrayAttribute Self;
  typedef PSMAttribute<VDimension> Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  typedef itk::WeakPointer<const Self>  ConstWeakPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMContainerArrayAttribute, PSMAttribute);

  /** Callbacks that may be defined by a subclass.  If a subclass defines one
      of these callback methods, the corresponding flag in m_DefinedCallbacks
      should be set to true so that the ParticleSystem will know to register
      the appropriate event with this method. */
  virtual void DomainAddEventCallback(Object *, const itk::EventObject &)
  {
    this->resize( this->size() +1);
    this->operator[](this->size() -1) = PSMContainer<T>::New();
  }

  virtual void PositionAddEventCallback(Object *, const itk::EventObject &e) 
  {
    const ParticlePositionAddEvent &event
      = dynamic_cast<const ParticlePositionAddEvent &>(e);
    this->operator[](event.GetDomainIndex())->operator[](event.GetPositionIndex()) = 0.0;    
  }

  virtual void PositionRemoveEventCallback(Object *, const itk::EventObject &) 
  {
    itkExceptionMacro("This class does note support removal of particles positions.");
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
  PSMContainerArrayAttribute()
    {
      this->m_DefinedCallbacks.DomainAddEvent = true;
      this->m_DefinedCallbacks.PositionAddEvent = true;
      this->m_DefinedCallbacks.PositionRemoveEvent = true;
    }
  virtual ~PSMContainerArrayAttribute() {};
  
  void PrintSelf(std::ostream& os, itk::Indent indent) const
  {  Superclass::PrintSelf(os,indent);  }
  
 private:
  PSMContainerArrayAttribute(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
};
 
#endif
