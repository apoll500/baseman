/*******************************************************************************
*                                                                              *
*  csv.h                                                                       *
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
//csv/code/v01/files/source/csv/csv.h

#ifndef MOD_csv_H
#define MOD_csv_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "csv/import/prokee.h"
//#include "csv.fw"

class csv
{
public:
    static int record_count(AbsCsvRecord **a);
};

#include "csv.hh"

#include "CsvRecord.h"
#include "CsvData.h"
#include "CsvField.h"
#include "CsvSettings.h"

#include "csv/import/modules.h"

#include "csv.hh2"

int cmpi(const void *a,const void *b);
int iln(int *row);

template<class T> int aln(const T **a)
{
    int i=0;
    while(a[i]!=0)i++;
    return i;
}
template<class T> int lln(const T *a)
{
    int i=0;
    while(a[i]!=0)i++;
    return i;
}

#endif
