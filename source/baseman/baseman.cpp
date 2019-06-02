/*******************************************************************************
*                                                                              *
*  baseman.cpp                                                                 *
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
//baseman/code/v01/files/source/baseman/baseman.cpp

#include "baseman.h"

#include "bm/bm.h"
#include "bm/base.h"
#include "bm/project.h"
#include "bm/version.h"

AbsMultiSettings *ini;

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

    osio::xprint("@%s:/",group);
    if(base[0]!=0)osio::xprint("%s/",base);
    if(project[0]!=0)osio::xprint("%s/",project);
    if(version[0]!=0)osio::xprint("%s/",version);
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
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();

    data->load(BASEMAN_BASELISTPATH,"name,path,target,flag,description");

    data->useHeader(true);
    int hid_name=data->getHeaderId("name");

    AbsCsvRecord **rec=data->getAllRecords("flag",group);
    int i=0;
    while(rec[i]!=0)
    {
        if(strcmp(rec[i++]->getField(hid_name),base)==0)
        {
            osio::xprint("Can't create base %s in group %s. Base already exists in this group.",base,group);
            delete data;
            return;
        }
    }

    int row=data->addRecord();
    if(!data->setField(row,"name",base))osio::xprint("!-");
    if(!data->setField(row,"path",path))osio::xprint("!-");
    if(!data->setField(row,"flag",group))osio::xprint("!-");

    data->save(BASEMAN_BASELISTPATH);

    delete data;
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

    if(group[0]==0)group="1";
    list_group(group);
}
void list_group(const char *group)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();

    data->load(BASEMAN_BASELISTPATH,"name,path,target,flag,description");

    data->useHeader(true);
    int hid_name=data->getHeaderId("name");

    int col_list[2];
    col_list[0]=hid_name;
    col_list[1]=INT_MAX;

    osio::xprint("\nBases:\n----------------------------------------------------------------------\n");

    AbsCsvRecord **rec=data->getAllRecords("flag",group);
    int i=0;
    while(rec && rec[i]!=0)
    {
        osio::xprint("    ");
        rec[i++]->print_ln(stdout,col_list);
    }

    delete data;
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
    osio::xprint("Location is now at level <group>.\n");
}
void select_group(const char *group)
{
    ini->set("group",group);
    ini->set("base","");
    ini->set("project","");
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::xprint("Group %s selected.\n",group);
    osio::xprint("Location is now at level <group>.\n");
}
void select_base(const char *base)
{
    ini->set("base",base);
    ini->set("project","");
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::xprint("Base %s selected.\n",base);
    osio::xprint("Location is now at level <base>.\n");
}
void select_project(const char *project)
{
    std::string p=ini->get("project");
    if(p!="")ini->set("project",p+"/"+project);
    else ini->set("project",project);
    ini->set("version","");
    ini->save(BASEMAN_INIPATH);
    osio::xprint("Project %s selected.\n",project);
    osio::xprint("Location is now at level <project>.\n");
}
void select_version(const char *version)
{
    std::string p=ini->get("version");
    if(p!="")ini->set("version",p+"/"+version);
    else ini->set("version",version);
    ini->save(BASEMAN_INIPATH);
    osio::xprint("Version %s selected.\n",version);
    osio::xprint("Location is now at level <version>.\n");
}
void unselect_base(void)
{
    ini->set("base","");
    ini->save(BASEMAN_INIPATH);
    osio::xprint("Location is now at level <group>.\n");
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
        osio::xprint("Location is now at level <version>.\n");
    }
    else if(ini->get("project")!="")
    {
        osio::xprint("Location is now at level <project>.\n");
    }
    else if(ini->get("base")!="")
    {
        osio::xprint("Location is now at level <base>.\n");
    }
    else
    {
        osio::xprint("Location is now at level <group>.\n");
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
        osio::xprint("Could'nt create the file baselist.csv.\nCheck permissions and availability.");
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

/*********************************************************
*                                                        *
*  prokee module interface                               *
*                                                        *
*********************************************************/
#include "cli/runclp.h"
/**bmc
lp_argc:i
{
    name="argc";
    desc="Die Anzahl Commandline-Parameter.";
}
lp_argv:cpp
{
    name="argv";
    desc="Die Commandline-Parameter mit denen <code>baseman</code> ausgeführt werden soll.";
}
DEF inc_baseman
{
    class="baseman";
}
DEF lp_exprint:func
{
    func_name="print";
    func_direction="IN";
    func_desc="Die Funktion, die für die Ausgabe aufgerufen werden soll, oder @kw.null, falls die Ausgabe an <span class='out'>stdout</span> erfolgen soll.";
    func_return:i="Die Funktion sollte die Anzahl Zeichen zurückgebene, die ausgegeben wurden.<br>Der Rückgabewert wird jedoch von <code>baseman</code> nicht verwendet.";
    func_param:ccp
    {
        name="str";
        desc="Der null-terminierte String, der ausgegeben werden soll. Die Funktion erhält einen UTF-8 String.";
    }
    func_param_classname="external_printer_function";
}
*/
/**bmc
DEF main:POINTER,inc_baseman
{
    function="@this.parent.NAME";
    brief="Führt <code>baseman</code> aus.";
    xinfo="Die Parameter <span class='out'>argc</span>  und <span class='out'>argv</span> sollen so angegeben werden, als würde <code>baseman</code> von der Commandline aufgerufen.";
    param:lp_argc{};
    param:lp_argv{};
    return:i="immer EXIT_SUCCESS (0)";
    docu{THEINTERFACE;};
}
*/
int baseman::main(int argc,char **argv)
{
    runargs(argc,argv);
    return EXIT_SUCCESS;
}
/**bmc
DEF set_printer:POINTER,inc_baseman
{
    function="@this.parent.NAME";
    brief="Setzt die Funktion, die für die Ausgabe aufgerufen werden soll.";
    xinfo="Solange keine Funktion zugeordnet wurde, oder @kw.null als Funktionspointer zugewiesen wurde, erfolgte die Ausgabe an <span class='out'>stdout</span>.";
    param:lp_exprint{};
    return:v="";
    docu{THEINTERFACE;};
}
*/
void baseman::set_printer(int(*print)(const char *))
{
    osio::set_xprint(print);
}
external_print_t osio::external_print=0;
