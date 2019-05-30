/*******************************************************************************
*                                                                              *
*  CsvRecord.cpp                                                               *
*                                                                              *
*  This file is part of "progs/bmcli". (this program)                          *
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

CsvRecord::CsvRecord(AbsCsvData *d)
{
    top=d;
    record_memln=CSV_INI_REC_LENGTH;
    record=(CsvField **)malloc((record_memln+1)*sizeof(CsvField *));
    record_size=0;
}

CsvRecord::~CsvRecord()
{
    for(int i=0;i<record_size;i++)
    {
        delete record[i];
    }
    free(record);
}

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

int CsvRecord::get_record_size()
{
    return record_size;
}

int CsvRecord::match(int col,const char *val)
{
    if(col<0 || col>record_size)return false;
    return record[col]->match(val);
}

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

char *CsvRecord::getField(int col)
{
    if(col<0 || col>=record_size)return 0;
    return record[col]->get();
}

const char *CsvRecord::getField_f(int col)
{
    if(col<0 || col>=record_size)return "";
    return record[col]->get();
}

bool CsvRecord::setField(int col,const char *val)
{
    if(col<0 || col>=record_size)return false;
    record[col]->set(val);
    return true;
}

AbsCsvData *CsvRecord::getTab()
{
    return top;
}

void CsvRecord::print(FILE *f)
{
    int i;
    for(i=0;i<record_size;i++)
    {
        record[i]->print(f);
        if(i+1!=record_size)fprintf(f,"%c",top->get_settings()->get_field_seperator_out());
    }
}

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

void CsvRecord::print_ln(FILE *f)
{
    print(f);
    fprintf(f,"%c",top->get_settings()->get_record_seperator_out());
}

void CsvRecord::print_ln(FILE *f,int *col)
{
    print(f,col);
    fprintf(f,"%c",top->get_settings()->get_record_seperator_out());
}
