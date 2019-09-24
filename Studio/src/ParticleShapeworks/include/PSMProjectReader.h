#ifndef __PSMProjectReader_h
#define __PSMProjectReader_h

#include "PSMProject.h"
#include "PSMDOMNodeXMLReader.h"

//using namespace itk;



/**
 * \class PSMProjectReader
 *
 * \brief This class is a reader for PSMProjects. 
 *
 * The following code illustrates how to use this class to read a PSMProject from a file:
 *
 * 
 * Note: Though this class behaves similar to ProcessObject, it is not
 *       derived from ProcessObject. This is because the output of
 *       this class, i.e. a PSMProject object, is not an image and
 *       cannot be connected to an ITK process pipeline.
 */
class PSMProjectReader : public PSMDOMNodeXMLReader
{
public:
  /** Standard class typedefs. */
  typedef PSMProjectReader    Self;
  typedef PSMDOMNodeXMLReader Superclass;
  typedef itk::SmartPointer< Self >        Pointer;
  typedef itk::SmartPointer< const Self >  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMProjectReader, PSMDOMNodeXMLReader);

  /** Some convenient typedefs */
  typedef Superclass::DOMNodeType    DOMNodeType;
  typedef Superclass::DOMNodePointer DOMNodePointer;

  /** Get the project data structure generated after calling
      Update(). */
  itkGetObjectMacro( Output, PSMProject);
  itkSetObjectMacro( Output, PSMProject);
  itkGetConstObjectMacro( Output, PSMProject);

  /** Execute the reader. */
  virtual void Update();

 protected:
  PSMProjectReader();

 private:
  PSMProjectReader(const Self &); //purposely not implemented
  void operator=(const Self &); //purposely not implemented

  /** The PSMProject object that will be created by the reader. */
  PSMProject::Pointer m_Output;
};

#endif
