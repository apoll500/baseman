/*******************************************************************************
*                                                                              *
*  modules.h                                                                   *
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
//../../../baseman/import/modules.h

#ifndef baseman_import_modules
#define baseman_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "bmsetup/bmsetup.h"
#include "bmfragments/bmfragments.h"
#include "csv/csv.h"
#include "settings/settings.h"
#include "reader/reader.h"
#include "file/file.h"
#include "dir/dir.h"
#include "path/path.h"
#include "strman/strman.h"
#include "str/str.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "baseman/baseman.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "bmsetup/bmsetup.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "bmfragments/bmfragments.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "csv/csv.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "settings/settings.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "reader/reader.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "dir/dir.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "path/path.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strman/strman.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "str/str.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_baseman

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "baseman/baseman.hh2"
#endif

#endif

#endif
