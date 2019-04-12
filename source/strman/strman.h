/*******************************************************************************
*                                                                              *
*  strman.h                                                                    *
*                                                                              *
*  This file is part of "mods/baseman/cli". (this program)                     *
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
// strman.h
#ifndef MOD_strman_H
#define MOD_strman_H

#include "wwrap/str.h"
#include "wwrap/conststr.h"

#include <stdlib.h>

#include "strman/import/prokee.h"

/*********************************************************************
*                                                                    *
*  strman-Functions                                                  *
*                                                                    *
*********************************************************************/
class strman
{
public:
    /*****************************************************************
    *                                                                *
    *  explode()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static T **explode(const T *sep,const T *str);
    template<class T> static int explode_count(T **a);
    template<class T> static void explode_free(T **a);
    template<class T> static int findItem(const T *item,T **itemlist);
    template<class T> static T *getItem(int itemid,T **itemlist);
    /*****************************************************************
    *                                                                *
    *  level2()                                                      *
    *                                                                *
    *****************************************************************/
    template<class T> static void level2_free(T **a);
    template<class T> static bool level2_replaceItem_realloc(T **itemlist,const T *old_item,const T *new_item);
    template<class T> static bool level2_setItem_realloc(int itemid,T **itemlist,const T *item);
    template<class T> static bool level2_setItem_malloc(int itemid,T **itemlist,const T *item);
    template<class T> static bool level2_addItem_malloc(T **itemlist,const T *item);
    template<class T> static T **level2_create(int ln,T ***itemlist);
    template<class T> static bool level2_freeItem(int itemid,T **itemlist);
    /*****************************************************************
    *                                                                *
    *  level2() names <-> values                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static bool nvlist_add(T **names,T **values,const T *item_name);
    template<class T> static bool nvlist_add_if_missing(T **names,T **values,const T *item_name);
    template<class T> static bool nvlist_remove(T **names,T **values,const T *item_name);
    template<class T> static T *nvlist_get(T **names,T **values,const T *item_name);
    template<class T> static bool nvlist_set(T **names,T **values,const T *item_name,const T *item_value);
    template<class T> static bool nvlist_create(T ***names,T ***values,int ln);
    template<class T> static void nvlist_free(T **names,T **values);
    template<class T> static void nvlist_print_all(T **names,T **values);
    /*****************************************************************
    *                                                                *
    *  concat()                                                      *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  multistr()                                                    *
    *                                                                *
    *****************************************************************/
    template<class T> static T *nullconcat(T *a,T *b);
    template<class T> static T *nullcopy(T *a,T *b);
    template<class T> static T *nullcopy_new(T **a,T *b);
    /*****************************************************************
    *                                                                *
    *  isprefix()                                                    *
    *  issuffix()                                                    *
    *                                                                *
    *****************************************************************/
    template<class T> static bool isprefix(const T *a,const T *b);
    template<class T> static bool issuffix(const T *a,const T *b);
    template<class T> static bool issubstr(const T *a,const T *b);
    template<class T> static unsigned int findsubstr(const T *a,const T *b);
    /*****************************************************************
    *                                                                *
    *  match()                                                       *
    *                                                                *
    *****************************************************************/
    template<class T> static bool substrmatch(const T *searchpat,const T *text);
    template<class T> static bool matchpat(T *a,T *b);
    template<class T> static bool matchpat_i(T *a,T *b,unsigned int pos_a,unsigned int pos_b);
    /*****************************************************************
    *                                                                *
    *  matchsymbol()                                                 *
    *                                                                *
    *****************************************************************/
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2);
    template<class T> static bool matchsymbol(const T *str,size_t pos_in_str,const T *symbols0,const T *symbols1,const T *symbols2,const T *symbols3);
    /*****************************************************************
    *                                                                *
    *  isprefix()                                                    *
    *                                                                *
    *****************************************************************/
};

#include "strman/import/modules.h"

