/*******************************************************************************
*                                                                              *
*  bmsetup.h                                                                   *
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
#ifndef MOD_bmsetup_H
#define MOD_bmsetup_H
#include "macros/macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bmsetup_download download
#define bmsetup_download2 download2
#define bmsetup_install install
#define bmsetup_get_all_paths get_all_paths
//#include "wwrap/str.h"
DLL int run_script(const char *baseman_project_path,const char *package_path,const char *run_token);
DLL int run_script2(const char *baseman_project_path,const char *package_path,const char *run_token,const char *username,const char *userpass);
DLL int download(const char *baseman_project_path,const char *package_path,bool update);
DLL int download2(const char *baseman_project_path,const char *package_path,bool update,const char *username,const char *userpass);
DLL int exporter();
DLL int exporter2(const char *baseman_project_path);
DLL int export_projects(const char *csvpath);
DLL int export_versions(const char *csvpath);
DLL int importer();
DLL int importer2(const char *baseman_project_path);
DLL int import_info(const char *infopath);
DLL int publish(const char *baseman_project_path,const char *publish_path,bool dotar);
DLL int install(const char *baseman_project_path,const char *package_path,bool dotar);
DLL char **get_all_paths(const char *baseman_project_path,char **base_path,char **project_path,char **version_path);
DLL char *construct_package_path(const char *baseman_project_path,const char *package_path,const char *append);
DLL char *get_base_path(const char *base_name);
DLL char *get_project_path(char *base_path,char **loc,int *pos);
DLL char *get_version_path(char *project_path,char **loc,int *pos);
#include "bmsetup/import/prokee.h"
#define BMSETUP_USAGE "The 'help' option is not implemented for Windows.\n\
See documentation in html format at file:\n\
system/docu/man/bmsetup.v01.html\n"
#define BMSETUP_INSTALLATION_PATH "/usr/local/bin/"
#define BMSETUP_BASELIST_PATH ".baseman/baselist.csv"
class bmsetup
{
public:
    static int main(int argc,char **argv);
    static void print_usage();
    static void patch_basemanpath_parameter(char *path);
    static void print_error_line(const char *msg);
    static void print_error(const char *msg);
};
#include "bmsetup/import/modules.h"
#endif
