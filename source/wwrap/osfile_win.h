/*******************************************************************************
*                                                                              *
*  osfile_win.h                                                                *
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
#ifndef H_WWRAP_FILE_WIN
#define H_WWRAP_FILE_WIN
#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <wchar.h>
class osfile
{
public:
    static FILE *open(const char *n,const char *m)
    {
        return fopen(n,m);
    }
    static FILE *open(const wchar_t *n,const wchar_t *m)
    {
        return _wfopen(n,m);
    }
    static HANDLE myCreateFile(char *lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)
    {
        return CreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
    }
    static HANDLE myCreateFile(wchar_t *lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)
    {
        return CreateFileW(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
    }
    static bool rm(const char *filename)
    {
        //--TODO-- _unlink() _wunlink()
        return DeleteFileA(filename);
    }
    static bool rm(const wchar_t *filename)
    {
        return DeleteFileW(filename);
    }
    static time_t get_time_write(const char *filename)
    {
        long r;
        time_t rtime;
        _finddata_t d;
        r=_findfirst(filename,&d);
        rtime=d.time_write;
        _findclose(r);
        return rtime;
    }
    static time_t get_time_write(const wchar_t *filename)
    {
        long r;
        time_t rtime;
        _wfinddata_t d;
        r=_wfindfirst(filename,&d);
        rtime=d.time_write;
        _findclose(r);
        return rtime;
    }
    static unsigned long get_size(const char *filename)
    {
        long r;
        _fsize_t rsize;
        _finddata_t d;
        r=_findfirst(filename,&d);
        rsize=d.size;
        _findclose(r);
        return rsize;
    }
    static unsigned long get_size(const wchar_t *filename)
    {
        long r;
        _fsize_t rsize;
        _wfinddata_t d;
        r=_wfindfirst(filename,&d);
        rsize=d.size;
        _findclose(r);
        return rsize;
    }
    static bool testfile(const char *path)
    {
        long r;
        _finddata_t d;
        r=_findfirst(path,&d);
        _findclose(r);
        return r!=-1;
    }
    static bool testfile(const wchar_t *path)
    {
        long r;
        _wfinddata_t d;
        r=_wfindfirst(path,&d);
        _findclose(r);
        return r!=-1;
    }
};
#endif
