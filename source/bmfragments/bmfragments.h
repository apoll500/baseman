/*******************************************************************************
*                                                                              *
*  bmfragments.h                                                               *
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
//bmfragments/code/v01/files/source/bmfragments/bmfragments.h

#ifndef MOD_bmfragments_H
#define MOD_bmfragments_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

#include "macros/macros.h"
#include "wwrap/osio.h"

#define BMFRAGMENTS_FRAGMENT_TYPE_UNDEFINED 0
#define BMFRAGMENTS_FRAGMENT_TYPE_CODE 1
#define BMFRAGMENTS_FRAGMENT_TYPE_FRAGMENT 2

#define BMFRAGMENTS_CHKST_UNKNOWN 0
#define BMFRAGMENTS_CHKST_UNCHANGED_FRAGMENT 1
#define BMFRAGMENTS_CHKST_CHANGED_FRAGMENT 2
#define BMFRAGMENTS_CHKST_CODE 3
#define BMFRAGMENTS_CHKST_ERROR_HEADER 4
#define BMFRAGMENTS_CHKST_ERROR_FOOTER 5

#define BMFRAGMENTS_TYPE_UNDEFINED 0
#define BMFRAGMENTS_TYPE_INCLUDE 1
#define BMFRAGMENTS_TYPE_NORMAL 2
#define BMFRAGMENTS_TYPE_REMOVE 3

#define BMFRAGMENTS_FILE_SOURCE 0
#define BMFRAGMENTS_FILE_TARGET 1

#define FRAGMENTS_ACTION_DONOTHING 0
#define FRAGMENTS_ACTION_EXPORT 1
#define FRAGMENTS_ACTION_IMPORT 2
#define FRAGMENTS_ACTION_MERGE 3

#define bmfragments_startup startup
#define bmfragments_cleanup cleanup
#define bmfragments_prepare_fragments prepare_fragments
#define bmfragments_handle_fragments handle_fragments

#include "bmfragments/import/prokee.h"

DLL int startup();
DLL int cleanup();
DLL int handle_fragments(void *cc);
DLL int prepare_fragments(const char *source_filename,const char *target_filename,int fragment_task_action,int baseman_copy_case);

class bmfragments
{
public:
    static int main(int argc,char **argv);
};

#include "bmfragments/import/modules.h"

#endif
