/*******************************************************************************
*                                                                              *
*  osdir_win.h                                                                 *
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
#ifndef H_WWRAP_DIR_WIN
#define H_WWRAP_DIR_WIN
#ifdef OS_WIN
#include <windows.h>
#include <wchar.h>
#include <io.h>
#endif
#include "osdir/import/prokee.h"
class myWIN32_FIND_DATA
{
public:
    bool isw;
    WIN32_FIND_DATAA dataA;
    WIN32_FIND_DATAW dataW;
    myWIN32_FIND_DATA(const char *a)
    {
        isw=false;
    }
    myWIN32_FIND_DATA(const wchar_t *a)
    {
        isw=true;
    }
    wchar_t *get_cFileName(const wchar_t *a)
    {
        return dataW.cFileName;
    }
    char *get_cFileName(const char *a)
    {
        return dataA.cFileName;
    }
    WIN32_FIND_DATAW *get(const wchar_t *a)
    {
        return &dataW;
    }
    WIN32_FIND_DATAA *get(const char *a)
    {
        return &dataA;
    }
    void *get()
    {
        if(isw)return &dataW;
        return &dataA;
    }
    void setnull_cFileName()
    {
        dataA.cFileName[0]=0;
        dataW.cFileName[0]=0;
    }
    void append_cFileName(const char *a)
    {
        str::cat(dataA.cFileName,a);
    }
    void append_cFileName(const wchar_t *a)
    {
        str::cat(dataW.cFileName,a);
    }
};
class osdir
{
public:
    static int mk(const char *a)
    {
        return _mkdir(a);//mkdir() ist depricated.
    }
    static int mk(const wchar_t *a)
    {
        return _wmkdir(a);
    }
    static int rm(const char *a)
    {
        return !RemoveDirectoryA(a);
    }
    static int rm(const wchar_t *a)
    {
        return !RemoveDirectoryW(a);
    }
    
    static char *oscwd(char *a,size_t n)
    {
        return getcwd(a,n);
    }
    static wchar_t *oscwd(wchar_t *a,size_t n)
    {
        return _wgetcwd(a,n);
    }
    static HANDLE myFindFirstFile(char *directory,myWIN32_FIND_DATA *fdata)
    {
        return myFindFirstFile(directory,fdata->get(directory));
    }
    static HANDLE myFindFirstFile(char *directory,WIN32_FIND_DATAA *fdata)
    {
        return FindFirstFileA(directory,fdata);
    }
    static HANDLE myFindFirstFile(wchar_t *directory,WIN32_FIND_DATAW *fdata)
    {
        return FindFirstFileW(directory,fdata);
    }
    static bool myFindNextFile(HANDLE hfind,myWIN32_FIND_DATA *fdata)
    {
        if(fdata->isw)return FindNextFileA(hfind,&fdata->dataA);
        return FindNextFileW(hfind,&fdata->dataW);
    }
    static bool myFindNextFile(HANDLE hfind,WIN32_FIND_DATAA *fdata)
    {
        return FindNextFileA(hfind,fdata);
    }
    static bool myFindNextFile(HANDLE hfind,WIN32_FIND_DATAW *fdata)
    {
        return FindNextFileW(hfind,fdata);
    }
    
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
