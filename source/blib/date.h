/*******************************************************************************
*                                                                              *
*  date.h                                                                      *
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
#ifndef H_BLIB_DATE
#define H_BLIB_DATE
#include "wwrap/osio.h"
#include "wwrap/str.h"
#include <stdlib.h>
#include <time.h>
class date
{
public:
    template<class T> static T *get_bdn(T *str);
};
template<class T> T *date::get_bdn(T *str)
{
    const time_t t=time(0);
    struct tm *ti=gmtime(&t);
    osio::sprint(str,"%d",ti->tm_year+1900);
    int mon=ti->tm_mon+1;
    if(mon<10)str::cat(str,"0");
    osio::sprint(&str[str::len(str)],"%d",mon);
    int day=ti->tm_mday;
    if(day<10)str::cat(str,"0");
    osio::sprint(&str[str::len(str)],"%d",day);
    str::cat(str,"_");
    osio::sprint(&str[str::len(str)],"%lu",t);
    return str;
}
#endif
