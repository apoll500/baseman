/*******************************************************************************
*                                                                              *
*  StrReader.cpp                                                               *
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
#include "StrReader.hpp"

/**bmc
lp_input_str:ccp
{
    name="a";
    direction="IN";
    desc="Pointer auf den Speicherbereich der den einzulesenden Text enthält.";
    desc_en="Buffer which holds the text to be read.";
    test
    {
        test1
        {
            count="3";
            input="STRING('abc\ndef\ngh')";
            input="STRING('abc\rdef\rgh')";
            input="STRING('abc\r\ndef\r\ngh')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="abc\ndef\ngh";
                <-
            }
            testcode="@test1_testcode";
        }
        test2
        {
            count="3";
            input="STRING('\nabcdefgh\n')";
            input="STRING('\rabcdefgh\r')";
            input="STRING('\r\nabcdefgh\r\n')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="\nabcdefgh\n";
                <-
            }
            testcode="@test1_testcode";
        }
        test3
        {
            count="1";
            input="STRING('\n\rabc\n\rdefgh\n\r')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="\n\nabc\n\ndefgh\n\n";
                <-
            }
            testcode="@test1_testcode";
        }
        test4
        {
            count="1";
            input="STRING('\nabc\rdef\r\ngh\n\r')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="\nabc\ndef\ngh\n";
                <-
            }
            followup="obj->set_compatibility_mode(READER_COMPMODE_OFF);";
            testcode="@test1_testcode";
        }
        test5
        {
            count="1";
            input="STRING('\nabc\rdef\r\ngh\n\r')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="\nabc\ndef\n\ngh\n\n";
                <-
            }
            followup="obj->set_compatibility_mode(READER_COMPMODE_EXT);";
            testcode="@test1_testcode";
        }
        test6
        {
            count="3";
            input="STRING('abc\n\ndef\n\n\ngh')";
            input="STRING('abc\r\rdef\r\r\rgh')";
            input="STRING('abc\r\n\r\ndef\r\n\r\n\r\ngh')";
            output='@parent.parent.parent.name[]_copy';
            setup
            {
                ->
                    ln=str::len(a);
                    const char *r="abc\n\ndef\n\n\ngh";
                <-
            }
            testcode="@test1_testcode";
        }
    }
}
//------------------------------------------------------------------------------
DEF inc_StrReader
{
    iclass="Reader";
    class="StrReader";
    function="create@class";
}
//------------------------------------------------------------------------------
DEF StrReader:CONSTRUCTOR,inc_StrReader
{
    txt_bevore="Einlesen aus einem Speicherbereich:";
    Reader="TRUE";
    StrReader="TRUE";
    brief="Diese Klasse liest Zeichen (vom Typ char) aus einem Speicherbereich.";
    brief_en="This class reads characters (of type <code>char</code>) from a buffer.";
    param:lp_input_str{};
    param:lp_input_length{};
    return:vp="Gibt einen Pointer auf die neu erzeugte Instanz der Klasse <code>@class</code> zurück.";
    remark:remark_set_length{};
    docu
    {
        Reader_INTERFACE;
    }
    test:CTEST,test_common
    {
        name="test1";
    }
    test:CTEST,test_common
    {
        name="test2";
    }
    test:CTEST,test_common
    {
        name="test3";
    }
    test:CTEST,test_common
    {
        name="test4";
    }
    test:CTEST,test_common
    {
        name="test5";
    }
    test:CTEST,test_common
    {
        name="test6";
    }
    test_common
    {
        desc="Beispiele";
        testcode
        {
            ->
            <-
        }
    }
}
//------------------------------------------------------------------------------
DEF destroyStrReader:DESTRUCTOR
{
    StrReader="TRUE";
    Reader="TRUE";
    class="StrReader";
    iclass="Reader";
    function="@this.parent.NAME";
    return:v="";
}
//------------------------------------------------------------------------------
DEF x:METHOD,get
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,getChar
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,getLastError
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,getLastErrorDetail
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,resetLastError
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,getCurrLine
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,getCurrColumn
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,setCurrLine
{
    StrReader="TRUE";
    class="StrReader";
}
DEF x:METHOD,setCurrColumn
{
    StrReader="TRUE";
    class="StrReader";
}
*/
StrReader::StrReader(const char *a,int ln):ReaderImpl()
{
    str=a;
    strLength=ln;
    readPos=0;
}

