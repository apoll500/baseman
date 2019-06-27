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
//str/code/v01/files/source/str/str.h
#ifndef MOD_str_H
#define MOD_str_H
#include "str/import/prokee.h"
class str
{
public:
    template<class T> static unsigned int len(const T *a);
    template<class T> static T *cpy(T *a,const T *b);
    template<class T> static T *cat(T *a,const T *b);
    template<class T> static int cmp(const T *a,const T *b);
};
#include "str/import/modules.h"
template<class T> unsigned int str::len(const T *a)
{
    unsigned int i=0;
    while(a[i])i++;
    return i;
}
template<class T> T *str::cpy(T *a,const T *b)
{
    unsigned int i=0;
    while(b[i])
    {
        a[i]=b[i];
        i++;
    }
    a[i]=0;
    return a;
}
template<class T> T *str::cat(T *a,const T *b)
{
    unsigned int i=0,p=len(a);
    while(b[i])
    {
        a[p++]=b[i++];
    }
    a[p]=0;
    return a;
}
template<class T> int str::cmp(const T *a,const T *b)
{
    unsigned int i=0;
    while(a[i] && a[i]==b[i])i++;
    return a[i]-b[i];
}
#endif
