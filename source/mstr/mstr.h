/*******************************************************************************
*                                                                              *
*  mstr.h                                                                      *
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
//mstr/code/v01/files/source/mstr/mstr.h
#ifndef MOD_mstr_H
#define MOD_mstr_H
#include <stdio.h>
#include <stdlib.h>
#include "macros/macros.h"
#include "mstr/import/prokee.h"
class mstr
{
public:
    template<class T> static mstrs<T> *create(mstrs<T> **m,unsigned int length);
    template<class T> static mstrs<T> *create_from_str(mstrs<T> **m,const T *str);
    template<class T> static mstrs<T> *create_from_str(mstrs<T> **m,const T *str,unsigned int length);
    template<class T> static void destroy(mstrs<T> *m);
    template<class T> static unsigned int length(mstrs<T> *m);
    template<class T> static unsigned int buffer_length(mstrs<T> *m);
    template<class T> static unsigned int buffer_bytes(mstrs<T> *m);
    template<class T> static unsigned int used_memory(mstrs<T> *m);
    template<class T> static mstrs<T> *cpy(mstrs<T> *a,mstrs<T> *b);
    template<class T> static mstrs<T> *cat(mstrs<T> *a,mstrs<T> *b);
    template<class T> static int cmp(mstrs<T> *a,mstrs<T> *b);
    template<class T> static mstrs<T> *fit(mstrs<T> *m);
    template<class T> static mstrs<T> *reset(mstrs<T> *m);
    template<class T> static T *c_str(mstrs<T> *m);
    template<class T> static mstrs<T> *copy_str(mstrs<T> *a,const T *b);
    template<class T> static mstrs<T> *append_str(mstrs<T> *a,const T *b);
    template<class T> static int compare_str(mstrs<T> *a,const T *b);
    template<class T> static bool is_prefix(mstrs<T> *str,mstrs<T> *prefix);
    template<class T> static bool is_prefix(const T *str,mstrs<T> *prefix);
    template<class T> static int is_prefix(const T *str,mstrs<T> **prefix);
};
#include "mstr/import/modules.h"
template<class T> mstrs<T> *mstr::create(mstrs<T> **m,unsigned int length)
{
    *m=(mstrs<T> *)malloc(sizeof(mstrs<T>));
    (*m)->buffer=(T *)malloc((length+1)*sizeof(T));
    (*m)->buffer_len=length;
    (*m)->buffer[0]=0;
    (*m)->len=0;
    return *m;
}
template<class T> mstrs<T> *mstr::create_from_str(mstrs<T> **m,const T *str)
{
    *m=(mstrs<T> *)malloc(sizeof(mstrs<T>));
    size_t length=str::len(str);
    (*m)->buffer=(T *)malloc((length+1)*sizeof(T));
    (*m)->buffer_len=length;
    str::cpy((*m)->buffer,str);
    (*m)->len=length;
    return *m;
}
template<class T> mstrs<T> *mstr::create_from_str(mstrs<T> **m,const T *str,unsigned int length)
{
    *m=(mstrs<T> *)malloc(sizeof(mstrs<T>));
    (*m)->buffer=(T *)malloc((length+1)*sizeof(T));
    (*m)->buffer_len=length;
    size_t str_length=0;
    while(str_length<length && str[str_length])
    {
        (*m)->buffer[str_length]=str[str_length];
        str_length++;
    }
    (*m)->buffer[str_length]=0;
    (*m)->len=str_length;
    return *m;
}
template<class T> void mstr::destroy(mstrs<T> *m)
{
    free(m->buffer);
    free(m);
}
template<class T> unsigned int mstr::length(mstrs<T> *m)
{
    return m->len;
}
template<class T> unsigned int mstr::buffer_length(mstrs<T> *m)
{
    return m->buffer_len;
}
template<class T> unsigned int mstr::buffer_bytes(mstrs<T> *m)
{
    return (m->buffer_len+1)*sizeof(T);
}
template<class T> unsigned int mstr::used_memory(mstrs<T> *m)
{
    return (m->buffer_len+1)*sizeof(T)+sizeof(mstrs<T>);
}
template<class T> mstrs<T> *mstr::cpy(mstrs<T> *a,mstrs<T> *b)
{
    if(a->buffer_len<b->len)
    {
        a->buffer_len=MAX(b->len,a->buffer_len*2);
        a->buffer=(T *)realloc(a->buffer,(a->buffer_len+1)*sizeof(T));
    }
    str::cpy(a->buffer,b->buffer);
    a->len=b->len;
    return a;
}
template<class T> mstrs<T> *mstr::cat(mstrs<T> *a,mstrs<T> *b)
{
    if(a->buffer_len<a->len+b->len)
    {
        a->buffer_len=MAX(a->len+b->len,a->buffer_len*2);
        a->buffer=(T *)realloc(a->buffer,(a->buffer_len+1)*sizeof(T));
    }
    str::cat(a->buffer,b->buffer);
    a->len+=b->len;
    return a;
}
template<class T> int mstr::cmp(mstrs<T> *a,mstrs<T> *b)
{
    if(a==0 && b==0)return 0;
    if(a==0 || b==0)return a-b;
    if(a->len!=b->len)return a->len-b->len;
    unsigned int i=0;
    while(a->buffer[i])
    {
        if(a->buffer[i]!=b->buffer[i])return a->buffer[i]-b->buffer[i];
        i++;
    }
    return 0;
}
template<class T> mstrs<T> *mstr::fit(mstrs<T> *m)
{
    m->buffer=(T *)realloc(m->buffer,(m->len+1)*sizeof(T));
    m->buffer_len=m->len;
    return m;
}
template<class T> mstrs<T> *mstr::reset(mstrs<T> *m)
{
    m->len=0;
    m->buffer[0]=0;
    return m;
}
template<class T> T *mstr::c_str(mstrs<T> *m)
{
    return m->buffer;
}
template<class T> mstrs<T> *mstr::copy_str(mstrs<T> *a,const T *b)
{
    unsigned int bln=str::len(b);
    if(a->buffer_len<bln)
    {
        a->buffer_len=MAX(bln,a->buffer_len*2);
        a->buffer=(T *)realloc(a->buffer,(a->buffer_len+1)*sizeof(T));
    }
    str::cpy(a->buffer,b);
    a->len=bln;
    return a;
}
template<class T> mstrs<T> *mstr::append_str(mstrs<T> *a,const T *b)
{
    unsigned int bln=str::len(b);
    if(a->buffer_len<a->len+bln)
    {
        a->buffer_len=MAX(a->len+bln,a->buffer_len*2);
        a->buffer=(T *)realloc(a->buffer,(a->buffer_len+1)*sizeof(T));
    }
    str::cat(a->buffer,b);
    a->len+=bln;
    return a;
}
template<class T> int mstr::compare_str(mstrs<T> *a,const T *b)
{
    unsigned int i=0;
    while(b[i])
    {
        if(a->buffer[i]!=b[i])return a->buffer[i]-b[i];
        i++;
    }
    if(a->buffer[i])return a->buffer[i];
    return 0;
}
template<class T> bool mstr::is_prefix(mstrs<T> *str,mstrs<T> *prefix)
{
    size_t p=0;
    while(prefix->buffer[p])
    {
        if(str->buffer[p]!=prefix->buffer[p])return false;
        p++;
    }
    return true;
}
template<class T> bool mstr::is_prefix(const T *str,mstrs<T> *prefix)
{
    size_t p=0;
    while(prefix->buffer[p])
    {
        if(str[p]!=prefix->buffer[p])return false;
        p++;
    }
    return true;
}
template<class T> int mstr::is_prefix(const T *str,mstrs<T> **prefix)
{
    size_t k=0;
    while(prefix[k])
    {
        if(is_prefix(str,prefix[k]))return k;
        k++;
    }
    return -1;
}
#endif
