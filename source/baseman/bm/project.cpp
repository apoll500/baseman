/*******************************************************************************
*                                                                              *
*  project.cpp                                                                 *
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
#include "project.h"

#include "base.h"

Project::Project(char **projects):Bm()
{
    ini0(projects);
}

Project::Project(char **projects,std::string basename):Bm()
{
    ini0(projects,basename);
}

Project::Project():Bm()
{
    std::string temp_string=ini->get("project");
    char **projects=strman::explode("/",temp_string.c_str());
    ini0(projects);
    strman::explode_free(projects);
}

Project::Project(std::string basename,std::string projectname):Bm()
{
    char **projects=strman::explode("/",projectname.c_str());
    ini0(projects,basename);
    strman::explode_free(projects);
}

Project::~Project()
{
    delete plevelitem;
}

void Project::ini0(char **projects)
{
    ini0(projects,ini->get("base"));
}

void Project::ini0(char **projects,std::string basename)
{
    error=0;
    target="";
    path="";
    desc="";
    run="";
    fullpath="";

    int ln=strman::explode_count(projects);
    key_value=projects[ln-1];
    if(ln>1)
    {
        projects[ln-1]=0;
        parent=new Project(projects,basename);
        plevelitem=0;
    }
    else
    {
        parent=0;
        plevelitem=new Base(basename);
    }
    tabname=tabpath("projects.csv");
    flag="1";
    key_name="name";

    load();
}

void Project::set_values(AbsCsvRecord *r)
{
    char *path_cstr=r->getField(r->getTab()->getHeaderId("path"));
    char *target_cstr=r->getField(r->getTab()->getHeaderId("target"));
    char *description_cstr=r->getField(r->getTab()->getHeaderId("description"));
    char *run_cstr=r->getField(r->getTab()->getHeaderId("run"));

    if(path_cstr)path=path_cstr;
    else
    {
        path="";
        osio::xprint("ERROR: Project::set_values() path=0\n");
    }
    if(target_cstr)target=target_cstr;
    else
    {
        target="";
        osio::xprint("ERROR: Project::set_values() target=0\n");
    }
    if(description_cstr)desc=description_cstr;
    else
    {
        desc="";
        osio::xprint("ERROR: Project::set_values() desc=0\n");
    }
    if(run_cstr)run=run_cstr;
    else
    {
        run="";
        osio::xprint("ERROR: Project::set_values() run=0\n");
    }

    fullpath=abspath();
}

void Project::info()
{
    if(parent)
    {
        parent->info();
        osio::xprint("\nSub-Project:");
    }
    else
    {
        plevelitem->info();
        osio::xprint("\nProject:");
    }
    osio::xprint("\n----------------------------------------------------------------------\nname        = %s\npath        = %s\ntarget      = %s\nrun         = %s\ndescription = %s\n",key_value.c_str(),path.c_str(),target.c_str(),run.c_str(),desc.c_str());
}
