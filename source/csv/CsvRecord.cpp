/*******************************************************************************
*                                                                              *
*  CsvRecord.cpp                                                               *
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
#include "CsvRecord.h"
#include "csv.h"

//#include "csv.hh2"

//#include "reader/reader.h"

//#include "CsvSettings.h"

/**bmc
DEF param_CsvData:manu
{
    name="d";
    desc="Pointer to an instance of an implementation of AbsCsvData.<br>See <a href='@param_classinfo[]_AbsCsvData\.php'>@param_classinfo\:AbsCsvData</a>.";
    param_classname="AbsCsvData";
    param_classinfo="csv";
}
DEF param_CsvRecord:manu
{
    name="r";
    desc="Pointer to an instance of an implementation of AbsCsvRecord.<br>See <a href='@param_classinfo[]_AbsCsvData\.php'>@param_classinfo\:AbsCsvData</a>.";
    param_classname="AbsCsvRecord";
    param_classinfo="csv";
}
DEF param_CsvRecord2:manupp
{
    name="r";
    desc="Pointer to an instance of an implementation of AbsCsvRecord.<br>See <a href='@param_classinfo[]_AbsCsvData\.php'>@param_classinfo\:AbsCsvData</a>.";
    param_classname="AbsCsvRecord";
    param_classinfo="csv";
}
*/
//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
/**bmc
DEF inc_CsvRecord
{
    iclass="AbsCsvRecord";
    class="CsvRecord";
    function="create@class";
}
DEF CsvRecord:CONSTRUCTOR,inc_CsvRecord
{
    AbsCsvRecord="TRUE";
    CsvRecord="TRUE";
    brief="...";
    param:param_CsvData{};
    return:vp="Returns an instance of <code>@class</code>\.";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
CsvRecord::CsvRecord(AbsCsvData *d)
{
    top=d;
    record_memln=CSV_INI_REC_LENGTH;
    record=(CsvField **)malloc((record_memln+1)*sizeof(CsvField *));
    record_size=0;
}
/**bmc
DEF destroyCsvRecord:DESTRUCTOR
{
    CsvRecord="TRUE";
    class="CsvRecord";
    function="@this.parent.NAME";
    return:v="";
}
*/
CsvRecord::~CsvRecord()
{
    for(int i=0;i<record_size;i++)
    {
        delete record[i];
    }
    free(record);
}
/**bmc
DEF loadR:ABSTRACT_METHOD
{
    function="load";
    brief="Loads csv data.";
    param:param_Reader{};
    return:i="...";
}
DEF x:METHOD,loadR
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:loadR,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
int CsvRecord::load(Reader *r)
{
    int h=1;
    CsvField *fld;
    while(h==1)
    {
        fld=new CsvField(top->get_settings());
        h=fld->load(r);
        addField(fld);
    }
    if(h==0)return 1;
    return -1;
}
/**bmc
DEF addField1:ABSTRACT_METHOD
{
    function="addField";
    suffix="1";
    brief="...";
    return:v="...";
}
DEF x:METHOD,addField1
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:addField1,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
void CsvRecord::addField()
{
    CsvField *fld=new CsvField(top->get_settings());
    addField(fld);
}
void CsvRecord::addField(CsvField *fld)
{
    if(record_size>=record_memln)
    {
        record_memln*=2;
        record=(CsvField **)realloc(record,(record_memln+1)*sizeof(CsvField *));
    }
    record[record_size++]=fld;
}
/**bmc
DEF get_record_size:ABSTRACT_METHOD
{
    function="get_record_size";
    suffix="1";
    brief="...";
    return:i="...";
}
DEF x:METHOD,get_record_size
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:get_record_size,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
int CsvRecord::get_record_size()
{
    return record_size;
}
/**bmc
DEF match1:ABSTRACT_METHOD
{
    function="match";
    suffix="1";
    brief="...";
    param:param_col{};
    param:param_val{};
    return:i="...";
}
DEF x:METHOD,match1
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:match1,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
int CsvRecord::match(int col,const char *val)
{
    if(col<0 || col>record_size)return false;
    return record[col]->match(val);
}
/**bmc
DEF match2:ABSTRACT_METHOD
{
    function="match";
    suffix="2";
    brief="...";
    param:param_val{};
    return:i="...";
}
DEF x:METHOD,match2
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:match2,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
int CsvRecord::match(const char *val)
{
    for(int i=0;i<record_size;i++)
    {
        if(record[i]->match(val))
        {
            return i;
        }
    }
    return -1;
}
/**bmc
DEF getField:ABSTRACT_METHOD
{
    function="getField";
    brief="...";
    param:param_col{};
    return:cp="Returns a pointer to the null-terminated string or @kw.null\.";
}
DEF x:METHOD,getField
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:getField,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
char *CsvRecord::getField(int col)
{
    if(col<0 || col>=record_size)return 0;
    return record[col]->get();
}
/**bmc
DEF getField_f:ABSTRACT_METHOD
{
    function="getField_f";
    brief="...";
    param:param_col{};
    return:ccp="Returns a pointer to the null-terminated string or a empty string.";
}
DEF x:METHOD,getField_f
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:getField_f,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
const char *CsvRecord::getField_f(int col)
{
    if(col<0 || col>=record_size)return "";
    return record[col]->get();
}
/**bmc
DEF setField:ABSTRACT_METHOD
{
    function="setField";
    brief="...";
    param:param_col{};
    param:param_val{};
    return:b="...";
}
DEF x:METHOD,setField
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:setField,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
bool CsvRecord::setField(int col,const char *val)
{
    if(col<0 || col>=record_size)return false;
    record[col]->set(val);
    return true;
}
/**bmc
DEF getTab:ABSTRACT_METHOD
{
    function="getTab";
    brief="...";
    return:param_CsvData="...";
}
DEF x:METHOD,getTab
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:getTab,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
AbsCsvData *CsvRecord::getTab()
{
    return top;
}
//------------------------------------------------------------------------------
// printing
//------------------------------------------------------------------------------
/**bmc
DEF printR1:ABSTRACT_METHOD
{
    function="print";
    suffix="1";
    brief="...";
    param:param_file{};
    return:v="...";
}
DEF x:METHOD,printR1
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:printR1,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
void CsvRecord::print(FILE *f)
{
    int i;
    for(i=0;i<record_size;i++)
    {
        record[i]->print(f);
        if(i+1!=record_size)fprintf(f,"%c",top->get_settings()->get_field_seperator_out());
    }
}
/**bmc
DEF printR2:ABSTRACT_METHOD
{
    function="print";
    suffix="2";
    brief="...";
    param:param_file{};
    param:param_col2{};
    return:v="...";
}
DEF x:METHOD,printR2
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:printR2,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
void CsvRecord::print(FILE *f,int *col)
{
    int ln=record_size;
    int i,p=0;
    qsort(col,iln(col),sizeof(int),cmpi);
    for(i=0;i<ln;i++)
    {
        if(i==col[p])
        {
            record[i]->print(f);
            while(col[p]==col[p+1]){p++;}p++;
            if(i+1<ln && col[p]!=INT_MAX)fprintf(f,"%c",top->get_settings()->get_field_seperator_out());
            if(col[p]==INT_MAX)break;
        }
    }
}
/**bmc
DEF print_ln1:ABSTRACT_METHOD
{
    function="print_ln";
    suffix="1";
    brief="...";
    param:param_file{};
    return:v="...";
}
DEF x:METHOD,print_ln1
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:print_ln1,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
void CsvRecord::print_ln(FILE *f)
{
    print(f);
    fprintf(f,"%c",top->get_settings()->get_record_seperator_out());
}
/**bmc
DEF print_ln2:ABSTRACT_METHOD
{
    function="print_ln";
    suffix="2";
    brief="...";
    param:param_file{};
    param:param_col2{};
    return:v="...";
}
DEF x:METHOD,print_ln2
{
    CsvRecord="TRUE";
    class="CsvRecord";
}
DEF x:print_ln2,AbsCsvRecord,IMETHOD
{
    AbsCsvRecord="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvRecord_INTERFACE;
    }
}
*/
void CsvRecord::print_ln(FILE *f,int *col)
{
    print(f,col);
    fprintf(f,"%c",top->get_settings()->get_record_seperator_out());
}
