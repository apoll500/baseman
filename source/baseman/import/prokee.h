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
//../../../baseman/import/prokee.h

#ifndef baseman_import_prokee
#define baseman_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



class Reader;

#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/baseman/inc/interface/import/all.fw"
#include "../../interface/prokee/baseman/inc/wrapper/import/all.fw"

#include "bmsetup/v01/module.h"
#include "csv/v01/module.h"
#include "settings/v01/module.h"
#include "reader/v01/module.h"
#include "file/v01/module.h"
#include "dir/v01/module.h"
#include "path/v01/module.h"
#include "strman/v01/module.h"
#include "str/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_baseman

//Local classes


//Interface declarations of this module
#include "baseman/baseman.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "baseman/baseman.hh"

//Interface declarations of other required modules
#include "bmsetup/bmsetup.hh"
#include "csv/csv.hh"
#include "settings/settings.hh"
#include "reader/reader.hh"
#include "file/file.hh"
#include "dir/dir.hh"
#include "path/path.hh"
#include "strman/strman.hh"
#include "str/str.hh"
#include "strconv/strconv.hh"


#endif
#endif
