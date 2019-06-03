/*******************************************************************************
*                                                                              *
*  BmCopyControl.h                                                             *
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
#ifndef BASEMAN_BmCondCopyControl_H
#define BASEMAN_BmCondCopyControl_H

class Bm;

#ifndef COMPILE_PROKEE_MODULE
#include "file/file.h"
#endif

#include "../baseman.h"

#include "wwrap/osio.h"

#include <vector>
#include <string>

/** CondCopyControl implementation required for class Bm.

*/
template<class T> class BmCondCopyControl:public CondCopyControl<T>
{
protected:
    Bm *bm;
private:
    int error;
    std::vector<std::string> base_path;
    int base_path_index;
public:
    BmCondCopyControl()
    {
        error=0;
    }
    virtual ~BmCondCopyControl()
    {
        //base_path_index=0;
    }
    virtual void setBm(Bm *b);
    virtual void setError(int r);
    virtual int getError();
    virtual std::string get_base_path();
    virtual std::string get_next_base_path();
    virtual int get_base_path_count();
    virtual bool ignoreEmptyDir(const T *path);
    virtual void feedback();
    virtual size_t feedback_bytes();
    virtual time_t feedback_time();
};

#include "../bm/bm.h"

template<class T> void BmCondCopyControl<T>::setBm(Bm *b)
{
    bm=b;
    base_path.push_back(bm->basepath());
}

template<class T> void BmCondCopyControl<T>::setError(int e)
{
    error=e;
}

template<class T> int BmCondCopyControl<T>::getError()
{
    return error;
}

template<class T> std::string BmCondCopyControl<T>::get_base_path()
{
    return base_path[base_path.size()-1];
}

template<class T> std::string BmCondCopyControl<T>::get_next_base_path()
{
    base_path_index++;
    base_path_index%=base_path.size();
    return base_path[base_path_index];
}

template<class T> int BmCondCopyControl<T>::get_base_path_count()
{
    return base_path.size();
}

template<class T> bool BmCondCopyControl<T>::ignoreEmptyDir(const T *)//path)
{
    return false;
}

template<class T> void BmCondCopyControl<T>::feedback()
{
    osio::xprint(".");
}

template<class T> size_t BmCondCopyControl<T>::feedback_bytes()
{
    return 1000000;
}

template<class T> time_t BmCondCopyControl<T>::feedback_time()
{
    return 0;
}

#endif
