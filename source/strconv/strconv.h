/*******************************************************************************
*                                                                              *
*  strconv.h                                                                   *
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
// strconv.h
#ifndef MOD_strconv_H
#define MOD_strconv_H

#include "macros/macros.h"

#include <stdlib.h>

#ifdef OS_WIN
#include <windows.h>
#endif

#define INI_STRING_LENGTH 256

class strconv
{
public:
    static char *to_str(char **str_out,unsigned int *str_out_ln,const char *str_in);
#ifdef OS_WIN
    static char *to_str(char **str_out,unsigned int *str_out_ln,const wchar_t *str_in);
    static wchar_t *to_wcs(wchar_t **str_out,unsigned int *str_out_ln,const char *str_in);
#endif
    static wchar_t *to_wcs(wchar_t **str_out,unsigned int *str_out_ln,const wchar_t *str_in);
    template<class T> static T *strcopy(T **str_out,unsigned int *str_out_ln,const T *str_in);
private:
    template<class T> static void memory_alloc(T **str_out,unsigned int *str_out_ln);
    template<class T> static void memory_alloc(T **str_out,unsigned int *str_out_ln,unsigned int initial_ln);
    template<class T> static void memory_check(T **str_out,unsigned int *str_out_ln,unsigned int pos);
};

template<class T> T *strconv::strcopy(T **str_out,unsigned int *str_out_ln,const T *str_in)
{
    unsigned int str_out_ln_2;
    if(str_out_ln==0)str_out_ln_2=0;
    else str_out_ln_2=*str_out_ln;

    unsigned int pos=0;
    memory_alloc(str_out,&str_out_ln_2);
    while(str_in[pos]!=0)
    {
        memory_check(str_out,&str_out_ln_2,pos);
        (*str_out)[pos]=str_in[pos];
        pos++;
    }
    (*str_out)[pos]=0;

    if(str_out_ln!=0)*str_out_ln=str_out_ln_2;

    return *str_out;
}

template<class T> void strconv::memory_alloc(T **str_out,unsigned int *str_out_ln)
{
    memory_alloc(str_out,str_out_ln,INI_STRING_LENGTH);
}

template<class T> void strconv::memory_alloc(T **str_out,unsigned int *str_out_ln,unsigned int initial_ln)
{
    if(*str_out==0)
    {
        if(*str_out_ln==0)
        {
            *str_out_ln=initial_ln;
        }
        *str_out=(T *)malloc((*str_out_ln+1)*sizeof(T));
    }
    else if(*str_out_ln==0)
    {
        *str_out_ln=initial_ln;
        *str_out=(T *)realloc(*str_out,(*str_out_ln+1)*sizeof(T));
    }
}

template<class T> void strconv::memory_check(T **str_out,unsigned int *str_out_ln,unsigned int pos)
{
    if(pos==*str_out_ln)
    {
        *str_out_ln*=2;
        *str_out=(T *)realloc(*str_out,(*str_out_ln+1)*sizeof(T));
    }
}

#endif
