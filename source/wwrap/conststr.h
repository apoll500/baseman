/*******************************************************************************
*                                                                              *
*  conststr.h                                                                  *
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
#ifndef H_WWRAP_CONSTSTR
#define H_WWRAP_CONSTSTR
#define CONSTSTR_MAXSEPS 10
#include <string.h>
class conststr
{
public:
    //dirsep
    static char *dirsep(char *a)
    {
        return strcpy(a,"/\\");
    }
    static wchar_t *dirsep(wchar_t *a)
    {
        return wcscpy(a,L"/\\");
    }
    static char *dirsep1(char *a)
    {
        return strcpy(a,"/");
    }
    static wchar_t *dirsep1(wchar_t *a)
    {
        return wcscpy(a,L"/");
    }
    static char *dirsep2(char *a)
    {
        return strcpy(a,"\\");
    }
    static wchar_t *dirsep2(wchar_t *a)
    {
        return wcscpy(a,L"\\");
    }
    //labelsep
    static char *labelsep(char *a)
    {
        return strcpy(a,":");
    }
    static wchar_t *labelsep(wchar_t *a)
    {
        return wcscpy(a,L":");
    }
    //rootsym
    static char *rootsym(char *a)
    {
        return strcpy(a,"/");
    }
    static wchar_t *rootsym(wchar_t *a)
    {
        return wcscpy(a,L"/");
    }
    //susep
    static char *susep(char *a)
    {
        return strcpy(a,".");
    }
    static wchar_t *susep(wchar_t *a)
    {
        return wcscpy(a,L".");
    }
    //SIMPLE CAST
    template<class T> static T *cast(T *a,const char *ansi_string)
    {
        int p=0;
        while(ansi_string[p]!=0)
        {
            a[p]=(T)ansi_string[p];
            p++;
        }
        a[p]=0;
        return a;
    }
};
#endif
