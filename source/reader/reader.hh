//../../../reader/reader.hh

#ifndef PLIB_CLASS_reader_all_hh
#define PLIB_CLASS_reader_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "reader/v01/wrapper/import/all.fw"
#include "reader/v01/interface/import/all.fw"
//#include "reader/reader.fw"
#else
#include "reader/reader.fw"
#endif


#define READER_COMPMODE_OFF 0
#define READER_COMPMODE_STD 1
#define READER_COMPMODE_EXT 2
#include <uchar.h>


class Reader
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~Reader(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual int getLine()=0;
    
    
    virtual int getColumn()=0;
    
    
    virtual int get()=0;
    
    
    virtual int getChar()=0;
    
    
    virtual int getLastError()=0;
    
    
    virtual int getLastErrorDetail()=0;
    
    
    virtual void resetLastError()=0;
    
    
    virtual int getCurrLine()=0;
    
    
    virtual int getCurrColumn()=0;
    
    
    virtual void setCurrLine(int n)=0;
    
    
    virtual void setCurrColumn(int n)=0;
    
    //GETTER METHODS----------------------------------------------------
    virtual int get_currcolumn()=0;
    virtual int get_currline()=0;
    virtual int get_line_break_char()=0;
    virtual int get_compatibility_mode()=0;
    //SETTER METHODS----------------------------------------------------
    virtual void set_currcolumn(int value)=0;
    virtual void set_currline(int value)=0;
    virtual void set_line_break_char(int value)=0;
    virtual void set_compatibility_mode(int value)=0;
};
class Reader2:public Reader
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    int currcolumn;
    int currline;
    int line_break_char;
    int compatibility_mode;
    //DESTRUCTOR--------------------------------------------------------
    virtual ~Reader2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    virtual int get_currcolumn()
    {
        return currcolumn;
    }
    virtual int get_currline()
    {
        return currline;
    }
    virtual int get_line_break_char()
    {
        return line_break_char;
    }
    virtual int get_compatibility_mode()
    {
        return compatibility_mode;
    }
    //SETTER METHODS----------------------------------------------------
    virtual void set_currcolumn(int value)
    {
        currcolumn=value;
    }
    virtual void set_currline(int value)
    {
        currline=value;
    }
    virtual void set_line_break_char(int value)
    {
        line_break_char=value;
    }
    virtual void set_compatibility_mode(int value)
    {
        compatibility_mode=value;
    }
};


#include <uchar.h>

class AbsUniFileReader
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsUniFileReader(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    virtual int getLine()=0;
    
    
    virtual int getColumn()=0;
    
    
    virtual int get()=0;
    
    
    virtual int getChar()=0;
    
    
    virtual int getLastError()=0;
    
    
    virtual int getLastErrorDetail()=0;
    
    
    virtual void resetLastError()=0;
    
    
    virtual int getCurrLine()=0;
    
    
    virtual int getCurrColumn()=0;
    
    
    virtual void setCurrLine(int n)=0;
    
    
    virtual void setCurrColumn(int n)=0;
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    virtual int get_currcolumn()=0;
    virtual int get_currline()=0;
    virtual int get_line_break_char()=0;
    virtual int get_compatibility_mode()=0;
    //SUPERCLASS SETTER METHODS-----------------------------------------
    virtual void set_currcolumn(int value)=0;
    virtual void set_currline(int value)=0;
    virtual void set_line_break_char(int value)=0;
    virtual void set_compatibility_mode(int value)=0;
    //METHODS-----------------------------------------------------------
    
    virtual int getCharSize()=0;
    
    
    virtual void setCharSize(int csize)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
class AbsUniFileReader2:virtual public Reader2,public AbsUniFileReader
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsUniFileReader2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    virtual int get_currcolumn()
    {
        return currcolumn;
    }
    virtual int get_currline()
    {
        return currline;
    }
    virtual int get_line_break_char()
    {
        return line_break_char;
    }
    virtual int get_compatibility_mode()
    {
        return compatibility_mode;
    }
    //SUPERCLASS SETTER METHODS-----------------------------------------
    virtual void set_currcolumn(int value)
    {
        currcolumn=value;
    }
    virtual void set_currline(int value)
    {
        currline=value;
    }
    virtual void set_line_break_char(int value)
    {
        line_break_char=value;
    }
    virtual void set_compatibility_mode(int value)
    {
        compatibility_mode=value;
    }
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};



#endif
#endif
