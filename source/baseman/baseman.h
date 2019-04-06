/*******************************************************************************
*                                                                              *
*  baseman.h                                                                   *
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
#ifndef MOD_baseman_H
#define MOD_baseman_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string>

void print_location(void);

void create_base0(const char *base,const char *path);
void create_base(const char *base,const char *path,const char *group);

void list_selected_group(void);
void list_group(const char *group);

void reset(void);
void select_group(const char *group);
void select_base(const char *base);
void select_project(const char *project);
void select_version(const char *version);
void unselect_base(void);
void unselect_project(void);
void unselect_version(void);
void print_level(void);

void create_baselist(void);
void open_baselist(void);

std::string get_baselist_path();
std::string get_statusini_path();

#include "csv/csv.h"
#include "settings/settings.h"

class Bm;

Bm *bmObject(void);

class MultiSettings;

extern MultiSettings *ini;

#include "csv/CsvData.h"
#include "csv/CsvRecord.h"
#include "csv/CsvField.h"

#endif
