/*******************************************************************************
*                                                                              *
*  osexe_lin.h                                                                 *
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
#ifndef H_WWRAP_EXE_LIN
#define H_WWRAP_EXE_LIN

#include <stdio.h>
#include <string>
#include <string.h>

class osexe
{
public:
    static int myShellExecute(void *,const char *action,const char *filename,const char *,const char *,int)
    {
        std::string a;
        /*
        a=a+"xdg-open "+filename+" &";
        printf("> %s\n",a.c_str());
        system(a.c_str());
        */
        if(strman::isprefix("http://",filename) || strman::isprefix("https://",filename))
        {
            if(strcmp(action,"open")==0)
            {
                a=ini->get("main","browser");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
        }
        else
        {
            if(strcmp(action,"open")==0)
            {
                a=ini->get("main","fileman");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
            else if(strcmp(action,"edit")==0)
            {
                a=ini->get("main","editor");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
        }
        return 0;
    }
};

#endif
