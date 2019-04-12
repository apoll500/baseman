/*******************************************************************************
*                                                                              *
*  settings.cpp                                                                *
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
//settings/code/v01/files/source/settings/settings.cpp

#include "settings.h"

bool cmp_name(std::string a,std::string b)
{
    const char *aa=a.c_str();
    const char *bb=b.c_str();
    int i=0;
    while(aa[i] && bb[i] && aa[i]!='[' && bb[i]!='[')
    {
        i++;
    }
    return (aa[i]==0 || aa[i]=='[') && (bb[i]==0 || bb[i]=='[');
}

//------------------------------------------------------------------------------
//  #begin Parameter
//------------------------------------------------------------------------------
/**bmc
DEF param_filename:ccp
{
    name="filename";
    direction="IN";
    desc="Dateiname der Settings-Datei (opt. inkl. Pfad) als null-terminierter String (in ASCII oder UTF-8 Codierung).";
}
DEF param_filenameW:cwp
{
    name="filename";
    direction="IN";
    desc="Dateiname der Settings-Datei (opt. inkl. Pfad) als null-terminierter String (NUR FÜR WIN).";
}
DEF param_docreate:b
{
    name="docreate";
    desc="Gibt an, ob versucht werden soll eine nicht existierende Datei anzulegen.";
}
DEF param_defName:manu_copy
{
    name="defName";
    param_namespace="std";
    param_classname="string";
    desc="Name des Blocks.";
}
DEF param_name:manu_copy
{
    name="name";
    param_namespace="std";
    param_classname="string";
    desc="Name des Eintrags.";
}
DEF param_value:manu_copy
{
    name="value";
    param_namespace="std";
    param_classname="string";
    desc="Wert des Eintrags.";
}
DEF param_i:i
{
    name="i";
    desc="Die Nummerierung als Suffix für den Namen eines Eintrags. Beispiel: Der Eintrag mit dem Namen \"test\" und der Nummerierung i=17 wird unter dem vollständigen Namen \"test[17]\" abgespeichert.";
}
DEF param_defBlockName:ccp
{
    name="defBlockName";
    direction="IN";
    desc="Filename (incl. path)";
}
*/
//------------------------------------------------------------------------------
//  #end
//  #begin Infos
//------------------------------------------------------------------------------
/**bmc
DEF xinfo_morefiles="Durch wiederholten Aufruf dieser Methode können mehrere Settings-Dateien eingelesen werden. Gleich benannte Blöcke werden dabei zu einem Block zusammengefasst.";
DEF xinfo_dosave="Die Änderung wirkt sich nur auf die im Speicher geladenen Einstellungen aus. Verwenden Sie <a href='settings_AbsSettings.php#save'>save()</a> um die Änderungen in die Settings-Datei zu schreiben.";
DEF xinfo_newonget="Falls der Eintrag noch nicht existiert, wird ein solcher Eintrag mit einem Leerstring als Wert angelegt (und der leere String zurückgegeben).";
DEF xinfo_updatenames="Falls seit dem letzten Aufruf von <a href='#loadfile1'>loadfile()</a> weitere Blöcke hinzugefügt wurden, werden diese erst nach einem Aufruf von <a href='#updateDefBlockNames'>updateDefBlockNames()</a> berücksichtigt.";
DEF xinfo_selectload="Der ausgewählte Block wird durch den Wert des Eintrags mit dem Namen \"sblock\" im Block mit dem Namen \"main\" festgelegt.";
DEF xinfo_nameiter="Durch wiederholten Aufruf dieser Methode können alle Einträge abgerufen werden.";// Es kann jedoch immer nur durch einen Block gleichzeitig iteriert werden. D.h. zwischen den Aufrufen die sich auf einen bestimmten Block beziehen, dürfen keine weiteren Aufrufe für andere Blöcke erfolgen.";
*/
//------------------------------------------------------------------------------
//  #end
//  #begin Settings
//------------------------------------------------------------------------------
/*******************************************************************************
*                                                                              *
*  settings                                                                    *
*                                                                              *
*******************************************************************************/
/**bmc
DEF inc_settings
{
    iclass="AbsSettings";
    class="Settings";
    function="create@class";
}
DEF settings:CONSTRUCTOR,inc_settings
{
    AbsSettings="TRUE";
    Settings="TRUE";
    brief="Kann Settings-Dateien einlesen.";
    return:vp="Gibt einen Pointer auf die neu erzeugte Instanz der Klasse <code>@class</code> zurück.";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
Settings::Settings()
{
    //defBlock_iterator=0;
    //name_iterator=0;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- DESTRUCTOR
//------------------------------------------------------------------------------
/**bmc
DEF destroysettings:DESTRUCTOR
{
    Settings="TRUE";
    class="Settings";
    function="@this.parent.NAME";
    return:v="";
}
*/
Settings::~Settings()
{
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- loadfile
//------------------------------------------------------------------------------
/**bmc
DEF loadfile1:ABSTRACT_METHOD
{
    function="loadfile";
    suffix="1";
    brief="Liest eine Settings-Datei ein.";
    xinfo="Falls die Datei nicht existiert, wird @kw.false zurückgegeben.";
    xinfo="@xinfo_morefiles";
    param:param_filename{};
    return:b="Gibt @kw.true zurück, falls die Datei erfolgreich eingelesen werden konnte, sonst @kw.false\.";
}
DEF x:METHOD,loadfile1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:loadfile1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
bool Settings::loadfile(const char *inifilename)
{
    return loadfile(inifilename,false);
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- loadfile
//------------------------------------------------------------------------------
/**bmc
DEF loadfile2:ABSTRACT_METHOD
{
    function="loadfile";
    suffix="2";
    brief="Liest eine Settings-Datei ein.";
    xinfo="Falls die Datei nicht existiert, wird versucht sie anzulegen, falls <code>docreate=</code>@kw.true ist.";
    xinfo="@xinfo_morefiles";
    param:param_filename{};
    param:param_docreate{};
    return:b="Gibt @kw.true zurück, falls die Datei erfolgreich eingelesen werden konnte, sonst @kw.false\.";
}
DEF x:METHOD,loadfile2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:loadfile2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
bool Settings::loadfile(const char *inifilename,bool docreate)
{
    FILE *f=file::openfile(inifilename,"rb");
    if(!f)
    {
        if(docreate)
        {
            f=file::openfile(inifilename,"wb");
            if(!f)return false;
            else
            {
                fclose(f);
                f=file::openfile(inifilename,"rb");
                if(!f)return false;
            }
        }
        else
        {
            return false;
        }
    }
    bool b=loadfile(f);
    fclose(f);
    return b;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- loadfile -- intern
//------------------------------------------------------------------------------
bool Settings::loadfile(FILE *f)
{
    unsigned int i;

    unsigned int name_ln=0;
    unsigned int name_maxln=256;
    char *name=(char *)malloc((name_maxln+1)*sizeof(char));

    unsigned int value_ln=0;
    unsigned int value_maxln=1024;
    char *value=(char *)malloc((value_maxln+1)*sizeof(char));

    unsigned int defName_ln=0;
    unsigned int defName_maxln=128;
    char *defName=(char *)malloc((defName_maxln+1)*sizeof(char));
    defName[0]=0;

    unsigned int a_ln=0;
    unsigned int a_maxln=1024;
    char *a=(char *)malloc((a_maxln+1)*sizeof(char));

    while(readline(f,&a,&a_ln,&a_maxln))
    {
        i=0;

        //skip blancs
        while(iswhite(a[i]))i++;

        //scan DEF
        if(i<a_ln-4 && a[i]=='D' && a[i+1]=='E' && a[i+2]=='F' && (a[i+3]==' ' || a[i+3]=='\t' || a[i+3]==':'))
        {
            i=i+3;

            //copy DEF-Name
            if(a[i]==':')
            {
                defName[0]=0;
            }
            else
            {
                i++;
                while(iswhite(a[i]))i++;
                while(a[i]!=':' && a[i]!=0)
                {
                    if(defName_ln>=defName_maxln)
                    {
                        defName_maxln*=2;
                        defName=(char *)realloc(defName,(defName_maxln+1)*sizeof(char));
                    }
                    defName[defName_ln++]=a[i++];
                }
            }

            defName[defName_ln]=0;
        }
        else if(a[i]=='[')
        {
            i++;
            while(a[i]!=']' && a[i]!=0)
            {
                if(defName_ln>=defName_maxln)
                {
                    defName_maxln*=2;
                    defName=(char *)realloc(defName,(defName_maxln+1)*sizeof(char));
                }
                defName[defName_ln++]=a[i++];
            }
            defName[defName_ln]=0;
        }
        else if(a[i]=='}')
        {
            defName[0]=0;
            defName_ln=0;
        }
        else if(i<a_ln-3 && a[i]=='E' && a[i+1]=='N' && a[i+2]=='D')
        {
            defName[0]=0;
            defName_ln=0;
        }
        else if(a[i]=='$' || a[i]=='-')
        {
            i++;

            if(a[i]=='>')i++;

            name_ln=0;
            while(a[i]!=0 && a[i]!='=')
            {
                if(name_ln>=name_maxln)
                {
                    name_maxln*=2;
                    name=(char *)realloc(name,(name_maxln+1)*sizeof(char));
                }
                name[name_ln++]=a[i++];
            }
            name[name_ln]=0;

            if(a[i]=='=')i++;

            value_ln=0;
            while(a[i]!=0 && a[i]!='\n')
            {
                if(value_ln>=value_maxln)
                {
                    value_maxln*=2;
                    value=(char *)realloc(value,(value_maxln+1)*sizeof(char));
                }
                value[value_ln++]=a[i++];
            }
            value[value_ln]=0;

            parse_value(value,value_ln);

            insert(defName,name,value);
        }
    }

    free(defName);
    free(name);
    free(value);
    free(a);

    updateDefBlockNames();
    return true;
}
bool Settings::iswhite(char ch)
{
    if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')return true;
    return false;
}
unsigned int Settings::readline(FILE *f,char **a,unsigned int *ln,unsigned int *mem_ln)
{
    *ln=0;
    (*a)[*ln]=fgetc(f);
    while((*a)[*ln] && (*a)[*ln]!='\n' && (*a)[*ln]!='\r' && (*a)[*ln]!=EOF)
    {
        (*ln)++;
        if(*ln>=*mem_ln)
        {
            (*mem_ln)*=2;
            (*a)=(char *)realloc(*a,(*mem_ln+1)*sizeof(char));
        }
        (*a)[*ln]=fgetc(f);
    }
    (*a)[*ln]=0;
    return *ln;
}
int Settings::parse_value(char *value,unsigned int value_ln)
{
    if(value[0]=='\"' && value[1])
    {
        int esc=0;
        int pos=0;
        for(unsigned int k=1; k<value_ln; k++)
        {
            if(esc==0 && value[k]=='\\')
            {
                esc=1;
            }
            else if(esc==0 && value[k]=='\"')
            {
                break;
            }
            else if(esc==1)
            {
                esc=0;
                if(value[k]!='\'' && value[k]!='\"')
                {
                    value[pos++]=value[k];
                }
                else if(value[k]!='n')
                {
                    value[pos++]='\n';
                }
                else if(value[k]!='r')
                {
                    value[pos++]='\r';
                }
                else if(value[k]!='t')
                {
                    value[pos++]='\t';
                }
                else if(value[k]!='0')
                {
                    value[pos++]='\0';
                }
                else
                {
                    value[pos++]='\\';
                    value[pos++]=value[k];
                }
            }
            else
            {
                value[pos++]=value[k];
            }
        }
        value[pos]=0;
        return pos;
    }
    return -1;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getDefBlockCount
//------------------------------------------------------------------------------
/**bmc
DEF getDefBlockCount:ABSTRACT_METHOD
{
    function="getDefBlockCount";
    brief="Gibt die Anzahl Blöcke zurück.";
    xinfo="@xinfo_updatenames";
    return:i="Die Anzahl Blöcke.";
}
DEF x:METHOD,getDefBlockCount
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getDefBlockCount,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
int Settings::getDefBlockCount()
{
    return defBlock_names.size();
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getNextDefBlockName
//------------------------------------------------------------------------------
/**bmc
DEF getNextDefBlockName:ABSTRACT_METHOD
{
    function="getNextDefBlockName";
    brief="Gibt den Namen des nächsten Blocks zurück.";
    xinfo="@xinfo_updatenames";
    return:manu_copy
    {
        "Der Name des nächsten Blocks."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextDefBlockName
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNextDefBlockName,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::getNextDefBlockName()
{
    iteration_pos[":::"]%=getDefBlockCount();
    std::string defBlockName=defBlock_names[iteration_pos[":::"]];
    iteration_pos[":::"]++;
    return defBlockName;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- updateDefBlockNames
//------------------------------------------------------------------------------
/**bmc
DEF updateDefBlockNames:ABSTRACT_METHOD
{
    function="updateDefBlockNames";
    brief="Aktualisiert die Liste der Blöcke. Rufen Sie diese Methode auf, wenn nach dem letzten Aufruf von <a href='#loadfile1'>loadfile()</a> weitere Blöcke hinzugefügt wurden bevor Sie <a href='settings_AbsSettings.php#getDefBlockCount'>getDefBlockCount()</a> oder <a href='settings_AbsSettings.php#getNextDefBlockName'>getNextDefBlockName()</a> aufrufen.";
    return:v="";
}
DEF x:METHOD,updateDefBlockNames
{
    Settings="TRUE";
    class="Settings";
}
DEF x:updateDefBlockNames,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
void Settings::updateDefBlockNames()
{
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if(std::find(defBlock_names.begin(),defBlock_names.end(),(*i).first[0])==defBlock_names.end())
        {
            defBlock_names.push_back((*i).first[0]);
        }
    }
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- insert
//------------------------------------------------------------------------------
/**bmc
DEF insert:ABSTRACT_METHOD
{
    function="insert";
    brief="Fügt einen neuen Eintrag zu den Einstellungen hinzu.";
    xinfo="Falls kein Block mit dem angegebenen Namen existiert, wird ein neuer Block mit diesem Namen angelegt.";
    xinfo="Falls im angegebenen Block bereits ein Eintrag mit dem angegebenen Namen existiert, so wird ein neuer Eintrag erzeugt, wobei dem Namen zu Unterscheidung von den bestehenden Einträgen ein Suffix (Nummerierung) der Form [\$i] angehängt wird, mit \$i&in;{0,1,2,3,...} fortlaufend.";
    xinfo="@xinfo_dosave";
    param:param_defName{};
    param:param_name{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,insert
{
    Settings="TRUE";
    class="Settings";
}
DEF x:insert,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
void Settings::insert(std::string defName,std::string name,std::string value)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);

    if(vars.find(index)==vars.end())
    {
        vars[index]=value;
    }
    else
    {
        int i=0;
        char x[36];
        sprintf(x,"%d",i);

        index[1]=name+"["+x+"]";
        while(vars.find(index)!=vars.end())
        {
            i++;
            sprintf(x,"%d",i);
            index[1]=name+"["+x+"]";
        }
        vars[index]=value;
    }
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- set
//------------------------------------------------------------------------------
/**bmc
DEF set1:ABSTRACT_METHOD
{
    function="set";
    suffix="1";
    brief="Überschreibt den Eintrag mit dem angegebenen Namen im angegebenen Block mit einem neuen Wert. Falls der Eintrag noch nicht existiert, wird er neu angelegt.";
    xinfo="@xinfo_dosave";
    param:param_defName{};
    param:param_name{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,set1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:set1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
void Settings::set(std::string defName,std::string name,std::string value)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);
    vars[index]=value;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- set
//------------------------------------------------------------------------------
/**bmc
DEF set2:ABSTRACT_METHOD
{
    function="set";
    suffix="2";
    brief="Überschreibt einen nummerierten Eintrag mit dem angegebenen Namen im angegebenen Block mit einem neuen Wert. Falls der Eintrag noch nicht existiert, wird er neu angelegt.";
    xinfo="@xinfo_dosave";
    param:param_defName{};
    param:param_name{};
    param:param_i{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,set2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:set2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
void Settings::set(std::string defName,std::string name,int i,std::string value)
{
    char x[36];
    sprintf(x,"%d",i);
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name+"["+x+"]");
    vars[index]=value;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- get
//------------------------------------------------------------------------------
/**bmc
DEF get1:ABSTRACT_METHOD
{
    function="get";
    suffix="1";
    brief="Ruft den Wert eines Eintrags ab.";
    xinfo="@xinfo_newonget";
    param:param_defName{};
    param:param_name{};
    return:manu_copy
    {
        "Der Wert des angegebenen Eintrags des angegebenen Blocks."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,get1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:get1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::get(std::string defName,std::string name)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);
    return vars[index];
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- get
//------------------------------------------------------------------------------
/**bmc
DEF get2:ABSTRACT_METHOD
{
    function="get";
    suffix="2";
    brief="Ruft den Wert eines nummerierten Eintrags ab.";
    xinfo="@xinfo_newonget";
    param:param_defName{};
    param:param_name{};
    param:param_i{};
    return:manu_copy
    {
        "Der Wert des angegebenen Eintrags des angegebenen Blocks."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,get2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:get2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::get(std::string defName,std::string name,int i)
{
    char x[36];
    sprintf(x,"%d",i);
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name+"["+x+"]");
    return vars[index];
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- exists
//------------------------------------------------------------------------------
/**bmc
DEF exists1:ABSTRACT_METHOD
{
    function="exists";
    suffix="1";
    brief="Prüft, ob ein Eintrag existiert.";
    param:param_defName{};
    param:param_name{};
    return:b="@kw.true falls der gesuchte Eintrag existiert, sonst @kw.false\.";
}
DEF x:METHOD,exists1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:exists1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
bool Settings::exists(std::string defName,std::string name)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);
    if(vars.find(index)!=vars.end())
    {
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- exists
//------------------------------------------------------------------------------
/**bmc
DEF exists2:ABSTRACT_METHOD
{
    function="exists";
    suffix="2";
    brief="Prüft, ob ein nummerierter Eintrag existiert.";
    param:param_defName{};
    param:param_name{};
    param:param_i{};
    return:b="@kw.true falls der gesuchte Eintrag existiert, sonst @kw.false\.";
}
DEF x:METHOD,exists2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:exists2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
bool Settings::exists(std::string defName,std::string name,int i)
{
    char x[36];
    sprintf(x,"%d",i);
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name+"["+x+"]");
    if(vars.find(index)!=vars.end())
    {
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getNameCount
//------------------------------------------------------------------------------
/**bmc
DEF getNameCount1:ABSTRACT_METHOD
{
    function="getNameCount";
    suffix="1";
    brief="Gibt die Anzahl Einträge im angegebenen Block zurück.";
    param:param_defName{};
    return:i="Anzahl Einträge im angegebenen Block.";
}
DEF x:METHOD,getNameCount1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNameCount1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
int Settings::getNameCount(std::string defName)
{
    int k=0;
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        //printf("--> name = %s\n",(*i).first[0].c_str());
        if((*i).first[0]==defName)k++;
    }
    return k;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getNameCount
//------------------------------------------------------------------------------
/**bmc
DEF getNameCount2:ABSTRACT_METHOD
{
    function="getNameCount";
    suffix="2";
    brief="Gibt die Anzahl Einträge mit dem angegebenen Namen im angegebenen Block zurück.";
    param:param_defName{};
    param:param_name{};
    return:i="Anzahl Einträge mit angegebenem Namen im angegebenen Block.";
}
DEF x:METHOD,getNameCount2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNameCount2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
int Settings::getNameCount(std::string defName,std::string name)
{
    int k=0;
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if((*i).first[0]==defName && cmp_name(name,(*i).first[1]))k++;
    }
    return k;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getNextName
//------------------------------------------------------------------------------
/**bmc
DEF getNextName1:ABSTRACT_METHOD
{
    function="getNextName";
    suffix="1";
    brief="Gibt den Namen des nächsten Eintrags im angegebenen Block zurück.";
    param:param_defName{};
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Name des nächsten Eintrags im angegebenen Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextName1
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNextName1,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::getNextName(std::string defName)
{
    int k=0;
    iteration_pos[defName]%=getNameCount(defName);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        //printf("--> %s\n",(*i).first[1].c_str());
        if((*i).first[0]==defName)
        {
            if(k==iteration_pos[defName])
            {
                iteration_pos[defName]++;
                return (*i).first[1];
            }
            k++;
        }
    }
    iteration_pos[defName]++;
    return "";
}
/**bmc
DEF getNextName2:ABSTRACT_METHOD
{
    function="getNextName";
    suffix="2";
    brief="Gibt den (vollständigen, ggf. um eine Nummerierung erweiterten) Namen des nächsten Eintrags mit angegebenem Namen im angegebenen Block zurück.";
    param:param_defName{};
    param:param_name{};
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Name des nächsten Eintrags mit angegebenem Namen im angegebenen Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextName2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNextName2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::getNextName(std::string defName,std::string name)
{
    int k=0;
    iteration_pos["n:"+defName+":"+name]%=getNameCount(defName,name);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if((*i).first[0]==defName && cmp_name(name,(*i).first[1]))
        {
            if(k==iteration_pos["n:"+defName+":"+name])
            {
                iteration_pos["n:"+defName+":"+name]++;
                return (*i).first[1];
            }
            k++;
        }
    }
    iteration_pos["n:"+defName+":"+name]++;
    return "";
}
/**bmc
DEF getNextValue:ABSTRACT_METHOD
{
    function="getNextValue";
    brief="Gibt den Wert des nächsten Eintrags mit angegebenem Namen im angegebenen Block zurück.";
    param:param_defName{};
    param:param_name{};
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Wert des nächsten Eintrags mit angegebenem Namen im angegebenen Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextValue
{
    Settings="TRUE";
    class="Settings";
}
DEF x:getNextValue,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
std::string Settings::getNextValue(std::string defName,std::string name)
{
    int k=0;
    iteration_pos["v:"+defName+":"+name]%=getNameCount(defName,name);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if((*i).first[0]==defName && cmp_name(name,(*i).first[1]))
        {
            if(k==iteration_pos["v:"+defName+":"+name])
            {
                return (*i).second;
            }
            k++;
        }
    }
    iteration_pos["v:"+defName+":"+name]++;
    return "";
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- save
//------------------------------------------------------------------------------
/**bmc
DEF save:ABSTRACT_METHOD
{
    function="save";
    brief="Schreibt die aktuell geladenen Einstellungen in eine Datei.";
    xinfo="<span style='background-color:&num;FFFFAA;color:&num;AA5500'><b>ACHTUNG:</b></span> Falls die Datei nicht angelegt (bzw. beschrieben) werden kann, bricht das Programm mit <code>exit(EXIT_FAILURE)</code> ab!";
    param:param_filename{};
    return:v="";
}
DEF x:METHOD,save
{
    Settings="TRUE";
    class="Settings";
}
DEF x:save,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
void Settings::save(const char *inifilename)
{
    FILE *f=file::openfile(inifilename,"wb");
    if(!f)
    {
        fprintf(stderr,"Fatal error: ini-File not found or writeable (missing %s).\nthis will terminate.\n",inifilename);
        exit(EXIT_FAILURE);
    }
    print_all(f);
    fclose(f);
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- save2
//------------------------------------------------------------------------------
/**bmc
DEF save2:ABSTRACT_METHOD
{
    function="save2";
    brief="Schreibt die aktuell geladenen Einstellungen in eine Datei.";
    param:param_filename{};
    return:b="Gibt @kw.false zurück, falls die Datei nicht angelegt (bzw. nicht zum Schreiben geöffnet) werden konnte. Sonst wird @kw.true zurückgegeben.";
}
DEF x:METHOD,save2
{
    Settings="TRUE";
    class="Settings";
}
DEF x:save2,AbsSettings,IMETHOD
{
    AbsSettings="TRUE";
    overloaded="FALSE";
    memclass="virtual";
    docu
    {
        AbsSettings_INTERFACE;
    }
}
*/
bool Settings::save2(const char *inifilename)
{
    FILE *f=file::openfile(inifilename,"wb");
    if(!f)
    {
        return false;
    }
    print_all(f);
    fclose(f);
    return true;
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- print
//------------------------------------------------------------------------------
void Settings::print_all(FILE *f)
{
    updateDefBlockNames();
    int i,n=getDefBlockCount();
    std::string defName;
    for(i=0;i<n;i++)
    {
        defName=getNextDefBlockName();
        print_defBlock(f,defName);
    }
}
void Settings::print_defBlock(FILE *f,std::string defName)
{
    fprintf(f,"DEF %s:SETTINGS\n{\n",defName.c_str());
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if((*i).first[0]==defName)fprintf(f,"    $%s=\"%s\";\n",((*i).first)[1].c_str(),(*i).second.c_str());
    }
    fprintf(f,"}\n");
}
/*
void Settings::getNextItemName(std::string defName)
{
    //static int start_index=0;
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin();i!=vars.end();i++)
    {
        if((*i).first[0]==defName)
        {
            //((*i).first)[1].c_str()
            //(*i).second.c_str()
        }
    }
}
*/
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings
//------------------------------------------------------------------------------
/*******************************************************************************
*                                                                              *
*  MultiSettings                                                               *
*                                                                              *
*******************************************************************************/
/**bmc
DEF inc_MultiSettings
{
    iclass="AbsMultiSettings";
    class="MultiSettings";
    function="create@class";
}
DEF MultiSettings:CONSTRUCTOR,inc_MultiSettings
{
    AbsMultiSettings="TRUE";
    MultiSettings="TRUE";
    brief="Kann Settings-Dateien einlesen und ermöglicht einen Block auszuwählen.";
    return:vp="Returns an instance of <code>@class</code>\.";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
MultiSettings::MultiSettings():Settings()
{
    // -- TODO --
    //selectedDefBlockName=getSelectedDefBlockName();
    selectedDefBlockName="";
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- DESTRUCTOR
//------------------------------------------------------------------------------
/**bmc
DEF destroyMultiSettings:DESTRUCTOR
{
    MultiSettings="TRUE";
    class="MultiSettings";
    function="@this.parent.NAME";
    return:v="";
}
*/
MultiSettings::~MultiSettings()
{
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- loadfile
//------------------------------------------------------------------------------
/**bmc
DEF loadfile_M1:ABSTRACT_METHOD
{
    function="loadfile";
    suffix="1";
    brief="Liest eine Settings-Datei ein.";
    xinfo="Falls die Datei nicht existiert, wird @kw.false zurückgegeben.";
    xinfo="@xinfo_morefiles";
    xinfo="@xinfo_selectload";
    param:param_filename{};
    return:b="Gibt @kw.true zurück, falls die Datei erfolgreich eingelesen werden konnte, sonst @kw.false\.";
}
DEF x:METHOD,loadfile_M1
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:loadfile_M1,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
bool MultiSettings::loadfile(const char *inifilename)
{
    bool b=Settings::loadfile(inifilename);
    selectedDefBlockName=getSelectedDefBlockName();
    return b;
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- loadfile
//------------------------------------------------------------------------------
/**bmc
DEF loadfile_M2:ABSTRACT_METHOD
{
    function="loadfile";
    suffix="2";
    brief="Liest eine Settings-Datei ein.";
    xinfo="Falls die Datei nicht existiert, wird versucht sie anzulegen, falls <code>docreate=</code>@kw.true ist.";
    xinfo="@xinfo_morefiles";
    xinfo="@xinfo_selectload";
    param:param_filename{};
    param:param_docreate{};
    return:b="Gibt @kw.true zurück, falls die Datei erfolgreich eingelesen werden konnte, sonst @kw.false\.";
}
DEF x:METHOD,loadfile_M2
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:loadfile_M2,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
bool MultiSettings::loadfile(const char *inifilename,bool docreate)
{
    bool b=Settings::loadfile(inifilename,docreate);
    selectedDefBlockName=getSelectedDefBlockName();
    return b;
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- setSelectedDefBlockName
//------------------------------------------------------------------------------
/**bmc
DEF setSelectedDefBlockName:ABSTRACT_METHOD
{
    function="setSelectedDefBlockName";
    brief="Legt den ausgewählten Block fest. (Der Block muss nicht existieren. Ein neuer Block wird erst angelegt, wenn Werte eingetragen oder abgefragt werden.)";
    param:param_defBlockName{};
    return:v="";
}
DEF x:METHOD,setSelectedDefBlockName
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:setSelectedDefBlockName,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
void MultiSettings::setSelectedDefBlockName(const char *defBlockName)
{
    selectedDefBlockName=defBlockName;
    set("main","sblock",defBlockName);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- getSelectedDefBlockName
//------------------------------------------------------------------------------
/**bmc
DEF getSelectedDefBlockName:ABSTRACT_METHOD
{
    function="getSelectedDefBlockName";
    brief="Gibt den Namen des ausgewählten Blocks zurück.";
    return:manu_copy
    {
        "Der Name des ausgewählten Blocks."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getSelectedDefBlockName
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getSelectedDefBlockName,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::getSelectedDefBlockName()
{
    return get("main","sblock");
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- insert
//------------------------------------------------------------------------------
/**bmc
DEF insertM:ABSTRACT_METHOD
{
    function="insert";
    brief="Fügt dem ausgewählten Block einen neuen Eintrag hinzu.";
    xinfo="Falls der ausgewählte Block noch nicht existiert, wird er angelegt.";
    xinfo="Falls im ausgewählten Block bereits ein Eintrag mit dem angegebenen Namen existiert, so wird ein neuer Eintrag erzeugt, wobei dem Namen zu Unterscheidung von den bestehenden Einträgen ein Suffix (Nummerierung) der Form [\$i] angehängt wird, mit \$i&in;{0,1,2,3,...} fortlaufend.";
    xinfo="@xinfo_dosave";
    param:param_name{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,insertM
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:insertM,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
void MultiSettings::insert(std::string name,std::string value)
{
    insert(selectedDefBlockName,name,value);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- set
//------------------------------------------------------------------------------
/**bmc
DEF setM1:ABSTRACT_METHOD
{
    function="set";
    suffix="1";
    brief="Überschreibt den Eintrag mit dem angegebenen Namen im ausgewählten Block mit einem neuen Wert. Falls der Eintrag noch nicht existiert, wird er neu angelegt.";
    xinfo="@xinfo_dosave";
    param:param_name{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,setM1
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:setM1,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
void MultiSettings::set(std::string name,std::string value)
{
    set(selectedDefBlockName,name,value);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- set
//------------------------------------------------------------------------------
/**bmc
DEF setM2:ABSTRACT_METHOD
{
    function="set";
    suffix="2";
    brief="Überschreibt einen nummerierten Eintrag mit dem angegebenen Namen im ausgewählten Block mit einem neuen Wert. Falls der Eintrag noch nicht existiert, wird er neu angelegt.";
    xinfo="@xinfo_dosave";
    param:param_name{};
    param:param_i{};
    param:param_value{};
    return:v="";
}
DEF x:METHOD,setM2
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:setM2,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
void MultiSettings::set(std::string name,int i,std::string value)
{
    set(selectedDefBlockName,name,i,value);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- get
//------------------------------------------------------------------------------
/**bmc
DEF getM1:ABSTRACT_METHOD
{
    function="get";
    suffix="1";
    brief="Ruft den Wert eines Eintrags im ausgewählten Block ab.";
    xinfo="@xinfo_newonget";
    param:param_name{};
    return:manu_copy
    {
        "Der Wert des angegebenen Eintrags im ausgewählten Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getM1
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getM1,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::get(std::string name)
{
    return get(selectedDefBlockName,name);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- get
//------------------------------------------------------------------------------
/**bmc
DEF getM2:ABSTRACT_METHOD
{
    function="get";
    suffix="2";
    brief="Ruft den Wert eines nummerierten Eintrags im ausgewählten Block ab.";
    xinfo="@xinfo_newonget";
    param:param_name{};
    param:param_i{};
    return:manu_copy
    {
        "Der Wert des angegebenen Eintrags im ausgewählten Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getM2
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getM2,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::get(std::string name,int i)
{
    return get(selectedDefBlockName,name,i);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- exists
//------------------------------------------------------------------------------
/**bmc
DEF existsM1:ABSTRACT_METHOD
{
    function="exists";
    suffix="1";
    brief="Prüft, ob der Eintrag im ausgewählten Block existiert.";
    param:param_name{};
    return:b="@kw.true falls der gesuchte Eintrag existiert, sonst @kw.false\.";
}
DEF x:METHOD,existsM1
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:existsM1,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
bool MultiSettings::exists(std::string name)
{
    return exists(selectedDefBlockName,name);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- exists
//------------------------------------------------------------------------------
/**bmc
DEF existsM2:ABSTRACT_METHOD
{
    function="exists";
    suffix="2";
    brief="Prüft, ob der nummerierte Eintrag im ausgewählten Block existiert.";
    param:param_name{};
    param:param_i{};
    return:b="@kw.true falls der gesuchte Eintrag existiert, sonst @kw.false\.";
}
DEF x:METHOD,existsM2
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:existsM2,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
bool MultiSettings::exists(std::string name,int i)
{
    return exists(selectedDefBlockName,name,i);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- getNameCount
//------------------------------------------------------------------------------
/**bmc
DEF getNameCountM21:ABSTRACT_METHOD
{
    function="getNameCount";
    suffix="1";
    brief="Gibt die Anzahl Einträge im ausgewählten Block zurück.";
    return:i="Anzahl Einträge im ausgewählten Block.";
}
DEF x:METHOD,getNameCountM21
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getNameCountM21,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
int MultiSettings::getNameCount()
{
    return Settings::getNameCount(selectedDefBlockName);
}
//------------------------------------------------------------------------------
//  #end
//  #begin Settings -- getNameCount
//------------------------------------------------------------------------------
/**bmc
DEF getNameCountM22:ABSTRACT_METHOD
{
    function="getNameCount";
    suffix="2";
    brief="Gibt die Anzahl Einträge mit angegebenem Namen im angegebenen Block zurück.";
    param:param_name{};
    return:i="Anzahl Einträge mit angegebenem Namen im angegebenen Block.";
}
DEF x:METHOD,getNameCountM22
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getNameCountM22,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
int MultiSettings::getNameCount(std::string name)
{
    return Settings::getNameCount(selectedDefBlockName,name);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- getNextName
//------------------------------------------------------------------------------
/**bmc
DEF getNextNameM21:ABSTRACT_METHOD
{
    function="getNextName";
    suffix="1";
    brief="Gibt den Namen des nächsten Eintrags im ausgewählten Block zurück.";
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Name des nächsten Eintrags im ausgewählten Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextNameM21
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getNextNameM21,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::getNextName()
{
    return Settings::getNextName(selectedDefBlockName);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- getNextName
//------------------------------------------------------------------------------
/**bmc
DEF getNextNameM22:ABSTRACT_METHOD
{
    function="getNextName";
    suffix="2";
    brief="Gibt den (vollständigen, ggf. um eine Nummerierung erweiterten) Namen des nächsten Eintrags mit angegebenem Namen im ausgewählten Block zurück.";
    param:param_name{};
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Name des nächsten Eintrags mit angegebenem Namen im ausgewählten Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextNameM22
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getNextNameM22,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::getNextName(std::string name)
{
    return Settings::getNextName(selectedDefBlockName,name);
}
/**bmc
DEF getNextValueM2:ABSTRACT_METHOD
{
    function="getNextValue";
    suffix="2";
    brief="Gibt den Wert des nächsten Eintrags mit angegebenem Namen im ausgewählten Block zurück.";
    param:param_name{};
    xinfo="@xinfo_nameiter";
    return:manu_copy
    {
        "Der Wert des nächsten Eintrags mit angegebenem Namen im ausgewählten Block."
        param_namespace="std";
        param_classname="string";
    }
}
DEF x:METHOD,getNextValueM2
{
    MultiSettings="TRUE";
    class="MultiSettings";
}
DEF x:getNextValueM2,AbsMultiSettings,IMETHOD
{
    AbsMultiSettings="TRUE";
    memclass="virtual";
    docu
    {
        AbsMultiSettings_INTERFACE;
    }
}
*/
std::string MultiSettings::getNextValue(std::string name)
{
    return Settings::getNextValue(selectedDefBlockName,name);
}
//------------------------------------------------------------------------------
//  #end
//  #begin MultiSettings -- print_defBlock
//------------------------------------------------------------------------------
void MultiSettings::print_defBlock(FILE *f)
{
    print_defBlock(f,selectedDefBlockName);
}
//------------------------------------------------------------------------------
//  #end
//------------------------------------------------------------------------------
