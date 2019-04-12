/*******************************************************************************
*                                                                              *
*  CsvRecord.h                                                                 *
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
#ifndef CsvRecord_H
#define CsvRecord_H

#include <stdio.h>

#include "csv/import/prokee.h"
#include "csv.hh"

#define CSV_INI_REC_LENGTH 16

class CsvData;
class CsvField;

//==============================================================================
// CsvRecord
//==============================================================================
/**bmc
DEF AbsCsvRecord_INTERFACE:INTERFACE
{
    class="AbsCsvRecord";
    no_interface_superclass="TRUE";
    implclass="CsvRecord";
    headers
    {
        ->
        <--
    }
    DEF docu
    {
        title="AbsCsvRecord";
        //text="<pre>@parent.parent.code</pre>";
        section:func.LSECTION
        {
            title="Motivation";
            text
            {
                ->
                <-
            }
        }
    }
}
DEF PAGE_02:FILE,WEBP1
{
    THE_INTERFACE="AbsCsvRecord_INTERFACE";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.html";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.php";
}
DEF AbsCsvRecord
{
    class="AbsCsvRecord";
}
DEF X:WRAPPER
{
    class="CsvRecord";
    baseclass="AbsCsvRecord";
}
*/
class CsvRecord:public AbsCsvRecord2
{
private:
    CsvField **record;
    int record_memln;
    int record_size;
    AbsCsvData *top;
public:
    CsvRecord(AbsCsvData *d);
    ~CsvRecord();
    // loading
    int load(Reader *r);
    // add fields
    void addField();
    void addField(CsvField *fld);
    int get_record_size();
    // get/set fields
    char *getField(int col);
    const char *getField_f(int col);
    bool setField(int col,const char *val);
    AbsCsvData *getTab();
    // match
    int match(int col,const char *val);
    int match(const char *val);
    // printing
    void print(FILE *f);
    void print(FILE *f,int *col);
    void print_ln(FILE *f);
    void print_ln(FILE *f,int *col);
};

//#include "CsvData.h"
////#include "CsvRecord.h"
//#include "CsvField.h"
//#include "CsvSettings.h"

#endif
