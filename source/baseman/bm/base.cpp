/*******************************************************************************
*                                                                              *
*  base.cpp                                                                    *
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
#include "base.h"

Base::Base():Bm()
{
    ini0(ini->get("base"));
}

Base::Base(std::string base):Bm()
{
    ini0(base);
}

Base::~Base()
{
    //
}

void Base::ini0(std::string base)
{
    error=0;
    target="";
    path="";
    desc="";
    fullpath="";

    plevelitem=0;
    parent=0;
    tabname=tabpath(BASEMAN_BASELISTPATH);
    flag=ini->get("group");
    if(flag=="")flag="1";
    key_name="name";
    key_value=base;

    load();
}

void Base::set_values(CsvRecord *r)
{
    char *path_cstr=r->getField(r->getTab()->getHeaderId("path"));
    char *target_cstr=r->getField(r->getTab()->getHeaderId("target"));
    char *description_cstr=r->getField(r->getTab()->getHeaderId("description"));

    if(path_cstr)path=path_cstr;
    else
    {
        path="";
        printf("ERROR: Base::set_values() path=0\n");
    }
    if(target_cstr)target=target_cstr;
    else
    {
        target="";
        printf("ERROR: Base::set_values() target=0\n");
    }
    if(description_cstr)desc=description_cstr;
    else
    {
        desc="";
        printf("ERROR: Base::set_values() desc=0\n");
    }

    fullpath=path;
}

void Base::info()
{
    osio::print("\nBase:\n----------------------------------------------------------------------\nname        = %s\npath        = %s\ntarget      = %s\ndescription = %s\n",key_value.c_str(),path.c_str(),target.c_str(),desc.c_str());
}
