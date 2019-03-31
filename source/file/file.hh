#ifndef PLIB_CLASS_file_all_hh
#define PLIB_CLASS_file_all_hh

//Interfaces
template< class T > class CondCopyControl;


//Factories
class CondCopyControlInterface;


#include <stdio.h>
#include <time.h>


template< class T > class CondCopyControl
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~CondCopyControl(){}
    //METHODS-----------------------------------------------------------
    
    
    virtual bool doCopyFile(const T * targetpath,const T * sourcepath)=0;
    
    
    virtual void filecopied(const T * targetpath,const T * sourcepath,size_t bytes)=0;
    
    
    virtual bool ignoreEmptyDir(const T * path)=0;
    
    
    virtual void feedback()=0;
    
    
    virtual size_t feedback_bytes()=0;
    
    
    virtual time_t feedback_time()=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};

#endif
