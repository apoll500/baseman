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
//../../../csv/import/prokee.h

#ifndef csv_import_prokee
#define csv_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



class Reader;

class CsvData;
class CsvRecord;
class CsvField;
class CsvSettings;

#ifdef COMPILE_PROKEE_MODULE

//#include "../../interface/prokee/csv/inc/interface/import/all.fw"
//#include "../../interface/prokee/csv/inc/wrapper/import/all.fw"
#include "csv/v01/interface/import/all.fw"
#include "csv/v01/wrapper/import/all.fw"

#include "file/v01/module.h"
#include "reader/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_csv

//Local classes


//Interface declarations of this module
#include "csv/csv.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "csv/csv.hh"

//Interface declarations of other required modules
#include "file/file.hh"
#include "reader/reader.hh"
#include "strconv/strconv.hh"


#endif
#endif
