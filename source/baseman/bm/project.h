/*******************************************************************************
*                                                                              *
*  project.h                                                                   *
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
#ifndef BASEMAN_PROJECT_H
#define BASEMAN_PROJECT_H

#include <string>

//#include "csv/CsvData.h"
//#include "settings/settings.h"
//#include "path/path.h"
//#include "strman/strman.h"

#include "../baseman.h"
#include "bm.h"

extern AbsMultiSettings *ini;

class Project:public Bm
{
private:
    std::string run;
public:
    Project(char **projects);
    Project(char **projects,std::string basename);
    Project();
    Project(std::string basename,std::string projectname);
    ~Project();
    void ini0(char **projects);
    void ini0(char **projects,std::string basename);
    void set_values(AbsCsvRecord *r);
    void info();
    virtual std::string getrun()
    {
        if(run=="")
        {
            if(parent)
            {
                return parent->getrun();
            }
            else
            {
                return "";
            }
        }
        else
        {
            return run;
        }
    }
};

#endif
