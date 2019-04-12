/*******************************************************************************
*                                                                              *
*  h3_AbsUniFileReader.h                                                       *
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
//------------------------------------------------------------------------------
//AbsUniFileReader_INTERFACE
//------------------------------------------------------------------------------
#include <uchar.h>

class AbsUniFileReader3:virtual public FileReader,virtual public AbsUniFileReader2
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsUniFileReader3(){}
    //SUPERCLASS METHOD WRAPPER ----------------------------------------
    
    int getLine(){return FileReader::getLine();}
    
    
    int getColumn(){return FileReader::getColumn();}
    
    
    int get(){return FileReader::get();}
    
    
    int getChar(){return FileReader::getChar();}
    
    
    int getLastError(){return FileReader::getLastError();}
    
    
    int getLastErrorDetail(){return FileReader::getLastErrorDetail();}
    
    
    void resetLastError(){FileReader::resetLastError();}
    
    
    int getCurrLine(){return FileReader::getCurrLine();}
    
    
    int getCurrColumn(){return FileReader::getCurrColumn();}
    
    
    void setCurrLine(int n){FileReader::setCurrLine(n);}
    
    
    void setCurrColumn(int n){FileReader::setCurrColumn(n);}
    
};

