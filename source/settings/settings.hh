//../../../settings/settings.hh

#ifndef PLIB_CLASS_settings_all_hh
#define PLIB_CLASS_settings_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "settings/v01/wrapper/import/all.fw"
#include "settings/v01/interface/import/all.fw"
//#include "settings/settings.fw"
#else
#include "settings/settings.fw"
#endif


#include <vector>
#include <map>
#include <string>
class Reader;

class AbsSettings
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsSettings(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual bool loadfile(const char *filename)=0;
    
    
    virtual bool loadfile(const char *filename,bool docreate)=0;
    
    
    virtual int getDefBlockCount()=0;
    
    
    virtual std::string getNextDefBlockName()=0;
    
    
    virtual void updateDefBlockNames()=0;
    
    
    virtual void insert(std::string defName,std::string name,std::string value)=0;
    
    
    virtual void set(std::string defName,std::string name,std::string value)=0;
    
    
    virtual void set(std::string defName,std::string name,int i,std::string value)=0;
    
    
    virtual std::string get(std::string defName,std::string name)=0;
    
    
    virtual std::string get(std::string defName,std::string name,int i)=0;
    
    
    virtual bool exists(std::string defName,std::string name)=0;
    
    
    virtual bool exists(std::string defName,std::string name,int i)=0;
    
    
    virtual int getNameCount(std::string defName)=0;
    
    
    virtual int getNameCount(std::string defName,std::string name)=0;
    
    
    virtual std::string getNextName(std::string defName)=0;
    
    
    virtual std::string getNextName(std::string defName,std::string name)=0;
    
    
    virtual std::string getNextValue(std::string defName,std::string name)=0;
    
    
    virtual void save(const char *filename)=0;
    
    
    virtual bool save2(const char *filename)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
class AbsSettings2:public AbsSettings
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsSettings2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};


class Reader;

class AbsMultiSettings
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsMultiSettings(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    virtual int getDefBlockCount()=0;
    
    
    virtual std::string getNextDefBlockName()=0;
    
    
    virtual void updateDefBlockNames()=0;
    
    
    virtual void insert(std::string defName,std::string name,std::string value)=0;
    
    
    virtual void set(std::string defName,std::string name,std::string value)=0;
    
    
    virtual void set(std::string defName,std::string name,int i,std::string value)=0;
    
    
    virtual std::string get(std::string defName,std::string name)=0;
    
    
    virtual std::string get(std::string defName,std::string name,int i)=0;
    
    
    virtual bool exists(std::string defName,std::string name)=0;
    
    
    virtual bool exists(std::string defName,std::string name,int i)=0;
    
    
    virtual std::string getNextName(std::string defName,std::string name)=0;
    
    
    virtual std::string getNextValue(std::string defName,std::string name)=0;
    
    
    virtual void save(const char *filename)=0;
    
    
    virtual bool save2(const char *filename)=0;
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual bool loadfile(const char *filename)=0;
    
    
    virtual bool loadfile(const char *filename,bool docreate)=0;
    
    
    virtual void setSelectedDefBlockName(const char *defBlockName)=0;
    
    
    virtual std::string getSelectedDefBlockName()=0;
    
    
    virtual void insert(std::string name,std::string value)=0;
    
    
    virtual void set(std::string name,std::string value)=0;
    
    
    virtual void set(std::string name,int i,std::string value)=0;
    
    
    virtual std::string get(std::string name)=0;
    
    
    virtual std::string get(std::string name,int i)=0;
    
    
    virtual bool exists(std::string name)=0;
    
    
    virtual bool exists(std::string name,int i)=0;
    
    
    virtual int getNameCount()=0;
    
    
    virtual int getNameCount(std::string name)=0;
    
    
    virtual std::string getNextName()=0;
    
    
    virtual std::string getNextName(std::string name)=0;
    
    
    virtual std::string getNextValue(std::string name)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
class AbsMultiSettings2:virtual public AbsSettings2,public AbsMultiSettings
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsMultiSettings2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};



#endif
#endif
