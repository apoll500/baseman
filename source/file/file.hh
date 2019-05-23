#ifndef PLIB_CLASS_file_all_hh
#define PLIB_CLASS_file_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "file/v01/wrapper/import/all.fw"
#include "file/v01/interface/import/all.fw"
//#include "file/file.fw"
#else
#include "file/file.fw"
#endif


#include <stdio.h>
#include <time.h>


template< class T > class CondCopyControl
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~CondCopyControl(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
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
template< class T > class CondCopyControl2:public CondCopyControl< T >
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~CondCopyControl2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};



#endif
#endif
