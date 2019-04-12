/*******************************************************************************
*                                                                              *
*  bmsetup.h                                                                   *
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
//bmsetup/code/v01/files/source/bmsetup/bmsetup.h

#ifndef MOD_bmsetup_H
#define MOD_bmsetup_H

#include "bmsetup/import/prokee.h"

#define BMSETUP_INSTALLATION_PATH "/usr/local/bin/"
#define BMSETUP_BASELIST_PATH ".baseman/baselist.csv"

int run_script(const char *baseman_project_path,const char *package_path,const char *run_token);

int download(const char *baseman_project_path,const char *package_path,bool update);

int exporter();
int exporter2(const char *baseman_project_path);
int export_projects(const char *csvpath);
int export_versions(const char *csvpath);

int importer();
int importer2(const char *baseman_project_path);
int import_info(const char *infopath);

int publish(const char *baseman_project_path,const char *publish_path,bool dotar);
int install(const char *baseman_project_path,const char *package_path,bool dotar);

char **select_all_paths(const char *baseman_project_path,char **base_path,char **project_path,char **version_path);
char *construct_package_path(const char *baseman_project_path,const char *package_path,const char *append);

char *select_base_path(const char *base_name);
char *select_project_path(char *base_path,char **loc,int *pos);
char *select_version_path(char *project_path,char **loc,int *pos);

#include "bmsetup/import/modules.h"

#endif
