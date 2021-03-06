/*******************************************************************************
*                                                                              *
*  osio_lin.h                                                                  *
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
#ifndef H_WWRAP_OSIO_LIN
#define H_WWRAP_OSIO_LIN
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
typedef int(*external_print_t)(const char *);
class osio
{
public:
    static external_print_t external_print;
    //--------------------------------------------------------------------------
    // char
    //--------------------------------------------------------------------------
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
    static int sprint(char *buffer,const char *format,...)
    {
        va_list args;
        va_start(args,format);
        int i=vsprintf(buffer,format,args);
        va_end(args);
        return i;
    }
    static int sprint(char **buffer,const char *format,...)
    {
        int i;
        va_list args;
        va_start(args,format);
        i=vsnprintf(*buffer,0,format,args);
        va_end(args);
        *buffer=(char *)realloc(*buffer,(i+1)*sizeof(char));
        va_start(args,format);
        i=vsnprintf(*buffer,i+1,format,args);
        va_end(args);
        va_end(args);
        return i;
    }
    static int sprint(char **buffer,int buffer_ln,const char *format,...)
    {
        int i;
        va_list args;
        va_start(args,format);
        i=vsnprintf(*buffer,0,format,args);
        va_end(args);
        if(i>=buffer_ln)*buffer=(char *)realloc(*buffer,(i+1)*sizeof(char));
        va_start(args,format);
        i=vsnprintf(*buffer,i+1,format,args);
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
        char *buffer=0;
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
    //--------------------------------------------------------------------------
    // wchar_t
    //--------------------------------------------------------------------------
    static int print(const wchar_t *,...)
    {
        return 0;
    }
    static int print(FILE *,const wchar_t *,...)
    {
        return 0;
    }
    static int sprint(wchar_t *,const wchar_t *,...)
    {
        return 0;
    }
};
//external_print_t osio::external_print=0;
#endif
