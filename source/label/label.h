/*******************************************************************************
*                                                                              *
*  label.h                                                                     *
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
#ifndef MOD_label_H
#define MOD_label_H
#ifdef OS_WIN
#include<direct.h>
#endif
#ifdef OS_LIN
#include <stdlib.h>
#endif
#include "label/import/prokee.h"
class label
{
public:
    
    template<class T> static bool testlabel(const T *path);
    
};
#include "label/import/modules.h"
#ifdef OS_WIN
template<class T> bool label::testlabel(const T *path)
{
    if(path[0]>64 && path[0]<91 && path[1]==':')
    {
        unsigned long d=_getdrives();
        return d & (1<<(path[0]-65));
    }
    return false;
}
#endif
#ifdef OS_LIN
template<class T> bool label::testlabel(const T *)
{
    return false;
}
#endif
#endif
