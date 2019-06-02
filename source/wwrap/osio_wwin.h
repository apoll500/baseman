/*******************************************************************************
*                                                                              *
*  osio_wwin.h                                                                 *
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
#ifndef H_WWRAP_OSIO_WWIN
#define H_WWRAP_OSIO_WWIN
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifdef COMPILE_PROKEE_MODULE
#ifndef COMPILE_PROKEE_MODULE_NO_STRCONV
#define PROKEE_USE_WRAPPER
#include "strconv/v01/module.h"
#else
#include "strconv/strconv.h"
#endif
#else
#include "strconv/strconv.h"
#endif
//------------------------------------------------------------------------------
#include <stdio.h>
#include <windows.h>
#include <io.h>
typedef int(*external_print_t)(const char *);
class osio
{
public:
    static external_print_t external_print;
    static int print(const char *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vprintf(format,args);
        va_end(args);
        return i;
    }
    static int print(FILE *f,const char *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vfprintf(f,format,args);
        va_end(args);
        return i;
    }
    static int print(const wchar_t *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vwprintf(format,args);
        va_end(args);
        return i;
    }
    static int print(FILE *f,const wchar_t *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vfwprintf(f,format,args);
        va_end(args);
        return i;
    }
    static int sprint(char *buffer,const char *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vsprintf(buffer,format,args);
        va_end(args);
        return i;
    }
    static int sprint(wchar_t *buffer,const wchar_t *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vswprintf(buffer,format,args);
        va_end(args);
        return i;
    }
    static void set_xprint(int(*exprint)(const char *))
    {
        external_print=exprint;
    }
    static int xprint(const char *format,...)
    {
        int i;
        va_list args;
        char *buffer;
        va_start(args,format);
        i=vsnprintf(buffer,0,format,args);
        va_end(args);
        buffer=(char *)malloc((i+1)*sizeof(char));
        va_start(args,format);
        i=vsnprintf(buffer,i+1,format,args);
        va_end(args);
        if(external_print)i=external_print(buffer);
        else printf(buffer);
        free(buffer);
        return i;
    }
};
#endif
