/*******************************************************************************
*                                                                              *
*  base64.h                                                                    *
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
#ifndef H_BASE64
#define H_BASE64

#include "wwrap/str.h"

#include <stdlib.h>
#include <math.h>

#include "base64/import/prokee.h"

/*******************************************************************************
*                                                                              *
*  base64-Functions                                                            *
*                                                                              *
*******************************************************************************/
class base64
{
public:
    /*****************************************************************
    *                                                                *
    *  encode()                                                      *
    *                                                                *
    *****************************************************************/
    //--------------------------------------------------------------------------
    //the encoder
    //--------------------------------------------------------------------------
    static int encode(void *data,unsigned int length,char *bstr,bool padding,const char *sym,char pad);
    //--------------------------------------------------------------------------
    //encoder wrappers
    //--------------------------------------------------------------------------
    //memory allocating versions using strings as input
    template<class T> static char *encode(const T *s);
    template<class T> static char *encode(const T *s,bool padding);
    template<class T> static char *encode(const T *s,bool padding,const char *sym,char pad);
    //writing to existing buffer
    static int encode(void *data,unsigned int length,char *bstr);
    static int encode(void *data,unsigned int length,char *bstr,bool padding);
    static int encode_url(void *data,unsigned int length,char *bstr,bool padding);
    //memory allocating versions
    static char *encode(void *data,unsigned int length);
    static char *encode(void *data,unsigned int length,bool padding);
    static char *encode(void *data,unsigned int length,bool padding,const char *sym,char pad);
    static char *encode_url(void *data,unsigned int length,bool padding);
    //writing to existing buffer with length check
    static int encode(void *data,unsigned int length,char *bstr,unsigned int bln);
    static int encode(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding);
    static int encode(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding,const char *sym,char pad);
    static int encode_url(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding);
    //reallocating versions
    static int encode(void *data,unsigned int length,char **bstr,unsigned int *bln);
    static int encode(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding);
    static int encode(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding,const char *sym,char pad);
    static int encode_url(void *data,unsigned int length,char **bstr,unsigned int *bln,bool padding);
    /*****************************************************************
    *                                                                *
    *  decode()                                                      *
    *                                                                *
    *****************************************************************/
    //--------------------------------------------------------------------------
    //the decoder
    //--------------------------------------------------------------------------
    static int decode_intern(const char *bstr,void *data,const char *symtab,char pad);
    //--------------------------------------------------------------------------
    //decode wrappers
    //--------------------------------------------------------------------------
    //writing to existing buffer
    static int decode(const char *bstr,void *data);
    static int decode(const char *bstr,void *data,const char *sym,char pad);
    static int decode_url(const char *bstr,void *data);
    //memory allocating versions
    static void *decode(const char *bstr);
    static void *decode(const char *bstr,const char *sym,char pad);
    static void *decode_url(const char *bstr);
    //writing to existing buffer with lenth check
    static int decode(const char *bstr,void *data,unsigned int dataln);
    static int decode(const char *bstr,void *data,unsigned int dataln,const char *sym,char pad);
    static int decode_url(const char *bstr,void *data,unsigned int dataln);
    //reallocating versions
    static int decode(const char *bstr,void **data,unsigned int *dataln);
    static int decode(const char *bstr,void **data,unsigned int *dataln,const char *sym,char pad);
    static int decode_url(const char *bstr,void **data,unsigned int *dataln);
    /*****************************************************************
    *                                                                *
    *  length()                                                      *
    *                                                                *
    *****************************************************************/
    static unsigned int encode_length(unsigned int length);
    static unsigned int encode_length(unsigned int length,bool padding);
    static unsigned int decode_length(unsigned int length);
    static unsigned int decode_length(const char *bstr);
};

#include "base64/import/modules.h"

//------------------------------------------------------------------------------
//
//  #begin encode -- str versions
//
//------------------------------------------------------------------------------
/**bmc
DEF encode:POINTER,inc_base64
{
    sep_bevore="0px";
    txt_bevore="These methods can be used, if the input for the encoder is a null-terminated string.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_str1";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_str{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_stdenc{};
    remark:remark_stdenc1{};
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        followup
        {
            ->
                void *temp=base64::decode(retv);
                if(temp)
                {
                    free(retv);
                    retv=(char *)temp;
                }
            <-
        }
        retv="in_str";
        test_cleanup
        {
            ->
            // ---> whatever
            <-
        }
    }
}
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_str2";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_str{};
    param:lp_padding{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_stdenc0{};
    remark:remark_stdenc1{};
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        followup
        {
            ->
                void *temp=base64::decode(retv);
                if(temp)
                {
                    free(retv);
                    retv=(char *)temp;
                }
            <-
        }
        retv="in_str";
        test_cleanup
        {
            ->
            // ---> whatever
            <-
        }
    }
}
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_str3";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_str{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        followup
        {
            ->
                void *temp=base64::decode(retv,sym,pad);
                if(temp)
                {
                    free(retv);
                    retv=(char *)temp;
                }
            <-
        }
        retv="in_str";
    }
}
*/
//------------------------------------------------------------------------------
//  #end
//  #begin encode -- str versions
//
//------------------------------------------------------------------------------
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_wcs1";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_wcs{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_stdenc{};
    remark:remark_stdenc1{};
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        testcode
        {
            ->
                wchar_t *temp=(wchar_t *)base64::decode(retv);
                if(temp)
                {
                    if(str::cmp(temp,in_str)!=0)
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                }
            <-
        }
    }
}
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_wcs2";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_wcs{};
    param:lp_padding{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_stdenc0{};
    remark:remark_stdenc1{};
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        testcode
        {
            ->
                wchar_t *temp=(wchar_t *)base64::decode(retv);
                if(temp)
                {
                    if(str::cmp(temp,in_str)!=0)
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                }
            <-
        }
    }
}
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_wcs3";
    brief="Returns the base64 encoded representation of the input string <code>in_str</code>.";
    param:lp_wcs{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:cp="The base64 encoded representation of the input string <code>in_str</code>.";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        testcode
        {
            ->
                wchar_t *temp=(wchar_t *)base64::decode(retv,sym,pad);
                if(temp)
                {
                    if(str::cmp(temp,in_str)!=0)
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                }
            <-
        }
    }
}
*/
//------------------------------------------------------------------------------
// #end
//------------------------------------------------------------------------------
template<class T> char *base64::encode(const T *s)
{
    return encode(s,(str::len(s)+1)*sizeof(T));
}
template<class T> char *base64::encode(const T *s,bool padding)
{
    return encode((void *)s,(str::len(s)+1)*sizeof(T),padding);
}
template<class T> char *base64::encode(const T *s,bool padding,const char *sym,char pad)
{
    return encode((void *)s,(str::len(s)+1)*sizeof(T),padding,sym,pad);
}

#endif
