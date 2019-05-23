/*******************************************************************************
*                                                                              *
*  CsvData.cpp                                                                 *
*                                                                              *
*  This file is part of "mods/baseman/cli". (this program)                     *
*                                                                              *
*  This source-file is also part of the prokee-module licensed under GPLv3.    *
*                                                                              *
*  Copyright (C) 2016 - 2019 by Andreas Pollhammer                             *
*                                                                              *
*  Email: apoll500@gmail.com                                                   *
*                                                                              *
*  ==========================================================================  *
*                                                                              *
*  This program is licensed under GPLv3:                                       *
*                                                                              *
*  The prokee-library is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by the    *
*  Free Software Foundation, either version 3 of the License, or (at your      *
*  option) any later version.                                                  *
*                                                                              *
*  This program is distributed in the hope that it will be useful, but WITHOUT *
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
*  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for   *
*  more details.                                                               *
*                                                                              *
*  You should have received a copy of the GNU General Public License           *
*  along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*                                                                              *
*  ==========================================================================  *
*                                                                              *
*  Alternative Licenses/Additional Terms:                                      *
*                                                                              *
*  Alternative licenses or additional terms can be provided on request.        *
*  In case you obtained an alternative license, you are free to use this       *
*  program either according to the obtained license or according to the        *
*  license stated above.                                                       *
*                                                                              *
*******************************************************************************/
#include "CsvData.h"
#include "csv.h"

