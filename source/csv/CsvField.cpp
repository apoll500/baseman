/*******************************************************************************
*                                                                              *
*  CsvField.cpp                                                                *
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
#include "CsvField.h"
#include "csv.h"

//#include "reader/reader.h"

//#include "CsvSettings.h"

/**bmc
DEF param_CsvSettings:manu
{
    name="s";
    desc="Pointer to an instance of an implementation of AbsCsvSettings.<br>See <a href='@param_classinfo[]_AbsCsvSettings\.php'>@param_classinfo\:AbsCsvSettings</a>.";
    param_classname="AbsCsvSettings";
    param_classinfo="csv";
}
DEF param_file:FILEp
{
    name="f";
    desc="Handle auf eine zum Schreiben geöffnete Datei.";
}
*/
//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
/**bmc
DEF inc_CsvField
{
    iclass="AbsCsvField";
    class="CsvField";
    function="create@class";
}
DEF CsvField:CONSTRUCTOR,inc_CsvField
{
    AbsCsvField="TRUE";
    CsvField="TRUE";
    brief="Der Konstruktor setzt den Wert des Feldes auf <span style='padding:3px;background-color:#DDDDDD;border:solid 1px &num;AAAAAA;'>\"\"</span> (Leerstring). Rufen Sie die Methode <a href='&num;load'>load()</a> auf um das nächste Feld aus der csv-Datei einzulesen. (Der eingelesene Wert wird in diesem Objekt als Wert des Feldes gespeichert.)";
    param:param_CsvSettings{};
    return:vp="Returns an instance of <code>@class</code>\.";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
CsvField::CsvField(AbsCsvSettings *s)
{
    settings=s;
    value_ln=CSV_INI_FLD_LENGTH;
    value=(char *)malloc((value_ln+1)*sizeof(char));
    value[0]=0;
}
/**bmc
DEF destroyCsvField:DESTRUCTOR
{
    CsvField="TRUE";
    class="CsvField";
    function="@this.parent.NAME";
    return:v="";
}
*/
CsvField::~CsvField()
{
    free(value);
}
/**bmc
DEF loadF:ABSTRACT_METHOD
{
    function="load";
    brief="Liest das nächste Feld aus der csv-Datei. Der eingelesene Wert (String) wird in diesem Objekt als Wert des Feldes gespeichert. Diese Methode sollte nur einmal aufgerufen werden.";
    param:param_Reader{};
    return:i
    {
        ->
        <table>
            <tr>
                <td>1</td>
                <td>Es folgen weitere Felder.</td>
            </tr>
            <tr>
                <td>0</td>
                <td>Zeilenende erreicht. Es folgen weitere Zeilen.</td>
            </tr>
            <tr>
                <td>-1</td>
                <td>Dateiende erreicht</td>
            </tr>
        </table>
        <-
    };
}
DEF x:METHOD,loadF
{
    CsvField="TRUE";
    class="CsvField";
}
DEF x:loadF,AbsCsvField,IMETHOD
{
    AbsCsvField="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
int CsvField::load(Reader *r)
{
    int ch;
    int opos=0;
    bool isinstr=false;
    bool instr_begin=false;
    bool skip=false;
    while((ch=r->get())!=-1)
    {
        if(!isinstr)
        {
            if(ch==settings->get_field_seperator_in())return 1;
            else if(ch==settings->get_record_seperator_in())return 0;
            else if(ch==settings->get_string_marker_in())
            {
                isinstr=true;
                instr_begin=true;
            }
        }
        else
        {
            if(!skip)
            {
                if(ch==settings->get_string_marker_in())
                {
                    skip=true;
                }
            }
            else
            {
                if(ch==settings->get_field_seperator_in())
                {
                    return 1;
                }
                else if(ch==settings->get_record_seperator_in())
                {
                    return 0;
                }
                else if(ch==settings->get_string_marker_in())
                {
                    skip=false;
                }
                else
                {
                    skip=false;
                    isinstr=false;
                }
            }
        }
        if(!skip && !instr_begin)
        {
            if(opos>=value_ln)
            {
                value_ln*=2;
                value=(char *)realloc(value,(value_ln+1)*sizeof(char));
            }
            value[opos++]=ch;
            value[opos]=0;
        }
        instr_begin=false;
    }
    return -1;
}
bool CsvField::match(const char *val)
{
    //printf("match %s with %s\n",value,val);
    return strcmp(value,val)==0;
}
/**bmc
DEF get:ABSTRACT_METHOD
{
    function="get";
    brief="Gibt den Wert des Feldes zurück.";
    return:cp="Der Wert des Feldes.";
}
DEF x:METHOD,get
{
    CsvField="TRUE";
    class="CsvField";
}
DEF x:get,AbsCsvField,IMETHOD
{
    AbsCsvField="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
char *CsvField::get()
{
    return value;
}
/**bmc
DEF set:ABSTRACT_METHOD
{
    function="set";
    brief="Setzt den Wert des Feldes.";
    param:param_val{};
    return:v="";
}
DEF x:METHOD,set
{
    CsvField="TRUE";
    class="CsvField";
}
DEF x:set,AbsCsvField,IMETHOD
{
    AbsCsvField="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
void CsvField::set(const char *v)
{
    value=(char *)realloc(value,(strlen(v)+1)*sizeof(char));
    strcpy(value,v);
}
/**bmc
DEF printF1:ABSTRACT_METHOD
{
    function="print";
    suffix="1";
    brief="Schreibt das Feld in die Datei <code class='name'>f</code>.";
    xinfo="Diese Methode ruft die Methode <a href='#print2'>print (version 2)</a> auf.";
    param:param_file{};
    return:v="";
}
DEF x:METHOD,printF1
{
    CsvField="TRUE";
    class="CsvField";
}
DEF x:printF1,AbsCsvField,IMETHOD
{
    AbsCsvField="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
void CsvField::print(FILE *f)
{
    print(f,value);
}
/**bmc
DEF printF2:ABSTRACT_METHOD
{
    function="print";
    suffix="2";
    brief="Schreibt den Wert <code class='name'>val</code> als csv-Feld in die Datei <code class='name'>f</code>.";
    xinfo="Es wird <code class='name'>val</code> entweder unverändert ausgegeben, oder falls erforderlich unter Anführungszeichen (bzw. mit String-Markierngs-Symbolen versehen, wie durch <a href='@modname[]_AbsCsvSettings.php&num;string_marker_out'>string_marker_out</a> festgelegt).
    <br><br>
    Beispiele:
    <br>a) <code class='name'>Hello Wolrd!</code> wird unverändert ausgegeben als <code class='name'>Hello Wolrd!</code>.
    <br>b) <code class='name'>red, green and blue</code> wird ausgegeben als <code class='name'>\"red, green and blue\"</code>.
    <br>c) <code class='name'>\"Hallo\"</code> wird ausgegeben als <code class='name'>\"\"\"Hallo\"\"\"</code>.
    ";
    param:param_file{};
    param:param_val{};
    return:v="";
}
DEF x:METHOD,printF2
{
    CsvField="TRUE";
    class="CsvField";
}
DEF x:printF2,AbsCsvField,IMETHOD
{
    AbsCsvField="TRUE";
    memclass="virtual";
    docu
    {
        AbsCsvField_INTERFACE;
    }
}
*/
void CsvField::print(FILE *f,const char *val)
{
    int i=0;
    bool doquote=false;
    while(val[i]!=0)
    {
        if(val[i]==settings->get_field_seperator_out() ||
                val[i]==settings->get_record_seperator_out() ||
                val[i]==settings->get_string_marker_out())
        {
            doquote=true;
        }
        i++;
    }
    if(doquote)
    {
        i=0;
        fprintf(f,"%c",settings->get_string_marker_out());
        while(val[i]!=0)
        {
            if(val[i]==settings->get_string_marker_out())
            {
                fprintf(f,"%c",settings->get_string_marker_out());
            }
            fprintf(f,"%c",val[i]);
            i++;
        }
        fprintf(f,"%c",settings->get_string_marker_out());
    }
    else
    {
        fprintf(f,"%s",val);
    }
}
