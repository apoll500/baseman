#ifndef PLIB_CLASS_dir_all_hh
#define PLIB_CLASS_dir_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "dir/v01/wrapper/import/all.fw"
#include "dir/v01/interface/import/all.fw"
//#include "dir/dir.fw"
#else
#include "dir/dir.fw"
#endif

template<class T> class CondCopyControl;



template< class T > class DIRECTORY
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~DIRECTORY(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual T *read()=0;
    
    
    virtual bool item_isdir()=0;
    
    
    virtual void dirsep()=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
template< class T > class DIRECTORY2:virtual public DIRECTORY< T >
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~DIRECTORY2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};




template< class T > class TreeWalkCallback
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~TreeWalkCallback(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual bool tw_callback(const T * path)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
template< class T > class TreeWalkCallback2:virtual public TreeWalkCallback< T >
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~TreeWalkCallback2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};



#endif
#endif
