/*******************************************************************************
*                                                                              *
*  macros.h                                                                    *
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
//#include <stdlib.h>

//------------------------------------------------------------------------------
// For specifying the target os, define one of the following:
//    OS_LIN ... Linux
//    OS_WIN ... Windows
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Using wide characters
//------------------------------------------------------------------------------
#ifdef OS_WIN
#define OS_WIN_WCS
#define UNICODE
#define _UNICODE
#endif

/*******************************************************************************
*  Common macros used for specifying operating systems:                        *
*  __linux__    Linux                                                          *
*  __sun        Solaris                                                        *
*  __FreeBSD__  FreeBSD                                                        *
*  __NetBSD__   NetBSD                                                         *
*  __OpenBSD__  OpenBSD                                                        *
*  __APPLE__    Mac OS X                                                       *
*  __hpux       HP-UX                                                          *
*  __osf__      Tru64 UNIX / DEC OSF1                                          *
*  __sgi        Irix                                                           *
*  _AIX         AIX                                                            *
*  _WIN32                                                                      *
*  _WIN64                                                                      *
*******************************************************************************/

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#ifdef OS_WIN
//#ifdef __cplusplus
#define DLL extern "C"
// __declspec(dllexport)
#else
#define DLL extern "C"
#endif

#if __cplusplus < 201103L
#define CPP11
#endif

//------------------------------------------------------------------------------
#ifdef OS_LIN
#define SW_SHOW 5
#endif
//------------------------------------------------------------------------------