int StrReader::getNextChar()
{
    if(readPos<strLength)
    {
        currentChar=str[readPos];
        readPos++;
        return 1;
    }
    return 0;
}

/**bmc
lp_input_str16:cc16p
{
    name="a";
    direction="IN";
    desc="Pointer auf den Speicherbereich der den einzulesenden Text enthält.";
    desc_en="Buffer which holds the text to be read.";
}
//------------------------------------------------------------------------------
DEF inc_Char16Reader
{
    iclass="Reader";
    class="Char16Reader";
    function="create@class";
}
//------------------------------------------------------------------------------
DEF Char16Reader:CONSTRUCTOR,inc_Char16Reader
{
    Reader="TRUE";
    Char16Reader="TRUE";
    brief="Diese Klasse liest Zeichen (vom Typ char16_t) aus einem Speicherbereich.";
    brief_en="This class reads characters (of type <code>char16_t</code>) from a buffer.";
    param:lp_input_str16{};
    param:lp_input_length{};
    return:vp="Gibt einen Pointer auf die neu erzeugte Instanz der Klasse <code>@class</code> zurück.";
    remark:remark_set_length{};
    docu
    {
        Reader_INTERFACE;
    }
}
//------------------------------------------------------------------------------
DEF destroyChar16Reader:DESTRUCTOR
{
    Char16Reader="TRUE";
    class="Char16Reader";
    function="@this.parent.NAME";
    return:v="";
}
//------------------------------------------------------------------------------
DEF x:METHOD,get
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,getChar
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,getLastError
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,getLastErrorDetail
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,resetLastError
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,getCurrLine
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,getCurrColumn
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,setCurrLine
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
DEF x:METHOD,setCurrColumn
{
    Char16Reader="TRUE";
    class="Char16Reader";
}
*/
Char16Reader::Char16Reader(const char16_t *a,int ln):ReaderImpl()
{
    str=a;
    strLength=ln;
    readPos=0;
}

int Char16Reader::getNextChar()
{
    if(readPos<strLength)
    {
        currentChar=str[readPos];
        readPos++;
        return 1;
    }
    return 0;
}

/**bmc
lp_input_str32:cc32p
{
    name="a";
    direction="IN";
    desc="Pointer auf den Speicherbereich der den einzulesenden Text enthält.";
    desc_en="Buffer which holds the text to be read.";
}
//------------------------------------------------------------------------------
DEF inc_Char32Reader
{
    iclass="Reader";
    class="Char32Reader";
    function="create@class";
}
//------------------------------------------------------------------------------
DEF Char32Reader:CONSTRUCTOR,inc_Char32Reader
{
    Reader="TRUE";
    Char32Reader="TRUE";
    brief="Diese Klasse liest Zeichen (vom Typ char32_t) aus einem Speicherbereich.";
    brief_en="This class reads characters (of type <code>char32_t</code>) from a buffer.";
    param:lp_input_str32{};
    param:lp_input_length{};
    return:vp="Gibt einen Pointer auf die neu erzeugte Instanz der Klasse <code>@class</code> zurück.";
    remark:remark_set_length{};
    docu
    {
        Reader_INTERFACE;
    }
}
//------------------------------------------------------------------------------
DEF destroyChar32Reader:DESTRUCTOR
{
    Char32Reader="TRUE";
    class="Char32Reader";
    function="@this.parent.NAME";
    return:v="";
}
//------------------------------------------------------------------------------
DEF x:METHOD,get
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,getChar
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,getLastError
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,getLastErrorDetail
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,resetLastError
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,getCurrLine
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,getCurrColumn
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,setCurrLine
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
DEF x:METHOD,setCurrColumn
{
    Char32Reader="TRUE";
    class="Char32Reader";
}
*/
Char32Reader::Char32Reader(const char32_t *a,int ln):ReaderImpl()
{
    str=a;
    strLength=ln;
    readPos=0;
}
int Char32Reader::getNextChar()
{
    if(readPos<strLength)
    {
        currentChar=str[readPos];
        readPos++;
        return 1;
    }
    return 0;
}
