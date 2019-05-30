//../../../csv/csv.hh

#ifndef PLIB_CLASS_csv_all_hh
#define PLIB_CLASS_csv_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "csv/v01/wrapper/import/all.fw"
#include "csv/v01/interface/import/all.fw"
//#include "csv/csv.fw"
#else
#include "csv/csv.fw"
#endif


#include <stdio.h>
class Reader;

class AbsCsvField
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvField(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual int load(Reader *reader)=0;
    
    
    virtual char *get()=0;
    
    
    virtual void set(const char *val)=0;
    
    
    virtual void print(FILE *f)=0;
    
    
    virtual void print(FILE *f,const char *val)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
class AbsCsvField2:public AbsCsvField
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvField2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};




class AbsCsvRecord
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvRecord(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual int load(Reader *reader)=0;
    
    
    virtual void addField()=0;
    
    
    virtual int get_record_size()=0;
    
    
    virtual int match(int col,const char *val)=0;
    
    
    virtual int match(const char *val)=0;
    
    
    virtual char *getField(int col)=0;
    
    
    virtual const char *getField_f(int col)=0;
    
    
    virtual bool setField(int col,const char *val)=0;
    
    
    virtual AbsCsvData *getTab()=0;
    
    
    virtual void print(FILE *f)=0;
    
    
    virtual void print(FILE *f,int *col)=0;
    
    
    virtual void print_ln(FILE *f)=0;
    
    
    virtual void print_ln(FILE *f,int *col)=0;
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};
class AbsCsvRecord2:public AbsCsvRecord
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvRecord2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    
    //SETTER METHODS----------------------------------------------------
    
};




class AbsCsvSettings
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvSettings(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    virtual int get_field_seperator_in()=0;
    virtual int get_field_seperator_out()=0;
    virtual int get_record_seperator_in()=0;
    virtual int get_record_seperator_out()=0;
    virtual int get_string_marker_in()=0;
    virtual int get_string_marker_out()=0;
    //SETTER METHODS----------------------------------------------------
    virtual void set_field_seperator_in(int value)=0;
    virtual void set_field_seperator_out(int value)=0;
    virtual void set_record_seperator_in(int value)=0;
    virtual void set_record_seperator_out(int value)=0;
    virtual void set_string_marker_in(int value)=0;
    virtual void set_string_marker_out(int value)=0;
};
class AbsCsvSettings2:public AbsCsvSettings
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    int field_seperator_in;
    int field_seperator_out;
    int record_seperator_in;
    int record_seperator_out;
    int string_marker_in;
    int string_marker_out;
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvSettings2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    virtual int get_field_seperator_in()
    {
        return field_seperator_in;
    }
    virtual int get_field_seperator_out()
    {
        return field_seperator_out;
    }
    virtual int get_record_seperator_in()
    {
        return record_seperator_in;
    }
    virtual int get_record_seperator_out()
    {
        return record_seperator_out;
    }
    virtual int get_string_marker_in()
    {
        return string_marker_in;
    }
    virtual int get_string_marker_out()
    {
        return string_marker_out;
    }
    //SETTER METHODS----------------------------------------------------
    virtual void set_field_seperator_in(int value)
    {
        field_seperator_in=value;
    }
    virtual void set_field_seperator_out(int value)
    {
        field_seperator_out=value;
    }
    virtual void set_record_seperator_in(int value)
    {
        record_seperator_in=value;
    }
    virtual void set_record_seperator_out(int value)
    {
        record_seperator_out=value;
    }
    virtual void set_string_marker_in(int value)
    {
        string_marker_in=value;
    }
    virtual void set_string_marker_out(int value)
    {
        string_marker_out=value;
    }
};


class Reader;

class AbsCsvData
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvData(){}
    //SUPERCLASS METHODS------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //METHODS-----------------------------------------------------------
    
    virtual int load(const char *filename,const char *docreate)=0;
    
    
    virtual int load(const char *filename)=0;
    
    #ifdef OS_WIN
    virtual int load(const wchar_t *filename,const char *docreate)=0;
    #endif
    #ifdef OS_WIN
    virtual int load(const wchar_t *filename)=0;
    #endif
    
    virtual int load(Reader *reader)=0;
    
    
    virtual AbsCsvRecord *load_rec(Reader *reader)=0;
    
    
    virtual int get_record_count()=0;
    
    
    virtual void useHeader(bool h)=0;
    
    
    virtual int getHeaderId(const char *column_name)=0;
    
    
    virtual char *getHeader(int col)=0;
    
    
    virtual bool setField(int row,int col,const char *val)=0;
    
    
    virtual bool setField(int row,const char *column_name,const char *val)=0;
    
    
    virtual int addRecord()=0;
    
    
    virtual int addRecord(int fldcount)=0;
    
    
    virtual bool addFieldToRecord(int row)=0;
    
    
    virtual AbsCsvRecord *getRecord(int col,const char *val)=0;
    
    
    virtual AbsCsvRecord *getRecord(int *col,const char **val)=0;
    
    
    virtual AbsCsvRecord *getRecord(int row)=0;
    
    
    virtual AbsCsvRecord *getRecord(const char *column_name,const char *val)=0;
    
    
    virtual AbsCsvRecord *getRecord(const char **column_name,const char **val)=0;
    
    
    virtual AbsCsvRecord **getAllRecords(int col,const char *val)=0;
    
    
    virtual AbsCsvRecord **getAllRecords()=0;
    
    
    virtual AbsCsvRecord **getAllRecords(const char *column_name,const char *val)=0;
    
    
    virtual bool save(const char *filename)=0;
    
    
    virtual void print(FILE *f)=0;
    
    
    virtual void print(FILE *f,int *row,int *col)=0;
    
    //GETTER METHODS----------------------------------------------------
    virtual AbsCsvSettings *get_settings()=0;
    //SETTER METHODS----------------------------------------------------
    virtual void set_settings(AbsCsvSettings *value)=0;
};
class AbsCsvData2:public AbsCsvData
{
private:
    //PRIVATE MEMBERS---------------------------------------------------
    
protected:
    //PROTECTED MEMBERS-------------------------------------------------
    
public:
    //PUBLIC MEMBERS----------------------------------------------------
    AbsCsvSettings *settings;
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsCsvData2(){}
    //METHODS-----------------------------------------------------------
    
    //SUPERCLASS GETTER METHODS-----------------------------------------
    
    //SUPERCLASS SETTER METHODS-----------------------------------------
    
    //GETTER METHODS----------------------------------------------------
    virtual AbsCsvSettings *get_settings()
    {
        return settings;
    }
    //SETTER METHODS----------------------------------------------------
    virtual void set_settings(AbsCsvSettings *value)
    {
        settings=value;
    }
};



#endif
#endif
