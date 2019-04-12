/*******************************************************************************
*                                                                              *
*  settings.h                                                                  *
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
//settings/code/v01/files/source/settings/settings.h

#ifndef MOD_settings_H
#define MOD_settings_H

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

#include "settings/import/prokee.h"
#include "settings/settings.hh"

//==============================================================================
// Settings
//==============================================================================
/**bmc
DEF AbsSettings_INTERFACE:INTERFACE
{
    class="AbsSettings";
    no_interface_superclass="TRUE";
    implclass="Settings";
    interface_subclass_show="TRUE";
    interface_subclass="AbsMultiSettings";
    //is_virtual="virtual";
    headers
    {
        ->
        #include <vector>
        #include <map>
        #include <string>
        class Reader;
        <--
    }
    DEF docu
    {
        title="AbsSettings";
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
    THE_INTERFACE="AbsSettings_INTERFACE";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.html";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.php";
}
DEF H3IFACE:FILE,H3INTERFACE
{
    THE_INTERFACE="AbsSettings_INTERFACE";
}
DEF AbsSettings
{
    class="AbsSettings";
}
DEF X:WRAPPER
{
    class="Settings";
    baseclass="AbsSettings";
}
*/
#include "h3_AbsSettings.h"
class Settings:public AbsSettings3
{
protected:
    std::vector<std::string> defBlock_names;
    std::map<std::vector<std::string>,std::string>vars;
    //int defBlock_iterator;
    //int name_iterator;
    std::map<std::string,int> iteration_pos;
public:
    Settings();
    virtual ~Settings();

    bool loadfile(const char *inifilename);
    bool loadfile(const char *inifilename,bool docreate);
    bool loadfile(FILE *f);
private:
    bool iswhite(char ch);
    unsigned int readline(FILE *f,char **a,unsigned int *ln,unsigned int *mem_ln);
    int parse_value(char *value,unsigned int value_ln);
public:
    virtual int getDefBlockCount();
    virtual std::string getNextDefBlockName();
    virtual void updateDefBlockNames();

    virtual void insert(std::string defName,std::string name,std::string value);
    virtual void set(std::string defName,std::string name,std::string value);
    virtual void set(std::string defName,std::string name,int i,std::string value);
    virtual std::string get(std::string defName,std::string name);
    virtual std::string get(std::string defName,std::string name,int i);
    virtual bool exists(std::string defName,std::string name);
    virtual bool exists(std::string defName,std::string name,int i);
    virtual int getNameCount(std::string defName);
    virtual int getNameCount(std::string defName,std::string name);
    virtual std::string getNextName(std::string defName);
    virtual std::string getNextName(std::string defName,std::string name);
    virtual std::string getNextValue(std::string defName,std::string name);
    virtual void save(const char *inifilename);
    virtual bool save2(const char *inifilename);
    virtual void print_all(FILE *f);
    virtual void print_defBlock(FILE *f,std::string defName);
};

//==============================================================================
// MultiSettings
//==============================================================================
/**bmc
DEF AbsMultiSettings_INTERFACE:INTERFACE
{
    class="AbsMultiSettings";
    interface_superclass="AbsSettings";
    interface_superclass_impl="Settings";
    implclass="MultiSettings";
    headers
    {
        ->
        class Reader;
        <--
    }
    __add_mthods
    {
        ->
            using AbsSettings::insert;
            using AbsSettings::set;
            using AbsSettings::get;
            using AbsSettings::exists;
            using AbsSettings::getNameCount;
            using AbsSettings::getNextName;
            using AbsSettings::getNextValue;
        <-
    }
    DEF docu
    {
        title="AbsMultiSettings";
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
    THE_INTERFACE="AbsMultiSettings_INTERFACE";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.html";
    PATH="../../../../docu/html/@modname[]_@version[]@<@THE_INTERFACE>.class[text='_#']\.php";
}
DEF H3IFACE:FILE,H3INTERFACE
{
    THE_INTERFACE="AbsMultiSettings_INTERFACE";
}
DEF AbsMultiSettings
{
    class="AbsMultiSettings";
}
DEF X:WRAPPER
{
    class="MultiSettings";
    baseclass="AbsMultiSettings";
}
*/
#include "h3_AbsMultiSettings.h"
class MultiSettings:virtual public Settings,public AbsMultiSettings3
{
private:
    std::string selectedDefBlockName;
public:
    MultiSettings();
    virtual ~MultiSettings();

    virtual bool loadfile(const char *inifilename);
    virtual bool loadfile(const char *inifilename,bool);
    virtual void setSelectedDefBlockName(const char *defBlockName);
    virtual std::string getSelectedDefBlockName();

    using Settings::insert;
    using Settings::set;
    using Settings::get;
    using Settings::exists;
    using Settings::print_defBlock;
    using Settings::getNameCount;
    using Settings::getNextName;
    using Settings::getNextValue;

    /*
    using AbsMultiSettings3::insert;
    using AbsMultiSettings3::set;
    using AbsMultiSettings3::get;
    using AbsMultiSettings3::exists;
    using AbsMultiSettings3::print_defBlock;
    using AbsMultiSettings3::getNameCount;
    using AbsMultiSettings3::getNextName;
    using AbsMultiSettings3::getNextValue;
    */

    virtual void insert(std::string name,std::string value);
    virtual void set(std::string name,std::string value);
    virtual void set(std::string name,int i,std::string value);
    virtual std::string get(std::string name);
    virtual std::string get(std::string name,int i);
    virtual bool exists(std::string name);
    virtual bool exists(std::string name,int i);
    virtual int getNameCount();
    virtual int getNameCount(std::string name);
    virtual std::string getNextName();
    virtual std::string getNextName(std::string name);
    virtual std::string getNextValue(std::string name);
    virtual void print_defBlock(FILE *f);
};

#include "settings/import/modules.h"

#include "settings/settings.hh2"

#endif
