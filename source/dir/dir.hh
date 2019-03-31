#ifndef PLIB_CLASS_dir_all_hh
#define PLIB_CLASS_dir_all_hh

//Interfaces
template< class T > class DIRECTORY;

template< class T > class TreeWalkCallback;


//Factories
class DIRECTORYInterface;

class TreeWalkCallbackInterface;

//Foreward declartions of classes
template<class T> class CondCopyControl;



template< class T > class DIRECTORY
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~DIRECTORY(){}
    //METHODS-----------------------------------------------------------
    
    
    virtual T *read()=0;
    
    
    virtual bool item_isdir()=0;
    
    
    virtual void dirsep()=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};




template< class T > class TreeWalkCallback
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~TreeWalkCallback(){}
    //METHODS-----------------------------------------------------------
    
    
    virtual bool tw_callback(const T * path)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};

#endif
