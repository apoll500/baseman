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
#include "wwrap/str.h"
//------------------------------------------------------------------------------
#ifdef OS_WIN
#include <windows.h>
#include <wchar.h>
#include <io.h>
#elif defined OS_LIN
//mkdir
#include <sys/types.h>
#include <sys/stat.h>
//getcwd
#include <unistd.h>
#endif
class myWIN32_FIND_DATA
{
private:
    char *cFileName;
    unsigned int cFileName_ln;
public:
    WIN32_FIND_DATAW dataW;
    myWIN32_FIND_DATA(const void *)
    {
        cFileName_ln=300;
        cFileName=(char *)malloc((cFileName_ln+1)*sizeof(char));
    }
    ~myWIN32_FIND_DATA()
    {
        if(cFileName)free(cFileName);
    }
    wchar_t *get_cFileName(const wchar_t *)
    {
        return dataW.cFileName;
    }
    char *get_cFileName(const char *)
    {
        if(!strconv::to_str(&cFileName,&cFileName_ln,dataW.cFileName))
        {
            cFileName[0]=0;
        }
        return cFileName;
    }
    WIN32_FIND_DATAW *get(const void *)
    {
        return &dataW;
    }
    WIN32_FIND_DATAW *get()
    {
        return &dataW;
    }
    void setnull_cFileName()
    {
        dataW.cFileName[0]=0;
    }
    void append_cFileName(const char *a)
    {
        wchar_t *w=0;
        if(strconv::to_wcs(&w,0,a))
        {
            str::cat(dataW.cFileName,w);
            free(w);
        }
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
        int retv=-1;
        wchar_t *_a=0;
        strconv::to_wcs(&_a,0,a);
        if(_a)
        {
            retv=mk(_a);
            free(_a);
        }
        return retv;
    }
    static int mk(const wchar_t *a)
    {
        return _wmkdir(a);
    }
    static int rm(const char *a)
    {
        int retv=-1;
        wchar_t *_a=0;
        strconv::to_wcs(&_a,0,a);
        if(_a)
        {
            //retv=_wrmdir(_a); //Funktioniert, wenn osio::print() folgt, gibt sonst 0 zurück (erfolgreich), löscht aber nicht.
            //osio::print("    ");   //Möglicherweise wird _a zu schnell freigegeben bzw. osio::print() führt zur ausführung von _wrmdir(). ...?
            retv=!RemoveDirectoryW(_a);
            //osio::print("    ");
            //Sleep(2000);
            //osio::print("    ");
            free(_a);
        }
        return retv;
    }
    static int rm(const wchar_t *a)
    {
        return !RemoveDirectoryW(a);
    }
    static wchar_t *oscwd()
    {
        return _wgetcwd(0,0);//Argument 0,0 lets the Funktion allocate the required memory.
    }
    static char *oscwd(char *a,size_t n)
    {
        //--TODO--
        return getcwd(a,n);
    }
    static wchar_t *oscwd(wchar_t *a,size_t n)
    {
        return _wgetcwd(a,n);
    }
    static HANDLE myFindFirstFile(char *directory,myWIN32_FIND_DATA *fdata)
    {
        HANDLE retv=0;
        wchar_t *_directory=0;
        strconv::to_wcs(&_directory,0,directory);
        if(_directory)
        {
            retv=myFindFirstFile(_directory,fdata);
            free(_directory);
        }
        return retv;
    }
    static HANDLE myFindFirstFile(wchar_t *directory,myWIN32_FIND_DATA *fdata)
    {
        return FindFirstFileW(directory,fdata->get());
    }
    static bool myFindNextFile(HANDLE hfind,myWIN32_FIND_DATA *fdata)
    {
        return FindNextFileW(hfind,fdata->get());
    }
    static bool myFindNextFile(HANDLE hfind,WIN32_FIND_DATAW *fdata)
    {
        return FindNextFileW(hfind,fdata);
    }
};
#endif
