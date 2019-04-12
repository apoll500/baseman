/*******************************************************************************
*                                                                              *
*  main.cpp                                                                    *
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
//bmsetup/cli/v01/files/source/bmsetup/cli/main.cpp

#include <stdio.h>
#include <stdlib.h>

#include "../bmsetup.h"

#define BMSETUP_USAGE "\n\
usage: bmsetup <command>[ [<target> ]<path>]\n\
\n\
If <path> is given, it has to specify a valid path within baseman.\n\
F.e: 'prokee/mods/bmsetup/full/v01'. This path may differ from the\n\
path within the file system. As <command> use one of the following:\n\
\n\
download [<target> ]<path>\n\
    Downloads the package specified by <path> and stores it to\n\
    ./baseman/packages/ or to the path given by <target>.\n\
    Previously downloaded package files for package <path> are\n\
    deleted bevore attempting to re-download them. The update\n\
    command can be used to upgrade packages to a newer version.\n\
\n\
install [<target> ]<path>:\n\
    Installs the package specified by <path> within baseman.\n\
    If the package is missing, bmsetup will try to download it.\n\
    Downloaded packeges are stored at ./baseman/packages/ or\n\
    at the path given by <target>.\n\
\n\
import-cfg [<path>]:\n\
    Updates projects.csv and versions.csv files from *.info files.\n\
    If no <path> is given, the program will search within the\n\
    current working directory and all subdirectories.\n\
\n\
export-cfg [<path>]:\n\
    Generates *.info files from projects.csv and versions.csv files.\n\
    If no <path> is given, the program will search within the\n\
    current working directory and all subdirectories.\n\
\n\
publish [<target> ]<path>:\n\
    Generates a package.\n\
\n\
push [<target> ]<path>:\n\
    Copies package files to a target directory.\n\
\n\
pull [<target> ]<path>:\n\
    Copies package files from a target directory.\n\
\n\
help:\n\
    Displays this information.\n\
\n"

void print_usage()
{
    printf(BMSETUP_USAGE);
}

void check_basemanpath_parameter(char *path)
{
    if(path[strlen(path)-1]=='/')path[strlen(path)-1]=0;
    if(path[0]=='@' && path[1] && path[2]==':' && path[3]=='/')
    {
        int i=4;
        while(path[i])
        {
            path[i-4]=path[i];
            i++;
        }
        path[i-4]=0;
    }
}

void print_error_line(const char *msg)
{
    bool instr=true;
    for(int i=0;i<60;i++)
    {
        int r=130+i*2;
        int g=i*2;
        int b=i;
        printf("%c[%d;2;%d;%d;%dm",27,38,r,r,r);
        printf("%c[%d;2;%d;%d;%dm",27,48,r,g,b);
        if(i-2>=0 && msg[i-2]==0)
        {
            instr=false;
        }
        if(i-2>=0 && instr)
        {
            printf("%c",msg[i-2]);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}

void print_error(const char *msg)
{
    print_error_line("");
    print_error_line("");
    printf("%c[%dA",27,1);
    print_error_line(msg);
    print_error_line("");
    printf("%c[%dD",27,2);
    printf("%c[%dm",27,0);
    printf("Use 'bmsetup help' for more information.\n");
}

int main(int argc,char **argv)
{
    if(argc==1)
    {
        //no command
        print_error("--- no command given ---");
    }
    else if(argc==2)
    {
        //param 1: command
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"import-cfg")==0)
        {
            importer();
        }
        else if(strcmp(argv[1],"export-cfg")==0)
        {
            exporter();
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"check")==0)
        {
            print_error("--- not jet implemented ---");
        }
        else if(strcmp(argv[1],"help")==0)
        {
            print_usage();
        }
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else if(argc==3)
    {
        //param 1: command
        //param 2: path
        //----------------------------------------------------------------------
        check_basemanpath_parameter(argv[2]);
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"download")==0)
        {
            if(download(argv[2],".baseman/packages/",true)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
        }
        else if(strcmp(argv[1],"install")==0)
        {
            if(download(argv[2],".baseman/packages/",false)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
            else install(argv[2],".baseman/packages/",true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"publish")==0)
        {
            publish(argv[2],"packages/",true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"pull")==0)
        {
            install(argv[2],"packages/",false);
        }
        else if(strcmp(argv[1],"push")==0)
        {
            publish(argv[2],"packages/",false);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"import-cfg")==0)
        {
            importer2(argv[2]);
        }
        else if(strcmp(argv[1],"export-cfg")==0)
        {
            exporter2(argv[2]);
        }
        //----------------------------------------------------------------------
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else if(argc==4)
    {
        //param 1: command
        //param 2: target
        //param 3: path
        //----------------------------------------------------------------------
        check_basemanpath_parameter(argv[3]);
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"download")==0)
        {
            if(download(argv[3],argv[2],true)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
        }
        else if(strcmp(argv[1],"install")==0)
        {
            if(download(argv[3],argv[2],false)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
            else install(argv[3],argv[2],true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"publish")==0)
        {
            publish(argv[3],argv[2],true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"pull")==0)
        {
            install(argv[3],argv[2],false);
        }
        else if(strcmp(argv[1],"push")==0)
        {
            publish(argv[3],argv[2],false);
        }
        //----------------------------------------------------------------------
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else
    {
        //wrong command line parameter
        print_error("--- wrong command line parameter ---");
    }

    return EXIT_SUCCESS;
}
