/*******************************************************************************
*                                                                              *
*  runclp.h                                                                    *
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
#ifndef BASEMAN_RUNCLP_H
#define BASEMAN_RUNCLP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseman/baseman.h"
#include "../controllers/MergeControler.h"
#include "licenses/license_GPL3.h"
#define BASEMAN_ABOUT "\
baseman  Copyright (C) 2016-2019  Andreas Pollhammer\n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
This is free software, and you are welcome to \n\
redistribute it under certain conditions.\n\
\n\
This software is licensed under GPL Version 3.\n\
Type 'license' for the full text of the GPLv3.\n\
\n\
Please read baseman_docu.pdf on how to use this\n\
software. Or type 'docu' to open this file.\n\
\n\
"
void runargs(int argc,char **argv);
void imode(void);
int cli_main(int argc,char **argv);
void runargs_delete_log(int argc,char **);
void runargs_clear(int argc,char **argv);
void runargs_goup(int argc,char **argv);
void runargs_list(int argc,char **argv);
void runargs_simu(int argc,char **argv);
void runargs_export(int argc,char **argv);

void runargs_package(int argc,char **argv);
void runargs_merge(int argc,char **argv);
void runargs_import(int argc,char **argv);
void runargs_remove(int argc,char **argv);
void runargs_import_p(int argc,char **argv);
void runargs_clean(int argc,char **argv);
void runargs_snapshot(int argc,char **argv);
void runargs_update(int argc,char **argv);
void runargs_diff(int argc,char **argv);
void runargs_run(int argc,char **argv);
void runargs_base(int argc,char **argv);
void runargs_project(int argc,char **argv);
void runargs_version(int argc,char **argv);
void runargs_info(int argc,char **argv);
void runargs_path(int argc,char **argv);
void runargs_open(int argc,char **argv);
void runargs_setgroup(int argc,char **argv);
bool select_element(Bm *p,const char *arg);
void select_line(Bm *p,const char *arg);
bool select_element_project(Bm *p,const char *arg);
bool select_element_version(Bm *p,const char *arg);
void select_project_line(Bm *p,const char *arg);
void select_version_line(Bm *p,const char *arg);
bool select_full_path(const char *path,bool (*selector_function)(Bm *,const char *));
bool select_path(const char *path,bool (*selector_function)(Bm *,const char *));
void runargs_select(int argc,char **argv);
void runargs_set(int argc,char **argv);
void runargs_setiniblock(int argc,char **argv);
void runargs_add_intro(int argc,char **argv);
void runargs_create(int argc,char **argv);
#endif
