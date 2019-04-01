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

Settings::Settings()
{
    //defBlock_iterator=0;
    //name_iterator=0;
}
Settings::~Settings()
{
}
bool Settings::loadfile(const char *inifilename)
{
    return loadfile(inifilename,false);
}
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
int Settings::getDefBlockCount()
{
    return defBlock_names.size();
}
std::string Settings::getNextDefBlockName()
{
    iteration_pos[":::"]%=getDefBlockCount();
    std::string defBlockName=defBlock_names[iteration_pos[":::"]];
    iteration_pos[":::"]++;
    return defBlockName;
}
void Settings::updateDefBlockNames()
{
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
    {
        if(std::find(defBlock_names.begin(),defBlock_names.end(),(*i).first[0])==defBlock_names.end())
        {
            defBlock_names.push_back((*i).first[0]);
        }
    }
}
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
void Settings::set(std::string defName,std::string name,std::string value)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);
    vars[index]=value;
}
void Settings::set(std::string defName,std::string name,int i,std::string value)
{
    char x[36];
    sprintf(x,"%d",i);
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name+"["+x+"]");
    vars[index]=value;
}
std::string Settings::get(std::string defName,std::string name)
{
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name);
    return vars[index];
}
std::string Settings::get(std::string defName,std::string name,int i)
{
    char x[36];
    sprintf(x,"%d",i);
    std::vector<std::string> index;
    index.push_back(defName);
    index.push_back(name+"["+x+"]");
    return vars[index];
}
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
int Settings::getNameCount(std::string defName)
{
    int k=0;
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
    {
        if((*i).first[0]==defName)k++;
    }
    return k;
}
int Settings::getNameCount(std::string defName,std::string name)
{
    int k=0;
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
    {
        if((*i).first[0]==defName && cmp_name(name,(*i).first[1]))k++;
    }
    return k;
}
std::string Settings::getNextName(std::string defName)
{
    int k=0;
    iteration_pos[defName]%=getNameCount(defName);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
    {
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
std::string Settings::getNextName(std::string defName,std::string name)
{
    int k=0;
    iteration_pos["n:"+defName+":"+name]%=getNameCount(defName,name);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
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
std::string Settings::getNextValue(std::string defName,std::string name)
{
    int k=0;
    iteration_pos["v:"+defName+":"+name]%=getNameCount(defName,name);
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
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
void Settings::print_all(FILE *f)
{
    updateDefBlockNames();
    int i,n=getDefBlockCount();
    std::string defName;
    for(i=0; i<n; i++)
    {
        defName=getNextDefBlockName();
        print_defBlock(f,defName);
    }
}
void Settings::print_defBlock(FILE *f,std::string defName)
{
    fprintf(f,"DEF %s:SETTINGS\n{\n",defName.c_str());
    for(std::map<std::vector<std::string>,std::string>::iterator i=vars.begin(); i!=vars.end(); i++)
    {
        if((*i).first[0]==defName)fprintf(f,"    $%s=\"%s\";\n",((*i).first)[1].c_str(),(*i).second.c_str());
    }
    fprintf(f,"}\n");
}
MultiSettings::MultiSettings():Settings()
{
    // -- TODO --
    //selectedDefBlockName=getSelectedDefBlockName();
    selectedDefBlockName="";
}
MultiSettings::~MultiSettings()
{
}
bool MultiSettings::loadfile(const char *inifilename)
{
    bool b=Settings::loadfile(inifilename);
    selectedDefBlockName=getSelectedDefBlockName();
    return b;
}
bool MultiSettings::loadfile(const char *inifilename,bool docreate)
{
    bool b=Settings::loadfile(inifilename,docreate);
    selectedDefBlockName=getSelectedDefBlockName();
    return b;
}
void MultiSettings::setSelectedDefBlockName(const char *defBlockName)
{
    selectedDefBlockName=defBlockName;
    set("main","sblock",defBlockName);
}
std::string MultiSettings::getSelectedDefBlockName()
{
    return get("main","sblock");
}
void MultiSettings::insert(std::string name,std::string value)
{
    insert(selectedDefBlockName,name,value);
}
void MultiSettings::set(std::string name,std::string value)
{
    set(selectedDefBlockName,name,value);
}
void MultiSettings::set(std::string name,int i,std::string value)
{
    set(selectedDefBlockName,name,i,value);
}
std::string MultiSettings::get(std::string name)
{
    return get(selectedDefBlockName,name);
}
std::string MultiSettings::get(std::string name,int i)
{
    return get(selectedDefBlockName,name,i);
}
bool MultiSettings::exists(std::string name)
{
    return exists(selectedDefBlockName,name);
}
bool MultiSettings::exists(std::string name,int i)
{
    return exists(selectedDefBlockName,name,i);
}
int MultiSettings::getNameCount()
{
    return Settings::getNameCount(selectedDefBlockName);
}
int MultiSettings::getNameCount(std::string name)
{
    return Settings::getNameCount(selectedDefBlockName,name);
}
std::string MultiSettings::getNextName()
{
    return Settings::getNextName(selectedDefBlockName);
}
std::string MultiSettings::getNextName(std::string name)
{
    return Settings::getNextName(selectedDefBlockName,name);
}
std::string MultiSettings::getNextValue(std::string name)
{
    return Settings::getNextValue(selectedDefBlockName,name);
}
void MultiSettings::print_defBlock(FILE *f)
{
    print_defBlock(f,selectedDefBlockName);
}
