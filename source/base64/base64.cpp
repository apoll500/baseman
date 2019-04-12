/*******************************************************************************
*                                                                              *
*  base64.cpp                                                                  *
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
#include "base64.h"

/***
table of ASCII characters
            (ASC)  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95  96  97  98  99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127
            (CHR)                                                                                                                                      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /   0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?   @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _   `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~
                   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
                  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
***/
#define B64TAB {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1}
#define B64URL {  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, 63, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1}

//------------------------------------------------------------------------------
//
//  #begin encode -- memory allocating versions
//
//------------------------------------------------------------------------------
/**bmc
DEF encode:POINTER,inc_base64
{
    txt_bevore="The following methods returns a new allocated buffer, in which the output is written.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_alloc1";
    brief="Encodes the input from buffer <code>data</code> and returns it as base64 encoded string.";
    param:lp_data{};
    param:lp_length{};
    return:cp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        setupcode
        {
            ->
            // setting up preconditions
            <-
        }
        testcode
        {
            ->
                void *temp=base64::decode(retv);
                if(temp)
                {
                    if(test::datacmp(temp,data,length)!=0)
                    {
                        test_successful=TEST_FAIL;
                        printf("[ERROR] Decode-Test failed.\nretv=%s\n",retv);
                        printf("data-length=%d\n",length);
                        //for(unsigned int k=0;k< length;k++){printf("data: Byte %d: %d=%d\n",k,((char *)data)[k],((char *)temp)[k]);}
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                    printf("[ERROR] base64::decode returned 0.\\n");
                }
            <-
        }
    }
}
*/
char *base64::encode(void *data,unsigned int length)
{
    return encode(data,length,true);
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_alloc2";
    brief="Encodes the input from buffer <code>data</code> and returns it as base64 encoded string.";
    param:lp_data{};
    param:lp_length{};
    param:lp_padding{};
    return:cp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        testcode
        {
            ->
                void *temp=base64::decode(retv);
                if(temp)
                {
                    if(test::datacmp(temp,data,length)!=0)
                    {
                        test_successful=TEST_FAIL;
                        printf("[ERROR] Decode-Test failed.\nretv=%s\n",retv);
                        printf("data-length=%d\n",length);
                        //for(unsigned int k=0;k< length;k++){printf("data: Byte %d: %d=%d\n",k,((char *)data)[k],((char *)temp)[k]);}
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                    printf("[ERROR] base64::decode returned 0.\\n");
                }
            <-
        }
    }
}
*/
char *base64::encode(void *data,unsigned int length,bool padding)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode(data,length,bstr,padding);
    return bstr;
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_alloc3";
    brief="Encodes the input from buffer <code>data</code> and returns it as base64 encoded string.";
    param:lp_data{};
    param:lp_length{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:cp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        testcode
        {
            ->
                void *temp=base64::decode(retv,sym,pad);
                if(temp)
                {
                    if(test::datacmp(temp,data,length)!=0)
                    {
                        test_successful=TEST_FAIL;
                        printf("[ERROR] Decode-Test failed.\nretv=%s\n",retv);
                        printf("data-length=%d\n",length);
                        //for(unsigned int k=0;k< length;k++){printf("data: Byte %d: %d=%d\n",k,((char *)data)[k],((char *)temp)[k]);}
                    }
                    free(temp);
                }
                else
                {
                    test_successful=TEST_FAIL;
                    printf("[ERROR] base64::decode returned 0.\\n");
                }
            <-
        }
    }
}
*/
char *base64::encode(void *data,unsigned int length,bool padding,const char *sym,char pad)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode(data,length,bstr,padding,sym,pad);
    return bstr;
}
//------------------------------------------------------------------------------
//  #end
//  #begin encode -- writing to existing buffer
//
//------------------------------------------------------------------------------
/**bmc
DEF encode:POINTER,inc_base64
{
    txt_bevore="The following methods write the encoded data into an existing buffer.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    return:i="Returns 0 on successful execution.";
    remark:REMARK
    {
        text="Mind that <code>bstr</code> has to be an already allocated buffer of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
int base64::encode(void *data,unsigned int length,char *bstr)
{
    return encode(data,length,bstr,true);
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_padding{};
    return:i="Returns 0 on successful execution.";
    remark:REMARK
    {
        text="Mind that <code>bstr</code> has to be an already allocated buffer of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
int base64::encode(void *data,unsigned int length,char *bstr,bool padding)
{
    return encode(data,length,bstr,padding,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",'=');
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="Returns 0 on successful execution.";
    remark:REMARK
    {
        text="Mind that <code>bstr</code> has to be an already allocated buffer of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr,sym,pad);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
//  #begin encode -- writing to existing buffer with length check
//
//------------------------------------------------------------------------------
/**bmc
DEF encode:POINTER,inc_base64
{
    txt_bevore="These versions, perform a length check on the output buffer.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_s1";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_bln{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
int base64::encode(void *data,unsigned int length,char *bstr,unsigned int bln)
{
    return encode(data,length,bstr,bln,true);
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_s2";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_bln{};
    param:lp_padding{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
int base64::encode(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding)
{
    if(encode_length(length)<bln-1)return encode(data,length,bstr,padding);
    return 1;
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_s3";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_bln{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
    test:CTEST
    {
        name="test1";
        desc="Encode/Decode-Test.";
        generate="$DATA_LEN=INTEGER(min=1,max=1024)";
        retv="0";
        testcode
        {
            ->
                void *temp_decoded=base64::decode(bstr,sym,pad);
                if(temp_decoded)
                {
                    if(!(test::datacmp(data_copy,temp_decoded,gen.getInteger("$DATA_LEN"))==0))
                    {
                        test_successful=TEST_FAIL;
                    }
                    free(temp_decoded);
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
/**bmc
DEF encode:POINTER,inc_base64
{
    txt_bevore="These versions reallocate the memory of the output buffer if necessary";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_realloc1";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr2{};
    param:lp_bln2{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::encode(void *data,unsigned int length,char **bstr,unsigned int *bln)
{
    return encode(data,length,bstr,bln,true);
}
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_realloc2";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr2{};
    param:lp_bln2{};
    param:lp_padding{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF encode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_realloc3";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr2{};
    param:lp_bln2{};
    param:lp_padding{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF encode_url:POINTER,inc_base64
{
    sep_bevore="10px";
    txt_bevore="These versions use different encoding symbols to encode data in urls.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="Encodes the input from buffer <code>data</code> and returns it as base64 encoded string.";
    param:lp_data{};
    param:lp_length{};
    param:lp_padding{};
    return:cp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
}
*/
char *base64::encode_url(void *data,unsigned int length,bool padding)
{
    char *bstr=(char *)malloc((encode_length(length)+1)*sizeof(char));
    encode_url(data,length,bstr,padding);
    return bstr;
}
/**bmc
DEF encode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_padding{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::encode_url(void *data,unsigned int length,char *bstr,bool padding)
{
    return encode(data,length,bstr,padding,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_",'=');
}
/**bmc
DEF encode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr{};
    param:lp_bln{};
    param:lp_padding{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::encode_url(void *data,unsigned int length,char *bstr,unsigned int bln,bool padding)
{
    if(encode_length(length)<bln-1)return encode_url(data,length,bstr,padding);
    return 1;
}
/**bmc
DEF encode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="4";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp_data{};
    param:lp_length{};
    param:lp_bstr2{};
    param:lp_bln2{};
    param:lp_padding{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF encode_length:POINTER,inc_base64
{
    sep_bevore="10px";
    txt_bevore="Calculates the lenght of the encoded base64 string.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="This function calculates the length (in bytes) of the encoded string.";
    param:lp_a_length{};
    return:ui="The length in bytes of the base64 encoded string.";
    docu
    {
        THEINTERFACE;
    }
}
*/
unsigned int base64::encode_length(unsigned int length)
{
    return (length+2)/3*4;
}
/**bmc
DEF encode_length:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="This function calculates the length (in bytes) of the encoded string.";
    param:lp_a_length{};
    param:lp_padding{};
    return:ui="The length in bytes of the base64 encoded string.";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF decode_length:POINTER,inc_base64
{
    sep_bevore="10px";
    txt_bevore="Calculates the length of the decoded data.";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="This function calculates the length (in bytes) of the decoded string.";
    param:lp_b_length{};
    return:ui="The length in bytes of the decoded data.";
    docu
    {
        THEINTERFACE;
    }
}
*/
unsigned int base64::decode_length(unsigned int length)
{
    unsigned int extra=length%4;
    if(extra)return length/4*3+extra-1;
    return length/4*3;
}
/**bmc
DEF decode_length:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="This function calculates the length (in bytes) of the decoded string.";
    param:lp2_bstr{};
    return:ui="The length in bytes of the decoded data.";
    docu
    {
        THEINTERFACE;
    }
}
*/
unsigned int base64::decode_length(const char *bstr)
{
    unsigned int i=0;
    while(bstr[i] && bstr[i]!='=')i++;
    return decode_length(i);
}
/**bmc//------------------------------------------------------------------------------
// private: int base64::decode_intern(char *bstr,void *data,const char *symtab,char pad)
//------------------------------------------------------------------------------
*/
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
//  #begin decode -- writing to existing buffer
//
//------------------------------------------------------------------------------
/**bmc
DEF decode:POINTER,inc_base64
{
    sep_bevore="10px";
    txt_bevore="writing to existing buffer";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    param:lp2_bstr{};
    param:lp2_data{};
    return:i="";
    remark:REMARK
    {
        text="Mind that the buffer <code>data</code> has to be already allocated and of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::decode(const char *bstr,void *data)
{
    const char b64tab[]=B64TAB;
    return decode_intern(bstr,data,b64tab,'=');
}
/**bmc
DEF decode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    param:lp2_bstr{};
    param:lp2_data{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="";
    remark:REMARK
    {
        text="Mind that the buffer <code>data</code> has to be already allocated and of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
}
*/
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
//  #begin decode -- allocating a new buffer
//
//------------------------------------------------------------------------------
/**bmc
DEF decode:POINTER,inc_base64
{
    txt_bevore="allocating a new buffer";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_alloc1";
    brief="Decodes the input from buffer <code>bstr</code> and returns the decoded data.";
    param:lp2_bstr{};
    return:vp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
}
*/
void *base64::decode(const char *bstr)
{
    void *data=malloc(decode_length(bstr)*sizeof(char));
    int err=decode(bstr,data);
    if(!err)return data;
    free(data);
    return 0;
}
/**bmc
DEF decode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_alloc2";
    brief="Decodes the input from buffer <code>bstr</code> and returns the decoded data.";
    param:lp2_bstr{};
    param:lp_sym{};
    param:lp_pad{};
    return:vp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
}
*/
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
//  #begin decode -- writing to existing buffer with length check
//
//------------------------------------------------------------------------------
/**bmc
DEF decode:POINTER,inc_base64
{
    txt_bevore="writing to existing buffer with length check";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_s1";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp2_bstr{};
    param:lp2_data{};
    param:lp2_dataln{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::decode(const char *bstr,void *data,unsigned int dataln)
{
    if(decode_length(bstr)<=dataln)return decode(bstr,data);
    return 1;
}
/**bmc
DEF decode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_s2";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp2_bstr{};
    param:lp2_data{};
    param:lp2_dataln{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF decode:POINTER,inc_base64
{
    txt_bevore="reallocating version";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_realloc1";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp2_bstr{};
    param:lp2_data2{};
    param:lp2_dataln2{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF decode:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="_realloc2";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp2_bstr{};
    param:lp2_data2{};
    param:lp2_dataln2{};
    param:lp_sym{};
    param:lp_pad{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
/**bmc
DEF decode_url:POINTER,inc_base64
{
    sep_bevore="10px";
    txt_bevore="These versions are for url decoding";
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    param:lp2_bstr{};
    param:lp2_data{};
    return:i="";
    remark:REMARK
    {
        text="Mind that the buffer <code>data</code> has to be already allocated and of sufficient size.";
    }
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::decode_url(const char *bstr,void *data)
{
    const char b64tab[]=B64URL;
    return decode_intern(bstr,data,b64tab,'=');
}
/**bmc
DEF decode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    param:lp2_bstr{};
    return:vp="";
    remark:remark_free_retval{};
    docu
    {
        THEINTERFACE;
    }
}
*/
void *base64::decode_url(const char *bstr)
{
    void *data=malloc(decode_length(bstr)*sizeof(char));
    int err=decode_url(bstr,data);
    if(!err)return data;
    free(data);
    return 0;
}
/**bmc
DEF decode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    brief="Encodes the input from buffer <code>data</code> and writes the output to the existing buffer <code>bstr</code>.";
    info="This version, performs a length check on the output buffer.";
    param:lp2_bstr{};
    param:lp2_data{};
    param:lp2_dataln{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
int base64::decode_url(const char *bstr,void *data,unsigned int dataln)
{
    if(decode_length(bstr)<=dataln)return decode_url(bstr,data);
    return 1;
}
/**bmc
DEF decode_url:POINTER,inc_base64
{
    base64="TRUE";
    function="@this.parent.NAME";
    suffix="4";
    brief="Decodes the input from buffer <code>bstr</code> and writes the output to the existing buffer <code>data</code>.";
    info="This version, performs a length check on the output buffer. If the buffer is to small, the function will automatically reallocate the buffer.";
    param:lp2_bstr{};
    param:lp2_data2{};
    param:lp2_dataln2{};
    return:i="";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