/**bmc
DEF unique_column:REMARK
{
    text="The comumn names have to be unique. If coumns have the same name, the first matching column will be found.";
}
DEF winonly_remark:REMARK
{
    text="Diese Funktion ist nur unter Windows verfügbar.";
    text_en="This function is available for Windows only.";
}
*/
/**bmc
DEF param_filename:ccp
{
    name="filename";
    direction="IN";
    desc="Filename (incl. path)";
}
DEF param_filenameW:cwp
{
    name="filename";
    direction="IN";
    desc="Filename (incl. path)";
}
DEF param_docreate:ccp
{
    name="docreate";
    direction="IN";
    desc="...";
}
DEF param_Reader:manu
{
    name="reader";
    desc="Pointer to an instance of an implementation of Reader.<br>See <a href='@param_classinfo[]_@version[]_Reader\.php'>@param_classinfo\:Reader</a>.";
    param_classname="Reader";
    param_classinfo="reader";
}
DEF param_colname:ccp
{
    name="column_name";
    direction="IN";
    desc="...";
}
DEF param_colname2:ccpp
{
    name="column_name";
    direction="IN";
    desc="...";
}
DEF param_row:i
{
    name="row";
    desc="Die Zeilennummer (Zählung beginnend mit 0).";
}
DEF param_row2:ip
{
    name="row";
    desc="Number of the row";
}
DEF param_col:i
{
    name="col";
    desc="Die Spaltennummer (Zählung beginnend mit 0).";
}
DEF param_col2:ip
{
    name="col";
    desc="Number of the column";
}
DEF param_val:ccp
{
    name="val";
    direction="IN";
    desc="Value to be stored in filed specified by <code>row</code> and <code>col</code>.";
}
DEF param_val2:ccpp
{
    name="val";
    direction="IN";
    desc="Values.";
}
*/
//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
/**bmc
DEF inc_CsvData
{
    iclass="AbsCsvData";
    class="CsvData";
    function="create@class";
}
DEF CsvData:CONSTRUCTOR,inc_CsvData
{
    AbsCsvData="TRUE";
    CsvData="TRUE";
    brief
    {
        ->
        Provides functionality to load, manage and store csv data.
        <-
    }
    return:vp="Returns an instance of <code>@class</code>\.";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
CsvData::CsvData()
{
    settings=new CsvSettings(',','\n','\"');
    header=false;
    data_memln=CSV_INI_DAT_LENGTH;
    data=(AbsCsvRecord **)malloc((data_memln+1)*sizeof(AbsCsvRecord *));
    data_size=0;
}
/**bmc
DEF destroyCsvData:DESTRUCTOR
{
    CsvData="TRUE";
    class="CsvData";
    function="@this.parent.NAME";
    return:v="";
}
*/
CsvData::~CsvData()
{
    for(int i=0;i<data_size;i++)
    {
        delete data[i];
    }
    delete settings;
}
//------------------------------------------------------------------------------
// Interface
//------------------------------------------------------------------------------
/**bmc
DEF load_str1:ABSTRACT_METHOD
{
    txt_bevore="Loading CSV Files";
    function="load";
    suffix="1";
    brief="Loads a csv-data from a file.";
    param:param_filename{};
    param:param_docreate{};
    return:i="Returns 0 if successful, or a value other than 0 otherwise.";
}
DEF x:METHOD,load_str1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_str1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::load(const char *filename,const char *docreate)
{
    if(load(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=fopen(filename,"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load(filename);
        }
    }
    return -1;
}
/**bmc
DEF load_str2:ABSTRACT_METHOD
{
    function="load";
    suffix="2";
    brief="Loads a csv-data from a file.";
    param:param_filename{};
    return:i="Returns 0 if successful, or a value other than 0 otherwise.";
}
DEF x:METHOD,load_str2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_str2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::load(const char *filename)
{
    //printf("CsvData::load: filename=%s\n",filename);
    Reader *r=ReaderInterface::createFileReader(filename);
    if(r->getLastError())
    {
        //printf("ERROR: %d-%d\n",r->getLastError(),r->getLastErrorDetail());
        delete r;
        return -1;
    }
    load(r);
    delete r;
    return 0;
}
/**bmc
DEF load_str3:ABSTRACT_METHOD
{
    function="load";
    suffix="3";
    switch="#ifdef OS_WIN";
    brief="Loads a csv-data from a file.";
    param:param_filenameW{};
    param:param_docreate{};
    return:i="Returns 0 if successful, or a value other than 0 otherwise.";
}
DEF x:METHOD,load_str3
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_str3,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:winonly_remark{};
}
*/
#ifdef OS_WIN
int CsvData::load(const wchar_t *filename,const char *docreate)
{
    if(load(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=_wfopen(filename,L"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load(filename);
        }
    }
    return -1;
}
#endif
/**bmc
DEF load_str4:ABSTRACT_METHOD
{
    function="load";
    suffix="4";
    switch="#ifdef OS_WIN";
    brief="Loads a csv-data from a file.";
    param:param_filenameW{};
    return:i="Returns 0 if successful, or a value other than 0 otherwise.";
}
DEF x:METHOD,load_str4
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_str4,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:winonly_remark{};
}
*/
#ifdef OS_WIN
int CsvData::load(const wchar_t *filename)
{
    Reader *r=ReaderInterface::createFileReader(filename);
    if(r->getLastError())return -1;
    load(r);
    return 0;
}
#endif
/*
DEF load_wcs1:ABSTRACT_METHOD
{
    function="load_wcs";
    suffix="1";
    brief="Loads a csv file.";
    param:param_filename{};
    param:param_docreate{};
    return:i="...";
}
DEF x:METHOD,load_wcs1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_wcs1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
/*
int CsvData::load_wcs(const char *filename,const char *docreate)
{
    if(load_wcs(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=fopen(filename,"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load_wcs(filename);
        }
    }
    return -1;
}
*/
/*
DEF load_wcs2:ABSTRACT_METHOD
{
    function="load_wcs";
    suffix="2";
    brief="Loads a csv file.";
    param:param_filename{};
    return:i="...";
}
DEF x:METHOD,load_wcs2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_wcs2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
/*
int CsvData::load_wcs(const char *filename)
{
    Reader *r=ReaderInterface::createWcsFileReader(filename);
    if(r->getLastError())return -1;
    load(r);
    return 0;
}
*/
/*
DEF load_wcs3:ABSTRACT_METHOD
{
    function="load_wcs";
    suffix="3";
    switch="#ifdef OS_WIN";
    brief="Loads a csv file.";
    param:param_filenameW{};
    param:param_docreate{};
    return:i="...";
}
DEF x:METHOD,load_wcs3
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_wcs3,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:winonly_remark{};
}
*/
/*
#ifdef OS_WIN
int CsvData::load_wcs(const wchar_t *filename,const char *docreate)
{
    if(load_wcs(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=_wfopen(filename,L"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load_wcs(filename);
        }
    }
    return -1;
}
#endif
*/
/*
DEF load_wcs4:ABSTRACT_METHOD
{
    function="load_wcs";
    suffix="4";
    switch="#ifdef OS_WIN";
    brief="Loads a csv file.";
    param:param_filenameW{};
    return:i="...";
}
DEF x:METHOD,load_wcs4
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_wcs4,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:winonly_remark{};
}
*/
/*
#ifdef OS_WIN
int CsvData::load_wcs(const wchar_t *filename)
{
    Reader *r=ReaderInterface::createWcsFileReader(filename);
    if(r->getLastError())return -1;
    load(r);
    return 0;
}
#endif
*/
/**bmc
DEF load:ABSTRACT_METHOD
{
    function="load";
    suffix="5";
    brief="Loads csv data.";
    param:param_Reader{};
    return:i="Returns 0.";
}
DEF x:METHOD,load
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::load(Reader *r)
{
    int h=1;
    while(h==1)
    {
        //CsvRecord rec(this);
        //h=rec.load(r);
        //data.push_back(rec);
        //printf("loading csv record\n");

        AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
        h=rec->load(r);
        addRecord(rec);
    }
    return 0;
}
void CsvData::addRecord(AbsCsvRecord *rec)
{
    if(data_size>=data_memln)
    {
        data_memln*=2;
        data=(AbsCsvRecord **)realloc(data,(data_memln+1)*sizeof(AbsCsvRecord *));
    }
    data[data_size++]=rec;
}
/**bmc
DEF load_rec:ABSTRACT_METHOD
{
    function="load_rec";
    brief="Loads the current line.";
    param:param_Reader{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,load_rec
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:load_rec,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::load_rec(Reader *r)
{
    AbsCsvRecord *rec=new CsvRecord(this);
    rec->load(r);
    return rec;
}
/**bmc
DEF get_record_count:ABSTRACT_METHOD
{
    txt_bevore="Counting Records";
    function="get_record_count";
    brief="Returns the number of currently loaded records.";
    return:i="The number of records.";
}
DEF x:METHOD,get_record_count
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:get_record_count,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::get_record_count()
{
    return data_size;
}
/**bmc
DEF useHeader:ABSTRACT_METHOD
{
    txt_bevore="Headers";
    function="useHeader";
    brief="...";
    param:b{name="h";desc="@kw.true if the first line contains headers and @kw.false otherwise.";};
    return:v="";
}
DEF x:METHOD,useHeader
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:useHeader,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
void CsvData::useHeader(bool h)
{
    header=h;
}
/**bmc
DEF getHeaderId:ABSTRACT_METHOD
{
    function="getHeaderId";
    brief="...";
    param:param_colname{};
    return:i="Number of the column or -1 if a column with this name does not exist.";
    remark:unique_column{};
}
DEF x:METHOD,getHeaderId
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getHeaderId,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::getHeaderId(const char *col)
{
    if(!header)return -1;
    if(!data_size)return -1;
    if(!data || !data[0])return -1;
    return data[0]->match(col);
}
/**bmc
DEF getHeader:ABSTRACT_METHOD
{
    function="getHeader";
    brief="Returns the column title of a column.";
    param:param_col{};
    return:cp="Title of the column spezified by its index <code>col</code>. If the index is out of range or, if the csv table does not contain a header line, the method returns @kw.null\.";
}
DEF x:METHOD,getHeader
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getHeader,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
char *CsvData::getHeader(int column_id)
{
    if(!header)return 0;
    if(column_id<0 || column_id>=data[0]->get_record_size())return 0;
    return data[0]->getField(column_id);
}
/**bmc
DEF setField1:ABSTRACT_METHOD
{
    txt_bevore="Setting Values of Fields";
    function="setField";
    suffix="1";
    brief="...";
    param:param_row{};
    param:param_col{};
    param:param_val{};
    return:b="...";
}
DEF x:METHOD,setField1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:setField1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
bool CsvData::setField(int row,int col,const char *val)
{
    AbsCsvRecord *rec=getRecord(row);
    if(!rec)return false;
    return rec->setField(col,val);
}
/**bmc
DEF setField2:ABSTRACT_METHOD
{
    function="setField";
    suffix="2";
    brief="...";
    param:param_row{};
    param:param_colname{};
    param:param_val{};
    return:b="...";
}
DEF x:METHOD,setField2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:setField2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:unique_column{};
}
*/
bool CsvData::setField(int row,const char *col,const char *val)
{
    int c=getHeaderId(col);
    if(c==-1)return false;
    return setField(row,c,val);
}
/**bmc
DEF addRecord1:ABSTRACT_METHOD
{
    txt_bevore="Adding Records";
    function="addRecord";
    suffix="1";
    brief="...";
    return:i="...";
}
DEF x:METHOD,addRecord1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:addRecord1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
    remark:unique_column{};
}
*/
int CsvData::addRecord()
{
    if(header)return addRecord(data[0]->get_record_size());

    //CsvRecord rec(this);
    //data.push_back(rec);
    //return data.size()-1;

    AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
    addRecord(rec);
    return data_size-1;
}
/**bmc
DEF param_fldcount:i
{
    name="fldcount";
    desc="Number of colums";
}
DEF addRecord2:ABSTRACT_METHOD
{
    function="addRecord";
    suffix="2";
    brief="...";
    param:param_fldcount{};
    return:i="...";
}
DEF x:METHOD,addRecord2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:addRecord2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
int CsvData::addRecord(int fldcount)
{
    //CsvRecord rec(this);
    //data.push_back(rec);
    //int i,row=data.size()-1;

    AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
    addRecord(rec);
    int i,row=data_size-1;

    for(i=0;i<fldcount;i++)addFieldToRecord(row);
    return row;
}
/**bmc
DEF addFieldToRecord:ABSTRACT_METHOD
{
    function="addFieldToRecord";
    param:param_row{};
    brief="...";
    return:b="...";
}
DEF x:METHOD,addFieldToRecord
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:addFieldToRecord,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
bool CsvData::addFieldToRecord(int row)
{
    AbsCsvRecord *rec=getRecord(row);
    if(!rec)return false;
    rec->addField();
    return true;
}
//get record
/**bmc
DEF getRecord1:ABSTRACT_METHOD
{
    txt_bevore="Getting a Record";
    function="getRecord";
    suffix="1";
    brief="...";
    param:param_col{};
    param:param_val{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,getRecord1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getRecord1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::getRecord(int col,const char *val)
{
    /*
    for(std::vector<AbsCsvRecord>::iterator i=data.begin();i!=data.end();i++)
    {
        if((*i).match(col,val))
        {
            return &(*i);
        }
    }
    */

    for(int i=0;i<data_size;i++)
    {
        if(data[i]->match(col,val))
        {
            return data[i];
        }
    }

    return 0;
}
/**bmc
DEF getRecord2:ABSTRACT_METHOD
{
    function="getRecord";
    suffix="2";
    brief="...";
    param:param_col2{};
    param:param_val2{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,getRecord2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getRecord2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::getRecord(int *col,const char **val)
{
    int ln=iln(col);
    int j;

    /*
    for(std::vector<AbsCsvRecord>::iterator i=data.begin();i!=data.end();i++)
    {
        for(j=0;j<ln;j++)
        {
            if(!(*i).match(col[j],val[j]))break;
        }
        if(j==ln)
        {
            return &(*i);
        }
    }
    */

    for(int i=0;i<data_size;i++)
    {
        for(j=0;j<ln;j++)
        {
            if(!data[i]->match(col[j],val[j]))break;
        }
        if(j==ln)
        {
            return data[i];
        }
    }

    return 0;
}
/**bmc
DEF getRecord3:ABSTRACT_METHOD
{
    function="getRecord";
    suffix="3";
    brief="...";
    param:param_row{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,getRecord3
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getRecord3,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::getRecord(int row)
{
    int rrow;
    if(row>=0)rrow=row;
    else rrow=data_size+row;
    if(rrow<0 || rrow>=data_size)return 0;
    return data[rrow];
}
/**bmc
DEF getRecord4:ABSTRACT_METHOD
{
    function="getRecord";
    suffix="4";
    brief="...";
    param:param_colname{};
    param:param_val{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,getRecord4
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getRecord4,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::getRecord(const char *col,const char *val)
{
    if(!header)return 0;
    int c=getHeaderId(col);
    if(c<0)return 0;
    return getRecord(c,val);
}
/**bmc
DEF getRecord5:ABSTRACT_METHOD
{
    function="getRecord";
    suffix="5";
    brief="...";
    param:param_colname2{};
    param:param_val2{};
    return:param_CsvRecord="...";
}
DEF x:METHOD,getRecord5
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getRecord5,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord *CsvData::getRecord(const char **col,const char **val)
{
    if(!header)return 0;

    int ln=aln(col);
    int *c=(int *)malloc((ln+1)*sizeof(int));
    int i;

    for(i=0;i<ln;i++)
    {
        c[i]=getHeaderId(col[i]);
        if(c[i]<0){free(c);return 0;}
    }
    c[ln]=INT_MAX;

    AbsCsvRecord *r=getRecord(c,val);
    free(c);
    return r;
}
/**bmc
DEF getAllRecords_free:REMARK
{
    text="The application has to free the returned buffer.
    (Do NOT free returned records: <s><code>free(r[i]);</code></s> or <s><code>delete r[i];</code></s>.)
<div style='margin-left:20px;background-color:rgb(200,200,200);'>
<code>AbsCsvRecord **r=getAllRecords();<br>
...<br>
free(r);
</code>
</div>";
}
DEF getAllRecords_free2:REMARK
{
    text="The application has to free the returned buffer.
    (Do NOT free returned records: <s><code>free(r[i]);</code></s> or <s><code>delete r[i];</code></s>.)
<div style='margin-left:20px;background-color:rgb(200,200,200);'>
<code>AbsCsvRecord **r=getAllRecords();<br>
...<br>
if(r)free(r);
</code>
</div>";
}
*/
/**bmc
DEF getAllRecords1:ABSTRACT_METHOD
{
    txt_bevore="Selecting Records";
    function="getAllRecords";
    suffix="1";
    brief="Selects all records with value <i>val</i> in column <i>col</i>.";
    param:param_col{};
    param:param_val{};
    return:param_CsvRecord2="The method returns a pointer to a null-terminated sequence of pointers to the found records. If no records are found, or if column <i>col</i> does not exist, the method returns an empty sequence (where getAllRecords(col,val)[0]==0).";
    remark:getAllRecords_free{};
}
DEF x:METHOD,getAllRecords1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getAllRecords1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord **CsvData::getAllRecords(int col,const char *val)
{
    int rpos=0,rmax=16;
    /*
    CsvRecord **r;
    r=(CsvRecord **)malloc((rmax+1)*sizeof(CsvRecord *));
    for(std::vector<CsvRecord>::iterator i=data.begin();i!=data.end();i++)
    {
        if((*i).match(col,val))
        {
            if(rpos>=rmax)
            {
                rmax*=2;
                r=(CsvRecord **)realloc(r,(rmax+1)*sizeof(CsvRecord *));
            }
            r[rpos++]=&(*i);
        }
    }
    r[rpos]=0;
    */

    AbsCsvRecord **r;
    r=(AbsCsvRecord **)malloc((rmax+1)*sizeof(AbsCsvRecord *));
    for(int i=0;i<data_size;i++)
    {
        if(data[i]->match(col,val))
        {
            if(rpos>=rmax)
            {
                rmax*=2;
                r=(AbsCsvRecord **)realloc(r,(rmax+1)*sizeof(AbsCsvRecord *));
            }
            r[rpos++]=data[i];
        }
    }
    r[rpos]=0;

    return r;
}
/**bmc
DEF getAllRecords2:ABSTRACT_METHOD
{
    function="getAllRecords";
    suffix="2";
    brief="Selects all records";
    return:param_CsvRecord2="The method returns a pointer to a null-terminated sequence of pointers to all records.";
    remark:getAllRecords_free{};
}
DEF x:METHOD,getAllRecords2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getAllRecords2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord **CsvData::getAllRecords()
{
    /*
    CsvRecord **r;
    int rpos=0,rmax=data.size();
    r=(CsvRecord **)malloc((rmax+1)*sizeof(CsvRecord *));
    for(std::vector<CsvRecord>::iterator i=data.begin();i!=data.end();i++)
    {
        if(!header || i!=data.begin())
        {
            if(rpos>=rmax)
            {
                rmax*=2;
                r=(CsvRecord **)realloc(r,(rmax+1)*sizeof(CsvRecord *));
            }
            r[rpos++]=&(*i);
        }
    }
    r[rpos]=0;
    */

    AbsCsvRecord **r;
    int rpos=0,rmax=data_size;
    r=(AbsCsvRecord **)malloc((rmax+1)*sizeof(AbsCsvRecord *));
    for(int i=header;i<data_size;i++)
    {
        r[rpos++]=data[i];
    }
    r[rpos]=0;

    return r;
}
/**bmc
DEF getAllRecords3:ABSTRACT_METHOD
{
    function="getAllRecords";
    suffix="3";
    brief="Selects all records with value <i>val</i> in column <i>column_name</i>.";
    param:param_colname{};
    param:param_val{};
    return:param_CsvRecord2="The method returns 0, if headers are disabled or if the header field is missing. Otherwise the method returns a pointer to a null-terminated sequence of pointers to the found records.";
    remark:getAllRecords_free2{};
}
DEF x:METHOD,getAllRecords3
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:getAllRecords3,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
AbsCsvRecord **CsvData::getAllRecords(const char *col,const char *val)
{
    if(!header)return 0;
    int c=getHeaderId(col);
    if(c<0)return 0;
    return getAllRecords(c,val);
}
//------------------------------------------------------------------------------
// printing/output
//------------------------------------------------------------------------------
/**bmc
DEF saveD:ABSTRACT_METHOD
{
    txt_bevore="Writing CSV Data";
    function="save";
    brief="...";
    param:param_filename{};
    return:b="...";
}
DEF x:METHOD,saveD
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:saveD,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
bool CsvData::save(const char *filename)
{
    FILE *f=fopen(filename,"wb");
    if(!f)return false;
    print(f);
    fclose(f);
    return true;
}
/**bmc
DEF printD1:ABSTRACT_METHOD
{
    function="print";
    suffix="1";
    brief="...";
    param:param_file{};
    return:v="...";
}
DEF x:METHOD,printD1
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:printD1,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
void CsvData::print(FILE *f)
{
    /*
    for(std::vector<CsvRecord>::iterator i=data.begin();i!=data.end();i++)
    {
        (*i).print(f);
        if(i+1!=data.end())fprintf(f,"%c",settings->record_seperator_out);
    }
    */

    for(int i=0;i<data_size;i++)
    {
        data[i]->print(f);
        if(i+1<data_size)fprintf(f,"%c",settings->get_record_seperator_out());
    }
}
/**bmc
DEF printD2:ABSTRACT_METHOD
{
    function="print";
    suffix="2";
    brief="...";
    param:param_file{};
    param:param_row2{};
    param:param_col2{};
    return:v="...";
}
DEF x:METHOD,printD2
{
    CsvData="TRUE";
    class="CsvData";
}
DEF x:printD2,AbsCsvData,IMETHOD
{
    AbsCsvData="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvData_INTERFACE;
    }
}
*/
void CsvData::print(FILE *f,int *row,int *col)
{
    int ln=data_size;
    int i,p=0;
    if(row)qsort(row,iln(row),sizeof(int),cmpi);
    for(i=0;i<ln;i++)
    {
        if(row)
        {
            if(i==row[p])
            {
                if(col==0)data[i]->print(f);else data[i]->print(f,col);
                if(i<ln)fprintf(f,"%c",settings->get_record_seperator_out());
                while(row[p]==row[p+1]){p++;}p++;
                if(row[p]==INT_MAX)break;
            }
        }
        else
        {
            if(col==0)data[i]->print(f);else data[i]->print(f,col);
            if(i<ln)fprintf(f,"%c",settings->get_record_seperator_out());
        }
    }
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
/*
void CsvData::copy(Reader *r,FILE *f,int *row,int *col)
{
    int h=1;
    int i=0,p=0;
    CsvRecord *rec;
    if(row)qsort(row,iln(row),sizeof(int),cmpi);
    while(h==1)
    {
        rec=new CsvRecord(this);
        h=rec->load(r);
        if(row)
        {
            if(i==row[p])
            {
                if(col==0)rec->print(f);else rec->print(f,col);
                while(row[p]==row[p+1])p++;p++;
                if(row[p]==INT_MAX)break;
            }
        }
        else
        {
            if(col==0)rec->print(f);else rec->print(f,col);
        }
        delete rec;
        i++;
    }
}
*/
