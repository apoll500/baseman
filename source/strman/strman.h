/*******************************************************************************
*                                                                              *
*  strman.h                                                                    *
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
#ifndef MOD_strman_H
#define MOD_strman_H
//#include "wwrap/str.h"
#include "wwrap/conststr.h"
#include <stdlib.h>
#include "strman/import/prokee.h"
class strman
{
public:
    
    template<class T> static T **explode(const T *sep,const T *str);
    template<class T> static int explode_count(T **a);
    template<class T> static void explode_free(T **a);
    template<class T> static int findItem(const T *item,T **itemlist);
    template<class T> static T *getItem(int itemid,T **itemlist);
    
    
    template<class T> static bool isprefix(const T *a,const T *b);
    template<class T> static bool issuffix(const T *a,const T *b);
    template<class T> static bool issubstr(const T *a,const T *b);
    template<class T> static unsigned int findsubstr(const T *a,const T *b);
    
    template<class T> static bool substrmatch(const T *searchpat,const T *text);
    template<class T> static bool matchpat(T *a,T *b);
    template<class T> static bool matchpat_i(T *a,T *b,unsigned int pos_a,unsigned int pos_b);
    
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2,const T *symbols3);
    
};
#include "strman/import/modules.h"
template<class T> T **strman::explode(const T *sep,const T *str)
{
    int aln=10,acnt=1;
    T **a=(T **)malloc((aln+1)*sizeof(T *));
    T *memory=(T *)malloc((str::len(str)+1)*sizeof(T));
    a[0]=memory;
    int pos=0;
    while(str[pos])
    {
        if(matchsymbol(str,pos,sep))
        {
            memory[pos]=0;
            if(acnt==aln)
            {
                aln*=2;
                a=(T **)realloc(a,(aln+1)*sizeof(T *));
            }
            a[acnt]=&memory[pos+1];
            acnt++;
        }
        else
        {
            memory[pos]=str[pos];
        }
        pos++;
    }
    memory[pos]=0;
    a=(T **)realloc(a,(acnt+1)*sizeof(T *));
    a[acnt]=0;
    return a;
}
template<class T> int strman::explode_count(T **a)
{
    int ln=0;
    while(a[ln])ln++;
    return ln;
}
template<class T> void strman::explode_free(T **a)
{
    free(a[0]);
    free(a);
}
template<class T> int strman::findItem(const T *item,T **itemlist)
{
    int i;
    int n=strman::explode_count(itemlist);
    for(i=0;i<n;i++)
    {
        if(str::cmp(item,itemlist[i])==0)return i;
    }
    return -1;
}
template<class T> T *strman::getItem(int itemid,T **itemlist)
{
    if(itemid<0)return 0;
    if(itemid>=strman::explode_count(itemlist))return 0;
    return itemlist[itemid];
}

template<class T> bool strman::isprefix(const T *a,const T *b)
{
    unsigned int i=0;
    while(a[i])
    {
        if(a[i]!=b[i])return false;
        i++;
    }
    return true;
}
template<class T> bool strman::issuffix(const T *a,const T *b)
{
    unsigned int i=0;
    unsigned int aln=str::len(a);
    unsigned int bln=str::len(b);
    if(bln<aln)return false;
    unsigned int p=bln-aln;
    while(a[i])
    {
        if(a[i]!=b[p+i])return false;
        i++;
    }
    return true;
}
template<class T> bool strman::issubstr(const T *a,const T *b)
{
    unsigned int i=0;
    while(b[i])
    {
        if(a[0]==b[i])
        {
            if(strman::isprefix(a,&b[i]))return true;
        }
        i++;
    }
    return false;
}
template<class T> unsigned int strman::findsubstr(const T *a,const T *b)
{
    unsigned int i=0;
    while(b[i])
    {
        if(a[0]==b[i])
        {
            if(strman::isprefix(a,&b[i]))return i;
        }
        i++;
    }
    return i;
}
//SUBSTRMATCH
template<class T> bool strman::substrmatch(const T *searchpat,const T *text)
{
    int ln;
    if(searchpat[0]=='*')
    {
        ln=str::len(searchpat);
        if(searchpat[ln-1]=='*')
        {
            T *s=(T *)malloc((str::len(searchpat))*sizeof(T));
            str::cpy(s,&searchpat[1]);
            s[ln-2]=0;
            bool b=strman::issubstr(s,text);
            free(s);
            return b;
        }
        else
        {
            return strman::issuffix(&searchpat[1],text);
        }
    }
    else
    {
        ln=str::len(searchpat);
        if(searchpat[ln-1]=='*')
        {
            return strman::isprefix(&searchpat[1],text);
        }
        else
        {
            return str::cmp(&searchpat[1],text)==0;
        }
    }
}
//MATCH
template<class T> bool strman::matchpat(T *a,T *b)
{
    return matchpat_i(a,b,0,0);
}
template<class T> bool strman::matchpat_i(T *a,T *b,unsigned int pos_a,unsigned int pos_b)
{
    if(a[pos_a]==0 && b[pos_b]==0)
    {
        return true;
    }
    if(a[pos_a]=='*' && b[pos_b]==0)
    {
        return true;
    }
    if(a[pos_a]==0 && b[pos_b]=='*')
    {
        return true;
    }
    if(a[pos_a]!='*' && b[pos_b]!='*')
    {
        if(a[pos_a]==b[pos_b])
        {
            return matchpat_i(a,b,pos_a+1,pos_b+1);
        }
        else
        {
            return false;
        }
    }
    if(a[pos_a]=='*' && b[pos_b]=='*')
    {
        bool h=matchpat_i(a,b,pos_a,pos_b+1);
        h=h || matchpat_i(a,b,pos_a+1,pos_b);
        if(h)return true;
        else return matchpat_i(a,b,pos_a+1,pos_b+1);
    }
    if(a[pos_a]!='*' && b[pos_b]=='*')
    {
        T *tmp;
        unsigned int pos_t;
        pos_t=pos_a;
        pos_a=pos_b;
        pos_b=pos_t;
        tmp=a;
        a=b;
        b=tmp;
    }
    if(a[pos_a]=='*' && b[pos_b]!='*')
    {
        T s=a[pos_a+1];
        unsigned int bp=pos_b;
        while(true)
        {
            if(b[bp]==s)
            {
                if(s==0)return true;
                if(matchpat_i(a,b,pos_a+2,bp+1))return true;
            }
            if(b[bp]==0)return false;
            bp++;
        }
        return false;
    }
    return false;
}
template<class T> bool strman::matchsymbol(const T *str,size_t pos_in_str,const T *symbols)
{
    int h=0;
    while(symbols[h])
    {
        if(str[pos_in_str]==symbols[h++])
        {
            return true;
        }
    }
    return false;
}
template<class T> bool strman::matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1)
{
    if(matchsymbol(str,pos_in_str,symbols0))return true;
    if(matchsymbol(str,pos_in_str,symbols1))return true;
    return false;
}
template<class T> bool strman::matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2)
{
    if(matchsymbol(str,pos_in_str,symbols0))return true;
    if(matchsymbol(str,pos_in_str,symbols1))return true;
    if(matchsymbol(str,pos_in_str,symbols2))return true;
    return false;
}
template<class T> bool strman::matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2,const T *symbols3)
{
    if(matchsymbol(str,pos_in_str,symbols0))return true;
    if(matchsymbol(str,pos_in_str,symbols1))return true;
    if(matchsymbol(str,pos_in_str,symbols2))return true;
    if(matchsymbol(str,pos_in_str,symbols3))return true;
    return false;
}
#endif
