/*******************************************************************************
*                                                                              *
*  baseman.cpp                                                                 *
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
#include "baseman.h"

#include "bm/bm.h"
#include "bm/base.h"
#include "bm/project.h"
#include "bm/version.h"

MultiSettings *ini;

Bm *bmObject(void)
{
    Bm *p;
    if(ini->get("version")!="")
    {
        p=new Version();
    }
    else if(ini->get("project")!="")
    {
        p=new Project();
    }
    else if(ini->get("base")!="")
    {
        p=new Base();
    }
    else
    {
        return 0;
    }
    if(p->getError())
    {
        delete p;
        return 0;
    }
    return p;
}
/*********************************************************
*                                                        *
*  location                                              *
*                                                        *
*********************************************************/
void print_location(void)
{
    std::string group_s=ini->get("group");
    const char *group=group_s.c_str();
    if(group[0]==0)group="1";

    std::string base_s=ini->get("base");
    const char *base=base_s.c_str();

    std::string project_s=ini->get("project");
    const char *project=project_s.c_str();

    std::string version_s=ini->get("version");
    const char *version=version_s.c_str();

    osio::print("@%s:/",group);
    if(base[0]!=0)osio::print("%s/",base);
    if(project[0]!=0)osio::print("%s/",project);
    if(version[0]!=0)osio::print("%s/",version);
}
/*********************************************************
*                                                        *
*  create                                                *
*                                                        *
*********************************************************/
void create_base0(const char *base,const char *path)
{
    std::string group_s=ini->get("group");
    const char *group=group_s.c_str();

    if(group[0]==0)group="1";
    create_base(base,path,group);
}
void create_base(const char *base,const char *path,const char *group)
{
    CsvData data;

    data.load(BASEMAN_BASELISTPATH,"name,path,target,flag,description");

    data.useHeader(true);
    int hid_name=data.getHeaderId("name");

    CsvRecord **rec=data.getAllRecords("flag",group);
    int i=0;
    while(rec[i]!=0)
    {
        if(strcmp(rec[i++]->getField(hid_name),base)==0)
        {
            osio::print("Can't create base %s in group %s. Base already exists in this group.",base,group);
            return;
        }
    }

    int row=data.addRecord();
    if(!data.setField(row,"name",base))osio::print("!-");
    if(!data.setField(row,"path",path))osio::print("!-");
    if(!data.setField(row,"flag",group))osio::print("!-");

    data.save(BASEMAN_BASELISTPATH);
}
/*********************************************************
*                                                        *
*  list                                                  *
*                                                        *
*********************************************************/
void list_selected_group(void)
{
    std::string group_s=ini->get("group");
    const char *group=group_s.c_str();

    if(group[0]==0)list_group("1");
    else list_group(group);
}
void list_group(const char *group)
{
    CsvData data;

    data.load(BASEMAN_BASELISTPATH,"name,path,target,flag,description");

    data.useHeader(true);
    int hid_name=data.getHeaderId("name");

    int col_list[2];
    col_list[0]=hid_name;
    col_list[1]=INT_MAX;

    osio::print("\nBases:\n----------------------------------------------------------------------\n");

    CsvRecord **rec=data.getAllRecords("flag",group);
    int i=0;
    while(rec && rec[i]!=0)
    {
        osio::print("    ");
        rec[i++]->print_ln(stdout,col_list);
    }
}
/*********************************************************
*                                                        *
*  select and reset                                      *
*                                                        *
*********************************************************/
void reset(void)
{
    ini->set("base","");
    ini->set("project","");
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::print("Location is now at level <group>.\n");
}
void select_group(const char *group)
{
    ini->set("group",group);
    ini->set("base","");
    ini->set("project","");
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::print("Group %s selected.\n",group);
    osio::print("Location is now at level <group>.\n");
}
void select_base(const char *base)
{
    ini->set("base",base);
    ini->set("project","");
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::print("Base %s selected.\n",base);
    osio::print("Location is now at level <base>.\n");
}
void select_project(const char *project)
{
    std::string p=ini->get("project");
    if(p!="")ini->set("project",p+"/"+project);
    else ini->set("project",project);
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::print("Project %s selected.\n",project);
    osio::print("Location is now at level <project>.\n");
}
void select_version(const char *version)
{
    std::string p=ini->get("version");
    if(p!="")ini->set("version",p+"/"+version);
    else ini->set("version",version);
    ini->save(BASEMAN_INIPATH);
    osio::print("Version %s selected.\n",version);
    osio::print("Location is now at level <version>.\n");
}
void unselect_base(void)
{
    ini->set("base","");
    ini->save(BASEMAN_INIPATH);
    osio::print("Location is now at level <group>.\n");
}
void unselect_project(void)
{
    int i=str::len(ini->get("project").c_str())-1;
    char *p=(char *)malloc((i+2)*sizeof(char));
    str::cpy(p,ini->get("project").c_str());
    while(i>0 && p[i]!='/')
    {
        p[i]=0;
        i--;
    }
    p[i]=0;
    ini->set("project",p);
    print_level();
    ini->save(BASEMAN_INIPATH);
    free(p);
}
void unselect_version(void)
{
    int i=str::len(ini->get("version").c_str())-1;
    char *p=(char *)malloc((i+2)*sizeof(char));
    str::cpy(p,ini->get("version").c_str());
    while(i>0 && p[i]!='/')
    {
        p[i]=0;
        i--;
    }
    p[i]=0;
    ini->set("version",p);
    print_level();
    ini->save(BASEMAN_INIPATH);
    free(p);
}
void print_level(void)
{
    if(ini->get("version")!="")
    {
        osio::print("Location is now at level <version>.\n");
    }
    else if(ini->get("project")!="")
    {
        osio::print("Location is now at level <project>.\n");
    }
    else if(ini->get("base")!="")
    {
        osio::print("Location is now at level <base>.\n");
    }
    else
    {
        osio::print("Location is now at level <group>.\n");
    }
}
/*********************************************************
*                                                        *
*  create baselist                                       *
*                                                        *
*********************************************************/
void create_baselist(void)
{
    reset();

    FILE *f=file::openfile(BASEMAN_BASELISTPATH,"wb");

    if(!f)
    {
        osio::print("Could'nt create the file baselist.csv.\nCheck permissions and availability.");
        return;
    }
    osio::print(f,"name,path,target,flag,description\n");
    fclose(f);
}
void open_baselist(void)
{
    //--TODO--
    //osexe::myShellExecute(NULL,"open",BASEMAN_BASELISTPATH,NULL,NULL,SW_SHOW);
}

#include "cli/runclp.h"
