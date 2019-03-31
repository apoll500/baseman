/*******************************************************************************
*                                                                              *
*  osfile_lin.h                                                                *
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
#ifndef H_WWRAP_FILE_LIN
#define H_WWRAP_FILE_LIN

#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class osfile
{
public:
    //--------------------------------------------------------------------------
    // char
    //--------------------------------------------------------------------------
    static FILE *open(const char *n,const char *m)
    {
        return fopen(n,m);
    }
    static bool rm(const char *filename)
    {
        //--TODO-- unlink()
        return (remove(filename)==0);
    }
    static time_t get_time_write(const char *filename)
    {
        struct stat sb;
        if(lstat(filename,&sb)!=-1)return sb.st_mtime;
        return 0;
    }
    static unsigned long get_size(const char *filename)
    {
        struct stat sb;
        if(lstat(filename,&sb)!=-1)return sb.st_size;
        return 0;
    }
    static bool testfile(const char *path)
    {
        struct stat sb;
        return lstat(path,&sb)!=-1;
    }
    //--------------------------------------------------------------------------
    // wchar_t
    //--------------------------------------------------------------------------
    static FILE *open(const wchar_t *,const wchar_t *)
    {
        return 0;
    }
    static bool rm(const wchar_t *)
    {
        return 0;
    }
    static time_t get_time_write(const wchar_t *)
    {
        return 0;
    }
    static unsigned long get_size(const wchar_t *)
    {
        return 0;
    }
    static bool testfile(const wchar_t *)
    {
        return 0;
    }
};

#endif
