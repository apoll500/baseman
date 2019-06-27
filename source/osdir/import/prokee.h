/*******************************************************************************
*                                                                              *
*  prokee.h                                                                    *
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
//../../../osdir/import/prokee.h

#ifndef osdir_import_prokee
#define osdir_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



#include "macros/macros.h"

#ifdef OS_WIN
#ifdef OS_WIN_WCS

#include <windows.h>
#include <wchar.h>
#include <io.h>

struct myWIN32_FIND_DATA
{
    char *cFileName;
    unsigned int cFileName_ln;
    WIN32_FIND_DATAA dataA;
    WIN32_FIND_DATAW dataW;
};

#else

#include <windows.h>
#include <wchar.h>
#include <io.h>

#endif
#elif defined OS_LIN

#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <unistd.h>

struct myWIN32_FIND_DATA{};
struct WIN32_FIND_DATAW{};
typedef unsigned int HANDLE;

#endif

#ifdef COMPILE_PROKEE_MODULE

//#include "../../interface/prokee/osdir/inc/interface/import/all.fw"
//#include "../../interface/prokee/osdir/inc/wrapper/import/all.fw"
#include "osdir/v01/interface/import/all.fw"
#include "osdir/v01/wrapper/import/all.fw"

#include "str/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_osdir

//Local classes


//Interface declarations of this module
#include "osdir/osdir.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "osdir/osdir.hh"

//Interface declarations of other required modules
#include "str/str.hh"
#include "strconv/strconv.hh"


#endif
#endif
