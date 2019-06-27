/*******************************************************************************
*                                                                              *
*  base64.cpp                                                                  *
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
#include "base64.h"
#define B64TAB {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1}
#define B64URL {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1}
//------------------------------------------------------------------------------
//
//  #begin encode -- memory allocating versions
//
//------------------------------------------------------------------------------
char *base64::encode(void *data,unsigned int length)
{
    return encode(data,length,true);
}
char *base64::encode(void *data,unsigned int length,bool padding)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode(data,length,bstr,padding);
    return bstr;
}
char *base64::encode(void *data,unsigned int length,bool padding,const char *sym,char pad)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode(data,length,bstr,padding,sym,pad);
    return bstr;
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode -- writing to existing memory block
//
//------------------------------------------------------------------------------
int base64::encode(void *data,unsigned int length,char *bstr)
{
    return encode(data,length,bstr,true);
}
int base64::encode(void *data,unsigned int length,char *bstr,bool padding)
{
    return encode(data,length,bstr,padding,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",'=');
}
int base64::encode(void *data,unsigned int length,char *bstr,bool padding,const char *sym,char pad)
{
    unsigned int pos=0;
    unsigned int spos=0;
    if(str::len(sym)<64)
    {
        bstr[0]=0;
        return 1;
    }
    while(pos<length)
    {
        if(pos<length-2)
        {
            bstr[spos++]=sym[((unsigned char *)data)[pos]>>2];
            bstr[spos++]=sym[(((unsigned char *)data)[pos]<<4 & 48) | ((unsigned char *)data)[pos+1]>>4];
            bstr[spos++]=sym[(((unsigned char *)data)[pos+1]<<2 & 60) | ((unsigned char *)data)[pos+2]>>6];
            bstr[spos++]=sym[((unsigned char *)data)[pos+2] & 63];
        }
        else if(pos<length-1)
        {
            bstr[spos++]=sym[((unsigned char *)data)[pos]>>2];
            bstr[spos++]=sym[(((unsigned char *)data)[pos]<<4 & 48) | ((unsigned char *)data)[pos+1]>>4];
            bstr[spos++]=sym[((unsigned char *)data)[pos+1]<<2 & 60];
            if(padding)bstr[spos++]=pad;
        }
        else
        {
            bstr[spos++]=sym[((unsigned char *)data)[pos]>>2];
            bstr[spos++]=sym[((unsigned char *)data)[pos]<<4 & 48];
            if(padding)
            {
                bstr[spos++]=pad;
                bstr[spos++]=pad;
            }
        }
        pos+=3;
    }
    bstr[spos]=0;
    return 0;
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode -- writing to existing memory block with length check
//
//------------------------------------------------------------------------------
int base64::encode(void *data,unsigned int length,char *bstr,unsigned int bln)
{
    return encode(data,length,bstr,bln,true);
}
int base64::encode(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding)
{
    if(encode_length(length)<bln-1)return encode(data,length,bstr,padding);
    return 1;
}
int base64::encode(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding,const char *sym,char pad)
{
    if(encode_length(length)<bln-1)return encode(data,length,bstr,padding,sym,pad);
    return 1;
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode -- reallocating versions
//
//------------------------------------------------------------------------------
int base64::encode(void *data,unsigned int length,char **bstr,unsigned int *bln)
{
    return encode(data,length,bstr,bln,true);
}
int base64::encode(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding)
{
    unsigned int len=encode_length(length);
    if(len>=*bln-1)
    {
        *bln=len+1;
        *bstr=(char *)realloc(*bstr,*bln*sizeof(char));
    }
    return encode(data,length,*bstr,padding);
}
int base64::encode(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding,const char *sym,char pad)
{
    unsigned int len=encode_length(length);
    if(len>=*bln-1)
    {
        *bln=len+1;
        *bstr=(char *)realloc(*bstr,*bln*sizeof(char));
    }
    return encode(data,length,*bstr,padding,sym,pad);
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode_url
//
//------------------------------------------------------------------------------
char *base64::encode_url(void *data,unsigned int length,bool padding)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode_url(data,length,bstr,padding);
    return bstr;
}
int base64::encode_url(void *data,unsigned int length,char *bstr,bool padding)
{
    return encode(data,length,bstr,padding,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_",'=');
}
int base64::encode_url(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding)
{
    if(encode_length(length)<bln-1)return encode_url(data,length,bstr,padding);
    return 1;
}
int base64::encode_url(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding)
{
    unsigned int len=encode_length(length);
    if(len>=*bln-1)
    {
        *bln=len+1;
        *bstr=(char *)realloc(*bstr,*bln*sizeof(char));
    }
    return encode_url(data,length,*bstr,padding);
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode_length
//
//------------------------------------------------------------------------------
unsigned int base64::encode_length(unsigned int length)
{
    return (length+2)/3*4;
}
unsigned int base64::encode_length(unsigned int length,bool padding)
{
    if(padding)return encode_length(length);
    int extra=length%3;
    if(extra)return length/3*4+extra+1;
    return length/3*4;
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode_length
//
//------------------------------------------------------------------------------
unsigned int base64::decode_length(unsigned int length)
{
    unsigned int extra=length%4;
    if(extra)return length/4*3+extra-1;
    return length/4*3;
}
unsigned int base64::decode_length(const char *bstr)
{
    unsigned int i=0;
    while(bstr[i] && bstr[i]!='=')i++;
    return decode_length(i);
}
int base64::decode_intern(const char *bstr,void *data,const char *symtab,char pad)
{
    unsigned char symbol[4];
    unsigned int i=0,p=0;
    unsigned char k=0;
    while(bstr[i] && bstr[i]!=pad)
    {
        //-- cast from char to unsigned char -- all ascii characters allways have positiv values.
        symbol[k]=symtab[(unsigned char)bstr[i]];
        if(symbol[k]==(unsigned char)-1)return 4;//non-alphabet character
        if(k==3)
        {
            ((unsigned char *)data)[p]=symbol[0]<<2 | symbol[1]>>4;
            ((unsigned char *)data)[p+1]=symbol[1]<<4 | symbol[2]>>2;
            ((unsigned char *)data)[p+2]=symbol[2]<<6 | symbol[3];
            p+=3;
        }
        i++;
        k++;
        k%=4;
    }
    if(k==1)
    {
        return 2;//misplaced padding character or missing data
    }
    else if(k==2)
    {
        ((unsigned char *)data)[p]=symbol[0]<<2 | symbol[1]>>4;
        if(bstr[i]==pad)if(bstr[i+1]!=pad)return 3;//incomplete padding
    }
    else if(k==3)
    {
        ((unsigned char *)data)[p]=symbol[0]<<2 | symbol[1]>>4;
        ((unsigned char *)data)[p+1]=symbol[1]<<4 | symbol[2]>>2;
    }
    return 0;
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode -- writing to existing memory block
//
//------------------------------------------------------------------------------
int base64::decode(const char *bstr,void *data)
{
    const char b64tab[]=B64TAB;
    return decode_intern(bstr,data,b64tab,'=');
}
int base64::decode(const char *bstr,void *data,const char *sym,char pad)
{
    char symtab[256];
    memset(symtab,-1,256*sizeof(char));
    //-- cast from char to unsigned char -- all ascii characters allways have positiv values.
    for(unsigned int j=0;j<64;j++)
    {
        if(!sym[j])
        {
            return 1;
        }
        symtab[(unsigned char)sym[j]]=j;
    }
    return decode_intern(bstr,data,symtab,pad);
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode -- allocating a new memory block
//
//------------------------------------------------------------------------------
void *base64::decode(const char *bstr)
{
    void *data=malloc(decode_length(bstr)*sizeof(char));
    int err=decode(bstr,data);
    if(!err)return data;
    free(data);
    return 0;
}
char *base64::decode_string(const char *bstr)
{
    size_t ln=decode_length(bstr);
    char *data=(char *)malloc((ln+1)*sizeof(char));
    int err=decode(bstr,data);
    data[ln]=0;
    if(!err)return data;
    free(data);
    return 0;
}
void *base64::decode(const char *bstr,const char *sym,char pad)
{
    void *data=malloc(decode_length(bstr)*sizeof(char));
    int err=decode(bstr,data,sym,pad);
    if(!err)return data;
    free(data);
    return 0;
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode -- writing to existing memory block with length check
//
//------------------------------------------------------------------------------
int base64::decode(const char *bstr,void *data,unsigned int dataln)
{
    if(decode_length(bstr)<=dataln)return decode(bstr,data);
    return 1;
}
int base64::decode(const char *bstr,void *data,unsigned int dataln,const char *sym,char pad)
{
    if(decode_length(bstr)<=dataln)return decode(bstr,data,sym,pad);
    return 1;
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode -- reallocating version
//
//------------------------------------------------------------------------------
int base64::decode(const char *bstr,void **data,unsigned int *dataln)
{
    unsigned int len=decode_length(bstr);
    if(len>*dataln)
    {
        *dataln=len;
        *data=realloc(*data,*dataln);
    }
    return decode(bstr,*data);
}
int base64::decode(const char *bstr,void **data,unsigned int *dataln,const char *sym,char pad)
{
    unsigned int len=decode_length(bstr);
    if(len>*dataln)
    {
        *dataln=len;
        *data=realloc(*data,*dataln);
    }
    return decode(bstr,*data,sym,pad);
}
//------------------------------------------------------------------------------
//  #end
//  #begin decode_url
//
//------------------------------------------------------------------------------
int base64::decode_url(const char *bstr,void *data)
{
    const char b64tab[]=B64URL;
    return decode_intern(bstr,data,b64tab,'=');
}
void *base64::decode_url(const char *bstr)
{
    void *data=malloc(decode_length(bstr)*sizeof(char));
    int err=decode_url(bstr,data);
    if(!err)return data;
    free(data);
    return 0;
}
int base64::decode_url(const char *bstr,void *data,unsigned int dataln)
{
    if(decode_length(bstr)<=dataln)return decode_url(bstr,data);
    return 1;
}
int base64::decode_url(const char *bstr,void **data,unsigned int *dataln)
{
    unsigned int len=decode_length(bstr);
    if(len>*dataln)
    {
        *dataln=len;
        *data=realloc(*data,*dataln);
    }
    return decode_url(bstr,*data);
}

//------------------------------------------------------------------------------
// #end
//------------------------------------------------------------------------------
