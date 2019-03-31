/*******************************************************************************
*                                                                              *
*  osdir_lin.h                                                                 *
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
#ifndef H_WWRAP_DIR_LIN
#define H_WWRAP_DIR_LIN

#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>

class osdir
{
public:
    //--------------------------------------------------------------------------
    // char
    //--------------------------------------------------------------------------
    static int mk(const char *a)
    {
        return mkdir(a,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    static int rm(const char *a)
    {
        return rmdir(a);
    }
    static char *oscwd()
    {
        return getcwd(0,0);//Arguments 0,0 lets the Funktion allocate the required memory.
    }
    static char *oscwd(char *a,size_t n)
    {
        return getcwd(a,n);
    }
    static int _stat(const char *path,struct stat *st)
    {
        return stat(path,st);
    }
    //--------------------------------------------------------------------------
    // wchar_t
    //--------------------------------------------------------------------------
    static int mk(const wchar_t *)
    {
        return 0;
    }
    static int rm(const wchar_t *)
    {
        return 0;
    }
    static wchar_t *oscwd(wchar_t *,size_t)
    {
        return 0;
    }
    static int _stat(const wchar_t *,struct stat *)
    {
        return 0;
    }
};

#endif
