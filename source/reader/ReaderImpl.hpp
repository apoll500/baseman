/*******************************************************************************
*                                                                              *
*  ReaderImpl.hpp                                                              *
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
#ifndef Reader_HPP
#define Reader_HPP

#include "ReaderImpl.h"

#include "h3_Reader.h"
class ReaderImpl:public Reader3
{
protected:
    int ahead;
    int currentChar;
    int charType;
    int lastError;
    int lastErrorDetail;
    int lastline;
    int lastcolumn;
public:
    ReaderImpl();
    virtual ~ReaderImpl(){};
    int get();
    int getChar();
    int getLastError();
    int getLastErrorDetail();
    void resetLastError();
    int getCurrLine();
    int getCurrColumn();
    void setCurrLine(int n);
    void setCurrColumn(int n);
    int getLine();
    int getColumn();
public:
    int getNext();
    void getNext_ahead();
    void moveCursorPos();
public:
    virtual int getNextChar()=0;
    //virtual int getNextChar(){return 1;}
    //--------------------------------------------------------------------------
    // DUMMY METHODS
    // This methods have to be added here, to be included in the symbol table.
    // Do not call this methods. These are only placeholders.
    //--------------------------------------------------------------------------
    //virtual int getCharSize(){return 0;}
    //virtual void setCharSize(int){}
 };

#endif
