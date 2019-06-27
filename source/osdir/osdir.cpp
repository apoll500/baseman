/*******************************************************************************
*                                                                              *
*  osdir.cpp                                                                   *
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
#include "osdir.h"

#ifdef OS_WIN
#ifdef OS_WIN_WCS

void osdir::ini_myWIN32_FIND_DATA(myWIN32_FIND_DATA *sdata,const void *)
{
    sdata->cFileName_ln=300;
    sdata->cFileName=(char *)malloc((sdata->cFileName_ln+1)*sizeof(char));
}
void osdir::free_myWIN32_FIND_DATA(myWIN32_FIND_DATA *sdata)
{
    if(sdata->cFileName)free(sdata->cFileName);
}

wchar_t *osdir::get_cFileName(myWIN32_FIND_DATA *sdata,const wchar_t *)
{
    return sdata->dataW.cFileName;
}
char *osdir::get_cFileName(myWIN32_FIND_DATA *sdata,const char *)
{
    if(!strconv::to_str(&(sdata->cFileName),&(sdata->cFileName_ln),sdata->dataW.cFileName))
    {
        sdata->cFileName[0]=0;
    }
    return sdata->cFileName;
}

WIN32_FIND_DATAW *osdir::get(myWIN32_FIND_DATA *sdata,const void *)
{
    return &(sdata->dataW);
}
WIN32_FIND_DATAW *osdir::get(myWIN32_FIND_DATA *sdata)
{
    return &(sdata->dataW);
}

void osdir::setnull_cFileName(myWIN32_FIND_DATA *sdata)
{
    sdata->dataW.cFileName[0]=0;
}
void osdir::append_cFileName(myWIN32_FIND_DATA *sdata,const char *a)
{
    wchar_t *w=0;
    if(strconv::to_wcs(&w,0,a))
    {
        str::cat(sdata->dataW.cFileName,w);
        free(w);
    }
}
void osdir::append_cFileName(myWIN32_FIND_DATA *sdata,const wchar_t *a)
{
    str::cat(sdata->dataW.cFileName,a);
}


int osdir::mk(const char *a)
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
int osdir::mk(const wchar_t *a)
{
    return _wmkdir(a);
}

int osdir::rm(const char *a)
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
int osdir::rm(const wchar_t *a)
{
    return !RemoveDirectoryW(a);
}

/*
wchar_t *osdir::oscwd()
{
    return _wgetcwd(0,0);//Argument 0,0 lets the Funktion allocate the required memory.
}
*/
char *osdir::oscwd(char *a,size_t n)
{
    //--TODO--
    return getcwd(a,n);
}
wchar_t *osdir::oscwd(wchar_t *a,size_t n)
{
    return _wgetcwd(a,n);
}

HANDLE osdir::myFindFirstFile(char *directory,myWIN32_FIND_DATA *fdata)
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
HANDLE osdir::myFindFirstFile(wchar_t *directory,myWIN32_FIND_DATA *fdata)
{
    return FindFirstFileW(directory,get(fdata));
}

bool osdir::myFindNextFile(HANDLE hfind,myWIN32_FIND_DATA *fdata)
{
    return FindNextFileW(hfind,get(fdata));
}
bool osdir::myFindNextFile(HANDLE hfind,WIN32_FIND_DATAW *fdata)
{
    return FindNextFileW(hfind,fdata);
}

#else
//
#endif
#elif defined OS_LIN
//
#endif
