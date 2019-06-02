/*******************************************************************************
*                                                                              *
*  version.cpp                                                                 *
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
#include "version.h"

#include "project.h"
#include "base.h"

Version::Version(char **versions):Bm()
{
    ini0(versions);
}

Version::Version(char **versions,std::string basename,std::string projectname):Bm()
{
    ini0(versions,basename,projectname);
}

Version::Version():Bm()
{
    std::string temp_string=ini->get("version");
    char **versions=strman::explode("/",temp_string.c_str());
    ini0(versions);
    strman::explode_free(versions);
}

Version::Version(std::string basename,std::string projectname,std::string versionname):Bm()
{
    char **versions=strman::explode("/",versionname.c_str());
    ini0(versions,basename,projectname);
    strman::explode_free(versions);
}

Version::~Version()
{
    delete plevelitem;
}

void Version::ini0(char **versions)
{
    ini0(versions,ini->get("base"),ini->get("project"));
}

void Version::ini0(char **versions,std::string basename,std::string projectname)
{
    error=0;
    target="";
    path="";
    desc="";
    date="";
    fullpath="";

    int ln=strman::explode_count(versions);
    key_value=versions[ln-1];
    if(ln>1)
    {
        versions[ln-1]=0;
        parent=new Version(versions,basename,projectname);
        plevelitem=0;
    }
    else
    {
        parent=0;
        if(projectname!="")
        {
            plevelitem=new Project(basename,projectname);
        }
        else
        {
            plevelitem=new Base(basename);
        }
    }
    tabname=tabpath("versions.csv");
    flag="1";
    key_name="version";

    load();
}

void Version::set_values(AbsCsvRecord *r)
{
    target="";

    char *path_cstr=r->getField(r->getTab()->getHeaderId("path"));
    char *description_cstr=r->getField(r->getTab()->getHeaderId("description"));
    char *date_cstr=r->getField(r->getTab()->getHeaderId("date"));

    if(path_cstr)path=path_cstr;
    else
    {
        path="";
        osio::xprint("ERROR: Version::set_values() path=0\n");
    }
    if(description_cstr)desc=description_cstr;
    else
    {
        desc="";
        osio::xprint("ERROR: Version::set_values() desc=0\n");
    }
    if(date_cstr)date=date_cstr;
    else
    {
        date="";
        osio::xprint("ERROR: Version::set_values() date=0\n");
    }

    fullpath=abspath();
}

void Version::info()
{
    if(parent)
    {
        parent->info();
        osio::xprint("\nSub-Version:");
    }
    else
    {
        plevelitem->info();
        osio::xprint("\nVersion:");
    }
    osio::xprint("\n----------------------------------------------------------------------\nversion     = %s\npath        = %s\ndate        = %s\ndescription = %s\n",key_value.c_str(),path.c_str(),date.c_str(),desc.c_str());
}
