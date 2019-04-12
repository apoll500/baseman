/*******************************************************************************
*                                                                              *
*  ReaderImpl.cpp                                                              *
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
#include "ReaderImpl.hpp"

ReaderImpl::ReaderImpl()
{
    ahead=0;
    currline=1;
    currcolumn=0;
    charType=0;
    lastError=0;
    lastErrorDetail=0;
    line_break_char='\n';
    compatibility_mode=READER_COMPMODE_STD;
    lastline=-1;
    lastcolumn=-1;
}
int ReaderImpl::get()
{
    if(ahead!=-1 && getNext())
    {
        if(charType==0)
        {
            //if(currentChar=='\n')return line_break_char;
            return currentChar;
        }
        return line_break_char;
    }
    else
    {
        return -1;
    }
}
int ReaderImpl::getChar()
{
    if(getNextChar())return currentChar;
    return -1;
}
int ReaderImpl::getNext()
{
    int n=1;
    moveCursorPos();
    if(ahead==0)
    {
        n=getNextChar();
    }
    if(n)
    {
        getNext_ahead();
    }
    else
    {
        charType=-1;
    }
    return n;
}
void ReaderImpl::getNext_ahead()
{
    int n;

    if((currentChar=='\n' || currentChar==0x0a00 || currentChar==0x0a000000) && compatibility_mode==READER_COMPMODE_OFF)
    {
        charType=1;
        n=getNextChar();
        if(n && (currentChar=='\r' || currentChar==0x0d00 || currentChar==0x0d000000))
        {
            ahead=0;
        }
        else if(n)
        {
            ahead=1;
        }
        else
        {
            ahead=-1;
        }
    }
    else if((currentChar=='\r' || currentChar==0x0d00 || currentChar==0x0d000000) && compatibility_mode!=READER_COMPMODE_EXT)
    {
        charType=1;
        n=getNextChar();
        if(n && (currentChar=='\n' || currentChar==0x0a00 || currentChar==0x0a000000))
        {
            ahead=0;
        }
        else if(n)
        {
            ahead=1;
        }
        else
        {
            ahead=-1;
        }
    }
    else
    {
        ahead=0;
        charType=0;
        if((currentChar=='\n' || currentChar==0x0a00 || currentChar==0x0a000000) || (currentChar=='\r' || currentChar==0x0d00 || currentChar==0x0d000000))
        {
            charType=1;
        }
    }
}
int ReaderImpl::getLastError()
{
    return lastError;
}
int ReaderImpl::getLastErrorDetail()
{
    return lastErrorDetail;
}
void ReaderImpl::resetLastError()
{
    lastError=0;
    lastErrorDetail=0;
}
void ReaderImpl::moveCursorPos()
{
    lastline=currline;
    lastcolumn=currcolumn;

    currcolumn++;
    if(charType!=0)
    {
        currline++;
        currcolumn=1;
    }
}
int ReaderImpl::getCurrLine()
{
    return currline;
}
int ReaderImpl::getCurrColumn()
{
    return currcolumn;
}
void ReaderImpl::setCurrLine(int n)
{
    currline=n;
}
void ReaderImpl::setCurrColumn(int n)
{
    currcolumn=n;
}
/**bmc
DEF getLine:ABSTRACT_METHOD
{
    function="@this.parent.NAME";
    brief="Gibt die Zeilennummer der Position des zuletzt eingelesenen Zeichens zurück.";
    return:i="Die Zeilennummer des zuletzt eingelesenen Zeichens. (Zählung beginnt mit 1.)";
}
DEF _getLine:getLine,Reader,IMETHOD
{
    Reader="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        Reader_INTERFACE;
    }
}
DEF x:METHOD,getLine
{
    UniFileReader="TRUE";
    class="UniFileReader";
}
DEF x:METHOD,getLine
{
    WcsReader="TRUE";
    class="WcsReader";
}
DEF x:METHOD,getLine
{
    FileReader="TRUE";
    class="FileReader";
}
DEF x:METHOD,getLine
{
    WcsFileReader="TRUE";
    class="WcsFileReader";
}
DEF x:METHOD,getLine
{
    Char16FileReader="TRUE";
    class="Char16FileReader";
}
DEF x:METHOD,getLine
{
    Char32FileReader="TRUE";
    class="Char32FileReader";
}
*/
int ReaderImpl::getLine()
{
    return lastline;
}
/**bmc
DEF getColumn:ABSTRACT_METHOD
{
    function="@this.parent.NAME";
    brief="Gibt die Spaltennummer der Position des zuletzt eingelesenen Zeichens zurück.";
    return:i="Die Spaltennummer des zuletzt eingelesenen Zeichens. (Zählung beginnt mit 1.)";
}
DEF _getColumn:getColumn,Reader,IMETHOD
{
    Reader="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        Reader_INTERFACE;
    }
}
DEF x:METHOD,getColumn
{
    UniFileReader="TRUE";
    class="UniFileReader";
}
DEF x:METHOD,getColumn
{
    WcsReader="TRUE";
    class="WcsReader";
}
DEF x:METHOD,getColumn
{
    FileReader="TRUE";
    class="FileReader";
}
DEF x:METHOD,getColumn
{
    WcsFileReader="TRUE";
    class="WcsFileReader";
}
DEF x:METHOD,getColumn
{
    Char16FileReader="TRUE";
    class="Char16FileReader";
}
DEF x:METHOD,getColumn
{
    Char32FileReader="TRUE";
    class="Char32FileReader";
}
*/
int ReaderImpl::getColumn()
{
    return lastcolumn;
}

