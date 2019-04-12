/*******************************************************************************
*                                                                              *
*  CsvSettings.h                                                               *
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
#ifndef CsvSettings_H
#define CsvSettings_H

#include "csv/import/prokee.h"
#include "csv.hh"

//==============================================================================
// CsvSettings
//==============================================================================
/**bmc
DEF AbsCsvSettings_INTERFACE:INTERFACE
{
    class="AbsCsvSettings";
    no_interface_superclass="TRUE";
    implclass="CsvSettings";
    headers
    {
        ->
        <--
    }
    DEF docu
    {
        title="AbsCsvSettings";
        //text="<pre>@parent.parent.code</pre>";
        section:func.LSECTION
        {
            title="Motivation";
            text
            {
                ->
                <-
            }
        }
    }
}
DEF PAGE_02:FILE,WEBP1
{
    THE_INTERFACE="AbsCsvSettings_INTERFACE";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.html";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.php";
}
DEF AbsCsvSettings
{
    class="AbsCsvSettings";
}
DEF X:WRAPPER
{
    class="CsvSettings";
    baseclass="AbsCsvSettings";
}
*/
class CsvSettings:public AbsCsvSettings2
{
public:
    /**bmc
    DEF field_seperator_in:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zwei Felder voneinander trennt. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>,</span>.
        <br>Dieses Trennzeichen wird beim einlesen der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int field_seperator_in;
    /**bmc
    DEF field_seperator_out:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zwei Felder voneinander trennt. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>,</span>.
        <br>Dieses Trennzeichen wird beim ausgeben der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int field_seperator_out;
    /**bmc
    DEF record_seperator_in:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zwei Zeilen voneinander trennt. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>\\n</span>.
        <br>Dieses Trennzeichen wird beim einlesen der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int record_seperator_in;
    /**bmc
    DEF record_seperator_out:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zwei Zeilen voneinander trennt. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>\\n</span>.
        <br>Dieses Trennzeichen wird beim ausgeben der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int record_seperator_out;
    /**bmc
    DEF string_marker_in:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zum markieren von Beginn und Ende von Strings verwendet wird. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>\"</span>.
        <br>Dieses Trennzeichen wird beim einlesen der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int string_marker_in;
    /**bmc
    DEF string_marker_out:AbsCsvSettings,PUBLIC_MEMBER
    {
        CsvSettings="TRUE";
        AbsCsvSettings="TRUE";
        variable_name="@this.parent.NAME";
        variable_type:i{};
        brief="Zeichen welches zum markieren von Beginn und Ende von Strings verwendet wird. Zum Beispiel <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>\"</span>.
        <br>Dieses Trennzeichen wird beim ausgeben der csv-Daten verwendet.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    //int string_marker_out;
    /**bmc
    DEF inc_CsvSettings
    {
        iclass="AbsCsvSettings";
        class="CsvSettings";
        function="create@class";
    }
    DEF CsvSettings:CONSTRUCTOR,inc_CsvSettings
    {
        AbsCsvSettings="TRUE";
        CsvSettings="TRUE";
        brief
        {
            ->
            Setzt die Member-Variablen wie folgt:
            <br>
            <div style="padding:5px;background-color:&num;DDDDDD;border:solid 1px &num;CCCCCC;">
            <a href="&num;field_seperator_in">field_seperator_in</a> = <code class="name">f</code><br>
            <a href="&num;field_seperator_out">field_seperator_out</a> = <code class="name">f</code><br>
            <a href="&num;record_seperator_in">record_seperator_in</a> = <code class="name">r</code><br>
            <a href="&num;record_seperator_out">record_seperator_out</a> = <code class="name">r</code><br>
            <a href="&num;string_marker_in">string_marker_in</a> = <code class="name">s</code><br>
            <a href="&num;string_marker_out">string_marker_out</a> = <code class="name">s</code>
            </div>
            <-
        }
        param:i{name="f";desc="field_seperator";}
        param:i{name="r";desc="record_seperator";}
        param:i{name="s";desc="string_marker";}
        return:vp="Returns an instance of <code>@class</code>\.";
        docu
        {
            AbsCsvSettings_INTERFACE;
        }
    }
    */
    CsvSettings(int f,int r,int s)
    {
        field_seperator_in=f;
        field_seperator_out=f;
        record_seperator_in=r;
        record_seperator_out=r;
        string_marker_in=s;
        string_marker_out=s;
    }
};

#endif
