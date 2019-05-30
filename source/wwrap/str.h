/*******************************************************************************
*                                                                              *
*  str.h                                                                       *
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
//str/code/v01/files/source/wwrap/str.h
#ifndef MOD_str_H
#define MOD_str_H
#include <wchar.h>
#include <string.h>
class str
{
public:
    static size_t len(const char *a)
    {
        return strlen(a);
    }
    static size_t len(const wchar_t *a)
    {
        return wcslen(a);
    }
    template<class T> static size_t len(const T *a)
    {
        size_t i=0;
        while(a[i])i++;
        return i;
    }
    //
    static char *cpy(char *a,const char *b)
    {
        return strcpy(a,b);
    }
    static wchar_t *cpy(wchar_t *a,const wchar_t *b)
    {
        return wcscpy(a,b);
    }
    template<class T> static T *cpy(T *a,const T *b)
    {
        size_t i=0;
        while(b[i])
        {
            a[i]=b[i];
            i++;
        }
        a[i]=0;
        return a;
    }
    //
    static char *cat(char *a,const char *b)
    {
        return strcat(a,b);
    }
    static wchar_t *cat(wchar_t *a,const wchar_t *b)
    {
        return wcscat(a,b);
    }
    template<class T> static T *cat(T *a,const T *b)
    {
        size_t i=0,p=len(a);
        while(b[i])
        {
            a[p++]=b[i++];
        }
        a[p]=0;
        return a;
    }
    //
    static int cmp(const char *a,const char *b)
    {
        return strcmp(a,b);
    }
    static int cmp(const wchar_t *a,const wchar_t *b)
    {
        return wcscmp(a,b);
    }
    template<class T> static int cmp(const T *a,const T *b)
    {
        size_t i=0;
        while(a[i] && a[i]==b[i])i++;
        return a[i]-b[i];
    }
};
#endif
