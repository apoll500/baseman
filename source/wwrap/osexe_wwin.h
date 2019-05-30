/*******************************************************************************
*                                                                              *
*  osexe_wwin.h                                                                *
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
#ifndef H_WWRAP_EXE_WWIN
#define H_WWRAP_EXE_WWIN

#include "macros/macros.h"

//------------------------------------------------------------------------------
/*
#ifdef COMPILE_PROKEE_MODULE
#define PROKEE_USE_WRAPPER
#include "strconv/v01/module.h"
#else
#include "strconv/strconv.h"
#endif
*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#ifdef COMPILE_PROKEE_MODULE
#ifndef COMPILE_PROKEE_MODULE_NO_STRCONV
#define PROKEE_USE_WRAPPER
#include "strconv/v01/module.h"
#else
#include "strconv/strconv.h"
#endif
#else
#include "strconv/strconv.h"
#endif
//------------------------------------------------------------------------------

#include <stdio.h>
#include <windows.h>

class osexe
{
public:
    static int myShellExecute(HWND hwnd,const char *action,const char *filename,const char *parameter,const char *workingDirectory,int show)
    {
        int retv=0;
        wchar_t *w_action=0;
        wchar_t *w_filename=0;
        wchar_t *w_parameter=0;
        wchar_t *w_workingDirectory=0;
        strconv::to_wcs(&w_action,0,action);
        strconv::to_wcs(&w_filename,0,filename);
        strconv::to_wcs(&w_parameter,0,parameter);
        strconv::to_wcs(&w_workingDirectory,0,workingDirectory);
        if(w_action && w_filename && w_parameter && w_workingDirectory)
        {
            retv=(long long)ShellExecuteW(hwnd,w_action,w_filename,w_parameter,w_workingDirectory,show);
        }
        if(w_action)free(w_action);
        if(w_filename)free(w_filename);
        if(w_parameter)free(w_parameter);
        if(w_workingDirectory)free(w_workingDirectory);
        return retv;
    }
    static int myShellExecute(HWND hwnd,const wchar_t *action,const wchar_t *filename,const wchar_t *parameter,const wchar_t *workingDirectory,int show)
    {
        return (long long)ShellExecuteW(hwnd,action,filename,parameter,workingDirectory,show);
    }
};

#endif
