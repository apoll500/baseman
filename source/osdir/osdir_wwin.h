/*******************************************************************************
*                                                                              *
*  osdir_wwin.h                                                                *
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
#ifndef H_WWRAP_DIR_WWIN
#define H_WWRAP_DIR_WWIN
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
//------------------------------------------------------------------------------
//#include "wwrap/str.h"
//#include "str/v01/module.h"
//------------------------------------------------------------------------------
#ifdef OS_WIN
#include <windows.h>
#include <wchar.h>
#include <io.h>
#endif
#include "osdir/import/prokee.h"
class osdir
{
public:
    static void ini_myWIN32_FIND_DATA(myWIN32_FIND_DATA *sdata,const void *);
    static void free_myWIN32_FIND_DATA(myWIN32_FIND_DATA *sdata);
    static wchar_t *get_cFileName(myWIN32_FIND_DATA *sdata,const wchar_t *);
    static char *get_cFileName(myWIN32_FIND_DATA *sdata,const char *);
    static WIN32_FIND_DATAW *get(myWIN32_FIND_DATA *sdata,const void *);
    static WIN32_FIND_DATAW *get(myWIN32_FIND_DATA *sdata);
    static void setnull_cFileName(myWIN32_FIND_DATA *sdata);
    static void append_cFileName(myWIN32_FIND_DATA *sdata,const char *a);
    static void append_cFileName(myWIN32_FIND_DATA *sdata,const wchar_t *a);
    
    
    
    static int mk(const char *a);
    static int mk(const wchar_t *a);
    static int rm(const char *a);
    static int rm(const wchar_t *a);
    
    static char *oscwd(char *a,size_t n);
    static wchar_t *oscwd(wchar_t *a,size_t n);
    static HANDLE myFindFirstFile(char *directory,myWIN32_FIND_DATA *fdata);
    static HANDLE myFindFirstFile(wchar_t *directory,myWIN32_FIND_DATA *fdata);
    static bool myFindNextFile(HANDLE hfind,myWIN32_FIND_DATA *fdata);
    static bool myFindNextFile(HANDLE hfind,WIN32_FIND_DATAW *fdata);
    
    static int _stat(const char *,struct stat *)
    {
        return 0;
    }
    static int _stat(const wchar_t *,struct stat *)
    {
        return 0;
    }
};
#include "osdir/import/modules.h"
#endif
