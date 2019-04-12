/*******************************************************************************
*                                                                              *
*  FileReader.hpp                                                              *
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
#ifndef FileReader_HPP
#define FileReader_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <uchar.h>

#include "macros/macros.h"
#include "ReaderImpl.hpp"

class FileReader:public ReaderImpl
{
protected:
    FILE *f;
    bool file_opened_here;
public:
    FileReader(){printf("??? ---> FileReader()\n");}
    FileReader(FILE *file);
    FileReader(const char *a);
    FileReader(const wchar_t *a);
    virtual ~FileReader();
    virtual int getNextChar();
};

class WcsFileReader:public ReaderImpl
{
protected:
    FILE *f;
    bool file_opened_here;
public:
    WcsFileReader(FILE *file);
    WcsFileReader(const char *a);
    WcsFileReader(const wchar_t *a);
    virtual ~WcsFileReader();
    virtual int getNextChar();
};

class Char16FileReader:public FileReader
{
public:
    Char16FileReader(FILE *file):FileReader(file){}
    Char16FileReader(const char *a):FileReader(a){}
    Char16FileReader(const wchar_t *a):FileReader(a){}
    virtual ~Char16FileReader(){}
    virtual int getNextChar();
};

class Char32FileReader:public FileReader
{
public:
    Char32FileReader(FILE *file):FileReader(file){}
    Char32FileReader(const char *a):FileReader(a){}
    Char32FileReader(const wchar_t *a):FileReader(a){}
    virtual ~Char32FileReader(){}
    virtual int getNextChar();
};

#include "h3_AbsUniFileReader.h"
class UniFileReader:virtual public FileReader,public AbsUniFileReader3
{
protected:
    int char_size;
public:
    UniFileReader(FILE *file,int csize);
    UniFileReader(const char *a,int csize);
    UniFileReader(const wchar_t *a,int csize);
    virtual ~UniFileReader(){}
    virtual int getNextChar();
    virtual int getCharSize();
    virtual void setCharSize(int csize);
};

#endif
