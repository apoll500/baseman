/*******************************************************************************
*                                                                              *
*  CsvField.cpp                                                                *
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
#include "CsvField.h"
#include "csv.h"

CsvField::CsvField(CsvSettings *s)
{
    settings=s;
    value_ln=CSV_INI_FLD_LENGTH;
    value=(char *)malloc((value_ln+1)*sizeof(char));
    value[0]=0;
}
CsvField::~CsvField()
{
    free(value);
}
int CsvField::load(FileReader *r)
{
    int ch;
    int opos=0;
    bool isinstr=false;
    bool instr_begin=false;
    bool skip=false;
    while((ch=r->get())!=-1)
    {
        if(!isinstr)
        {
            if(ch==settings->field_seperator_in)return 1;
            else if(ch==settings->record_seperator_in)return 0;
            else if(ch==settings->string_marker_in)
            {
                isinstr=true;
                instr_begin=true;
            }
        }
        else
        {
            if(!skip)
            {
                if(ch==settings->string_marker_in)
                {
                    skip=true;
                }
            }
            else
            {
                if(ch==settings->field_seperator_in)
                {
                    return 1;
                }
                else if(ch==settings->record_seperator_in)
                {
                    return 0;
                }
                else if(ch==settings->string_marker_in)
                {
                    skip=false;
                }
                else
                {
                    skip=false;
                    isinstr=false;
                }
            }
        }
        if(!skip && !instr_begin)
        {
            if(opos>=value_ln)
            {
                value_ln*=2;
                value=(char *)realloc(value,(value_ln+1)*sizeof(char));
            }
            value[opos++]=ch;
            value[opos]=0;
        }
        instr_begin=false;
    }
    return -1;
}
bool CsvField::match(const char *val)
{
    return strcmp(value,val)==0;
}
char *CsvField::get()
{
    return value;
}
void CsvField::set(const char *v)
{
    value=(char *)realloc(value,(strlen(v)+1)*sizeof(char));
    strcpy(value,v);
}
void CsvField::print(FILE *f)
{
    print(f,value);
}
void CsvField::print(FILE *f,const char *val)
{
    int i=0;
    bool doquote=false;
    while(val[i]!=0)
    {
        if(val[i]==settings->field_seperator_out ||
                val[i]==settings->record_seperator_out ||
                val[i]==settings->string_marker_out)
        {
            doquote=true;
        }
        i++;
    }
    if(doquote)
    {
        i=0;
        fprintf(f,"%c",settings->string_marker_out);
        while(val[i]!=0)
        {
            if(val[i]==settings->string_marker_out)
            {
                fprintf(f,"%c",settings->string_marker_out);
            }
            fprintf(f,"%c",val[i]);
            i++;
        }
        fprintf(f,"%c",settings->string_marker_out);
    }
    else
    {
        fprintf(f,"%s",val);
    }
}
