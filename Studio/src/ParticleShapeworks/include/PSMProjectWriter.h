#ifndef __PSMProjectWriter_h
#define __PSMProjectWriter_h

#include "PSMProject.h"

//using namespace itk;



/**
 * \class PSMProjectWriter
 *
 * \brief This class is a writer for PSMProjects. 
 *
 * The following code illustrates how to use this class to write a PSMProject to a file.
 *
 */
class PSMProjectWriter : public Object
{
public:
  /** Standard class typedefs. */
  typedef PSMProjectWriter Self;
  typedef Object           Superclass;
  typedef itk::SmartPointer< Self >       Pointer;
  typedef itk::SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(PSMProjectWriter, Object);

  /** Set the input XML filename. */
  itkSetStringMacro(FileName);
  
  /** Get the input XML filename. */
  itkGetStringMacro(FileName);
  
  /** Get the project data structure generated after calling
      Update(). */
  itkGetObjectMacro( Input, PSMProject);
  itkSetObjectMacro( Input, PSMProject);
  itkGetConstObjectMacro( Input, PSMProject);

  /** Execute the reader. */
  virtual void Update();

 protected:
  PSMProjectWriter();

 private:
  PSMProjectWriter(const Self &); //purposely not implemented
  void operator=(const Self &);   //purposely not implemented

  /** The PSMProject object that will be created by the reader. */
  PSMProject::Pointer m_Input;

  /** The filename of the project to be written. */
  std::string m_FileName;
};

#endif
