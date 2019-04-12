/*******************************************************************************
*                                                                              *
*  strconv.cpp                                                                 *
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
// strconv.cpp
#include "strconv.h"

char *strconv::to_str(char **str_out,unsigned int *str_out_ln,const char *str_in)
{
    char *str_out_i;
    if(str_out)
    {
        str_out_i=*str_out;
    }
    else
    {
        str_out_i=0;
    }

    strcopy(&str_out_i,str_out_ln,str_in);

    if(str_out)
    {
        *str_out=str_out_i;
    }

    return str_out_i;
}

#ifdef OS_WIN

char *strconv::to_str(char **str_out,unsigned int *str_out_ln,const wchar_t *str_in)
{
    unsigned int str_out_ln_2;
    if(str_out_ln==0)str_out_ln_2=0;
    else str_out_ln_2=*str_out_ln;

    char *str_out_i;
    if(str_out)
    {
        str_out_i=*str_out;
    }
    else
    {
        str_out_i=0;
    }

    //WideCharToMultiByte
    //    int WideCharToMultiByte(
    //      _In_      UINT    CodePage,
    //      _In_      DWORD   dwFlags,
    //      _In_      LPCWSTR lpWideCharStr,
    //      _In_      int     cchWideChar,
    //      _Out_opt_ LPSTR   lpMultiByteStr,
    //      _In_      int     cbMultiByte,
    //      _In_opt_  LPCSTR  lpDefaultChar,
    //      _Out_opt_ LPBOOL  lpUsedDefaultChar
    //    );
    //  1: code-page: CP_UTF8
    //  2: flags: WC_ERR_INVALID_CHARS (moeglich fuer CP_UTF8 ab Vista)
    //  3: input_string: wchar_t
    //  4: length (-1 for null-terminated strings, this should also output a null-terminated string)
    //  5: out_buffer: char
    //  6: output buffer size (0 for requesting the required size (this is in BYTES))
    //  7: pointer to default character (NULL for System default value)
    //  8: indicates if default character is used, can be set to NULL. (MUST be set to NULL for CP_UTF8)

    int length_in_bytes=WideCharToMultiByte(CP_UTF8,0,str_in,-1,str_out_i,0,NULL,NULL);
    if(length_in_bytes==0)
    {
        //WideCharToMultiByte: The function returns 0 if it does not succeed.
        return 0;
    }

    memory_alloc(&str_out_i,&str_out_ln_2,length_in_bytes+1);
    memory_check(&str_out_i,&str_out_ln_2,length_in_bytes);

    if(!WideCharToMultiByte(CP_UTF8,0,str_in,-1,str_out_i,length_in_bytes,NULL,NULL))
    {
        //WideCharToMultiByte: The function returns 0 if it does not succeed.
        return 0;
    }

    if(str_out_ln!=0)*str_out_ln=str_out_ln_2;

    if(str_out)
    {
        *str_out=str_out_i;
    }

    return str_out_i;
}

wchar_t *strconv::to_wcs(wchar_t **str_out,unsigned int *str_out_ln,const char *str_in)
{
    unsigned int str_out_ln_2;
    if(str_out_ln==0)str_out_ln_2=0;
    else str_out_ln_2=*str_out_ln;

    wchar_t *str_out_i;
    if(str_out)
    {
        str_out_i=*str_out;
    }
    else
    {
        str_out_i=0;
    }

    //MultiByteToWideChar
    //    int MultiByteToWideChar(
    //      _In_      UINT   CodePage,
    //      _In_      DWORD  dwFlags,
    //      _In_      LPCSTR lpMultiByteStr,
    //      _In_      int    cbMultiByte,
    //      _Out_opt_ LPWSTR lpWideCharStr,
    //      _In_      int    cchWideChar
    //    );

    int length_in_characters=MultiByteToWideChar(CP_UTF8,0,str_in,-1,str_out_i,0);
    if(length_in_characters==0)
    {
        //MultiByteToWideChar: The function returns 0 if it does not succeed.
        return 0;
    }

    memory_alloc(&str_out_i,&str_out_ln_2,length_in_characters+1);
    memory_check(&str_out_i,&str_out_ln_2,length_in_characters);

    if(!MultiByteToWideChar(CP_UTF8,0,str_in,-1,str_out_i,length_in_characters))
    {
        //MultiByteToWideChar: The function returns 0 if it does not succeed.
        return 0;
    }

    if(str_out_ln!=0)*str_out_ln=str_out_ln_2;

    if(str_out)
    {
        *str_out=str_out_i;
    }

    return str_out_i;
}

#endif

wchar_t *strconv::to_wcs(wchar_t **str_out,unsigned int *str_out_ln,const wchar_t *str_in)
{
    wchar_t *str_out_i;
    if(str_out)
    {
        str_out_i=*str_out;
    }
    else
    {
        str_out_i=0;
    }

    strcopy(&str_out_i,str_out_ln,str_in);

    if(str_out)
    {
        *str_out=str_out_i;
    }

    return str_out_i;
}