/*****************************************************************
*                                                                *
*  explode()                                                     *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  level2()                                                      *
*                                                                *
*****************************************************************/
template<class T> void strman::level2_free(T **itemlist)
{
    int i=0;
    while(itemlist[i])
    {
        if(itemlist[i])free(itemlist[i]);
        i++;
    }
    free(itemlist);
}
template<class T> bool strman::level2_replaceItem_realloc(T **itemlist,const T *old_item,const T *new_item)
{
    int itemid=strman::findItem(old_item,itemlist);
    if(itemid==-1)return false;
    return strman::level2_setItem_realloc(itemid,itemlist,new_item);
}
template<class T> bool strman::level2_setItem_realloc(int itemid,T **itemlist,const T *item)
{
    if(itemid<0)return false;
    if(itemid>=strman::explode_count(itemlist))return false;
    if(itemlist[itemid]==0)itemlist[itemid]=(T *)malloc((str::len(item)+1)*sizeof(T));
    else itemlist[itemid]=(T *)realloc(itemlist[itemid],(str::len(item)+1)*sizeof(T));
    str::cpy(itemlist[itemid],item);
    return true;
}
template<class T> bool strman::level2_setItem_malloc(int itemid,T **itemlist,const T *item)
{
    if(itemid<0)return false;
    if(itemid>=strman::explode_count(itemlist))return false;
    itemlist[itemid]=(T *)malloc((str::len(item)+1)*sizeof(T));
    str::cpy(itemlist[itemid],item);
    return true;
}
template<class T> bool strman::level2_addItem_malloc(T **itemlist,const T *item)
{
    int itemid=strman::explode_count(itemlist);
    itemlist[itemid]=(T *)malloc((str::len(item)+1)*sizeof(T));
    str::cpy(itemlist[itemid],item);
    return true;
}
template<class T> T **strman::level2_create(int ln,T ***itemlist)
{
    if(ln<1)return 0;
    *itemlist=(T **)malloc((ln+1)*sizeof(T *));
    memset(*itemlist,0,(ln+1)*sizeof(T *));
    return *itemlist;
}
template<class T> bool strman::level2_freeItem(int itemid,T **itemlist)
{
    if(itemid<0)return false;
    int ln=strman::explode_count(itemlist);
    if(itemid>=ln)return false;
    free(itemlist[itemid]);
    itemlist[itemid]=itemlist[ln-1];
    itemlist[ln-1]=0;
    return true;
}
/*****************************************************************
*                                                                *
*  level2() names <-> values                                     *
*                                                                *
*****************************************************************/
template<class T> bool strman::nvlist_add(T **names,T **values,const T *item_name)
{
    strman::level2_addItem_malloc(names,item_name);
    T ns;
    strman::level2_addItem_malloc(values,conststr::cast(&ns,""));
    return true;
}
template<class T> bool strman::nvlist_add_if_missing(T **names,T **values,const T *item_name)
{
    if(strman::findItem(item_name,names)==-1)
    {
        strman::level2_addItem_malloc(names,item_name);
        T ns;
        strman::level2_addItem_malloc(values,conststr::cast(&ns,""));
    }
    return true;
}
template<class T> bool strman::nvlist_remove(T **names,T **values,const T *item_name)
{
    int itemid=strman::findItem(item_name,names);
    strman::level2_freeItem(itemid,names);
    strman::level2_freeItem(itemid,values);
    return true;
}
template<class T> T *strman::nvlist_get(T **names,T **values,const T *item_name)
{
    return strman::getItem(strman::findItem(item_name,names),values);
}
template<class T> bool strman::nvlist_set(T **names,T **values,const T *item_name,const T *item_value)
{
    return strman::level2_setItem_realloc(strman::findItem(item_name,names),values,item_value);
}
template<class T> bool strman::nvlist_create(T ***names,T ***values,int ln)
{
    strman::level2_create(ln,names);
    strman::level2_create(ln,values);
    return true;
}
template<class T> void strman::nvlist_free(T **names,T **values)
{
    strman::level2_free(names);
    strman::level2_free(values);
}
#include "wwrap/osio.h"
template<class T> void strman::nvlist_print_all(T **names,T **values)
{
    int n=strman::explode_count(names);
    for(int i=0;i<n;i++)
    {
        if(sizeof(T)==1)osio::print("--> %s = %s\n",names[i],values[i]);
    }
}
/*****************************************************************
*                                                                *
*  concat()                                                      *
*                                                                *
*****************************************************************/
/*****************************************************************
*                                                                *
*  multistr()                                                    *
*                                                                *
*****************************************************************/
template<class T> T *strman::nullconcat(T *a,T *b)
{
    int p=str::len(a)+1;
    str::cpy(&a[p],b);
    a[p+str::len(b)+1]=0;
    return a;
}
template<class T> T *strman::nullcopy(T *a,T *b)
{
    str::cpy(a,b);
    a[str::len(a)+1]=0;
    return a;
}
template<class T> T *strman::nullcopy_new(T **a,T *b)
{
    if(*a==0)*a=(T *)malloc((2+str::len(b))*sizeof(T));
    return strman::nullcopy(*a,b);
}
/*****************************************************************
*                                                                *
*  isprefix()                                                    *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  match()                                                       *
*                                                                *
*****************************************************************/
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
        char s=a[pos_a+1];
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
/*****************************************************************
*                                                                *
*  matchsymbol()                                                 *
*                                                                *
*****************************************************************/
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
