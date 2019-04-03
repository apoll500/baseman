/*******************************************************************************
*                                                                              *
*  runclp.cpp                                                                  *
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
#include "runclp.h"

#include "../bm/bm.h"
#include "../bm/base.h"
#include "../bm/project.h"
#include "../bm/version.h"

void runargs(int argc,char **argv)
{
    if(argc<2)return;

    if(strcmp(argv[1],"about")==0)
    {
        osio::print(BASEMAN_ABOUT);
    }
    else if(strcmp(argv[1],"license")==0)
    {
        osio::print(LICENSE_GPL3);
    }
    else if(strcmp(argv[1],"end")==0 || strcmp(argv[1],"exit")==0)
    {
        osio::print("Thank's for using baseman!\n");
    }
    else if(strcmp(argv[1],"")==0)
    {
        //nothing to do
    }
    else if(strcmp(argv[1],"docu")==0)
    {
        //show documentation ... not implemented
    }
    else if(strcmp(argv[1],"reset")==0)
    {
        reset();
    }
    else if(strcmp(argv[1],"simu")==0)
    {
        runargs_simu(argc,argv);
    }
    else if(strcmp(argv[1],"export")==0 || strcmp(argv[1],"e")==0)
    {
        runargs_export(argc,argv);
    }
    else if(strcmp(argv[1],"package")==0 || strcmp(argv[1],"p")==0)
    {
        runargs_package(argc,argv);
    }
    else if(strcmp(argv[1],"merge")==0 || strcmp(argv[1],"m")==0)
    {
        runargs_merge(argc,argv);
    }
    else if(strcmp(argv[1],"import")==0)
    {
        runargs_import(argc,argv);
    }
    else if(strcmp(argv[1],"import_p")==0)
    {
        runargs_import_p(argc,argv);
    }
    else if(strcmp(argv[1],"clean")==0)
    {
        runargs_clean(argc,argv);
    }
    else if(strcmp(argv[1],"snapshot")==0)
    {
        runargs_snapshot(argc,argv);
    }
    else if(strcmp(argv[1],"update")==0 || strcmp(argv[1],"u")==0)
    {
        runargs_update(argc,argv);
    }
    else if(strcmp(argv[1],"diff")==0)
    {
        runargs_diff(argc,argv);
    }
    else if(strcmp(argv[1],"base")==0)
    {
        runargs_base(argc,argv);
    }
    else if(strcmp(argv[1],"project")==0)
    {
        runargs_project(argc,argv);
    }
    else if(strcmp(argv[1],"version")==0)
    {
        runargs_version(argc,argv);
    }
    else if(strcmp(argv[1],"clear")==0)
    {
        runargs_clear(argc,argv);
    }
    else if(strcmp(argv[1],"open")==0)
    {
        runargs_open(argc,argv);
    }
    else if(strcmp(argv[1],"goup")==0 || strcmp(argv[1],"up")==0)
    {
        runargs_goup(argc,argv);
    }
    else if(strcmp(argv[1],"list")==0 || strcmp(argv[1],"l")==0)
    {
        runargs_list(argc,argv);
    }
    else if(strcmp(argv[1],"info")==0 || strcmp(argv[1],"i")==0)
    {
        runargs_info(argc,argv);
    }
    else if(strcmp(argv[1],"location")==0 || strcmp(argv[1],"loc")==0)
    {
        print_location();
        osio::print("\n");
    }
    else if(strcmp(argv[1],"path")==0)
    {
        runargs_path(argc,argv);
    }
    else if(strcmp(argv[1],"setgroup")==0)
    {
        runargs_setgroup(argc,argv);
    }
    else if(strcmp(argv[1],"select")==0 || strcmp(argv[1],"s")==0)
    {
        runargs_select(argc,argv);
    }
    else if(strcmp(argv[1],"set")==0)
    {
        runargs_set(argc,argv);
    }
    else if(strcmp(argv[1],"w")==0)
    {
        runargs_setiniblock(argc,argv);
    }
    else if(strcmp(argv[1],"create")==0)
    {
        runargs_create(argc,argv);
    }
    else if(strcmp(argv[1],"run")==0 || strcmp(argv[1],"r")==0)
    {
        runargs_run(argc,argv);
    }
    else if(strcmp(argv[1],"intro")==0)
    {
        runargs_add_intro(argc,argv);
    }
    else if(strcmp(argv[1],"delete_log")==0)
    {
        runargs_delete_log(argc,argv);
    }
    else if(strcmp(argv[1],"plist")==0)
    {
        if(argc==2)
        {
            all_projects_info a;
            Bm *p=bmObject();
            if(p)a=p->get_all_projects(),delete p;
            else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
            for(unsigned int i=0; i<a.project.size(); i++)
            {
                printf("%d) %s --> %s --> %s\n",i,a.project[i].base.c_str(),a.project[i].project.c_str(),a.project[i].version.c_str());
            }
        }
        else
        {
            osio::print("Wrong number of arguments.\n");
        }
    }
    else
    {
        osio::print("Unknown command '%s'.\n",argv[1]);
    }
}

void imode(void)
{
    char command[1024];
    command[0]=0;
    int i,j,h;
    char *opt[5];
    osio::print("baseman  Copyright (C) 2016-2019  Andreas Pollhammer\n");
    osio::print("This program comes with ABSOLUTELY NO WARRANTY.\n");
    osio::print("Type 'about' for more details.\n\n");
    osio::print("Running in interactive mode:\n");
    osio::print("Type 'end' to quit.\n");
    while(strcmp(command,"end")!=0 && strcmp(command,"exit")!=0)
    {
        osio::print("\n");
        print_location();
        osio::print("> ");
        fgets(command,1023,stdin);
        i=0;
        j=2;
        while(command[i]!=0 && j<5)
        {
            if(command[i]==' ')
            {
                opt[j]=&command[i+1];
                command[i]=0;
                j++;
            }
            else if(command[i]=='\n')
            {
                command[i]=0;
            }
            i++;
        }
        opt[0]=&command[i];
        opt[1]=&command[0];
        for(h=j; h<5; h++)opt[h]=&command[i];
        //osio::print("%s(%s,%s)\n",opt[1],opt[2],opt[3]);
        runargs(j,opt);
    }
}

int cli_main(int argc,char **argv)
{
    setbuf(stdout,NULL);

    progdir=dir::getProgramDirectory(argv[0]);

    //ini=new settingsM(((std::string)""+progdir+"status.ini").c_str());

    //ini=AbsMultiSettingsInterface::createMultiSettings();
    ini=new MultiSettings();

    ini->loadfile(((std::string)""+progdir+"status.ini").c_str());

    if(argc==1)
    {
        imode();
    }
    else
    {
        runargs(argc,argv);
    }

    if(ini)delete ini;

    return EXIT_SUCCESS;
}

void runargs_delete_log(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->delete_log_file(),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_export(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_package(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_PACKAGE,
                    ACTION_PACKAGE,
                    ACTION_PACKAGE,

                    ACTION_PACKAGE,
                    ACTION_PACKAGE,
                    ACTION_PACKAGE,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_PACKAGE,
                    ACTION_PACKAGE,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_EXPORT,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_merge(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_IMPORT_BACKUP,
                    ACTION_EXPORT,

                    ACTION_EXPORT_BACKUP,
                    ACTION_CONFLICT_CHANGED,
                    ACTION_EXPORT,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_CONFLICT_NEW,
                    ACTION_EXPORT,
                    ACTION_INFO_NEW
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_import(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_IMPORT_BACKUP,
                    ACTION_DONOTHING,
                    ACTION_IMPORT
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_IMPORT,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_import_p(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_IMPORT_BACKUP,
                    ACTION_DONOTHING,
                    ACTION_IMPORT
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_IMPORT | RUN_EXTMODE,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_clean(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_DELETE_BACKUP,
                    ACTION_DELETE_BACKUP,
                    ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_CLEAN | RUN_EXPORT | RUN_DELDIRS,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_snapshot(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run_snap("",RUN_EXPORT,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_update(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_diff(int argc,char **)
{
    int actions[]= {ACTION_DONOTHING,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_EXPORT,

                    ACTION_DONOTHING,
                    ACTION_DONOTHING,
                    ACTION_DONOTHING,

                    ACTION_EXPORT,
                    ACTION_EXPORT,
                    ACTION_DONOTHING
                   };
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)
        {
            p->run_diff("",RUN_EXPORT,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_simu(int argc,char **argv)
{
    if(argc==2)
    {
        int actions[]= {ACTION_DONOTHING,

                        ACTION_PRINT_INFO,
                        ACTION_PRINT_INFO,
                        ACTION_PRINT_INFO,

                        ACTION_PRINT_INFO,
                        ACTION_PRINT_INFO,
                        ACTION_PRINT_INFO,

                        ACTION_DONOTHING,
                        ACTION_DONOTHING,
                        ACTION_DONOTHING,

                        ACTION_PRINT_INFO,
                        ACTION_PRINT_INFO,
                        ACTION_DONOTHING
                       };
        Bm *p=bmObject();
        if(p)
        {
            p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
            delete p;
        }
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else if(argc==3)
    {
        if(strcmp(argv[2],"source")==0)
        {
            int actions[]= {ACTION_DONOTHING,

                            ACTION_PRINT_SOURCE,
                            ACTION_PRINT_SOURCE,
                            ACTION_PRINT_SOURCE,

                            ACTION_PRINT_SOURCE,
                            ACTION_PRINT_SOURCE,
                            ACTION_PRINT_SOURCE,

                            ACTION_DONOTHING,
                            ACTION_DONOTHING,
                            ACTION_DONOTHING,

                            ACTION_PRINT_SOURCE,
                            ACTION_PRINT_SOURCE,
                            ACTION_DONOTHING
                           };
            Bm *p=bmObject();
            if(p)
            {
                p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
                delete p;
            }
            else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
        }
        else if(strcmp(argv[2],"target")==0)
        {
            int actions[]= {ACTION_DONOTHING,

                            ACTION_PRINT_TARGET,
                            ACTION_PRINT_TARGET,
                            ACTION_PRINT_TARGET,

                            ACTION_PRINT_TARGET,
                            ACTION_PRINT_TARGET,
                            ACTION_PRINT_TARGET,

                            ACTION_DONOTHING,
                            ACTION_DONOTHING,
                            ACTION_DONOTHING,

                            ACTION_PRINT_TARGET,
                            ACTION_PRINT_TARGET,
                            ACTION_DONOTHING
                           };
            Bm *p=bmObject();
            if(p)
            {
                p->run("",RUN_DIRWALK | RUN_EXPORT | RUN_PRINTNEW | RUN_PRINTOBS,actions);
                delete p;
            }
            else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
        }
        else
        {
            osio::print("Wrong arguments.\n");
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_clear(int argc,char **argv)
{
    if(argc==3)
    {
        if(strcmp(argv[2],"baselist")==0)
        {
            create_baselist();
        }
        else if(strcmp(argv[2],"versions")==0)
        {
            Bm *p=bmObject();
            if(p)p->clear_versions(),delete p;
            else osio::print("No versions supposed to be created here.");
        }
        else if(strcmp(argv[2],"projects")==0)
        {
            Bm *p=bmObject();
            if(p)p->clear_projects(),delete p;
            else osio::print("No projects supposed to be created here.");
        }
        else if(strcmp(argv[2],"files")==0)
        {
            Bm *p=bmObject();
            if(p)p->clear_files(),delete p;
            else osio::print("No files supposed to be created here.");
        }
        else
        {
            osio::print("Wrong parameter.\n");
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_goup(int argc,char **)
{
    if(argc==2)
    {
        if(ini->get("version")!="")
        {
            unselect_version();
        }
        else if(ini->get("project")!="")
        {
            unselect_project();
        }
        else if(ini->get("base")!="")
        {
            unselect_base();
        }
        else
        {
            osio::print("Location already at level <group>.\n");
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_list(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->list_existing(),delete p;
        else list_selected_group();
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_run(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->run_web(),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_base(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)osio::print("%s\n",p->base_name().c_str()),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_project(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)osio::print("%s\n",p->project_name().c_str()),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_version(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)osio::print("%s\n",p->version_name().c_str()),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_info(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->info(),delete p;
        else osio::print("Noting selected to display info for.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_path(int argc,char **)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->print_path(),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_open(int argc,char **argv)
{
    if(argc==2)
    {
        Bm *p=bmObject();
        if(p)p->open_folder_os(),delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else if(argc==3)
    {
        if(strcmp(argv[2],"csv")==0)
        {
            Bm *p=bmObject();
            if(p)p->open_csv(),delete p;
            else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
        }
        else if(strcmp(argv[2],"baselist")==0)
        {
            open_baselist();
        }
        else
        {
            osio::print("Wrong parameter.\n");
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_setgroup(int argc,char **argv)
{
    if(argc==3)
    {
        select_group(argv[2]);
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void select_element(Bm *p,const char *arg)
{
    bool b=true;
    if(ini->get("version")!="")
    {
        b=p->sel_version(arg);
    }
    else if(ini->get("project")!="")
    {
        b=p->sel_project(arg);
        if(!b)b=p->sel_version(arg);
    }
    else if(ini->get("base")!="")
    {
        b=p->sel_project(arg);
        if(!b)b=p->sel_version(arg);
    }
    else
    {
        select_base(arg);
    }
    if(!b)
    {
        osio::print("No element with name '%s' found.\n",arg);
    }
}

void select_line(Bm *p,const char *arg)
{
    bool b=true;
    int i=atoi(arg);
    if(ini->get("version")!="")
    {
        b=p->selline_version(i);
    }
    else if(ini->get("project")!="")
    {
        b=p->selline_project(i);
        if(!b)b=p->selline_version(i);
    }
    else if(ini->get("base")!="")
    {
        b=p->selline_project(i);
        if(!b)b=p->selline_version(i);
    }
    else
    {
        //select_base(i);
    }
    if(!b)
    {
        osio::print("could'nt select line %d.\n",i);
    }
}

void select_element_project(Bm *p,const char *arg)
{
    bool b=true;
    if(ini->get("version")!="")
    {
        osio::print("No project supposed to be here.\n");
    }
    else if(ini->get("project")!="")
    {
        b=p->sel_project(arg);
    }
    else if(ini->get("base")!="")
    {
        b=p->sel_project(arg);
    }
    else
    {
        osio::print("No project supposed to be here.\n");
    }
    if(!b)
    {
        osio::print("No element with name '%s' found.\n",arg);
    }
}

void select_element_version(Bm *p,const char *arg)
{
    bool b=true;
    if(ini->get("version")!="")
    {
        b=p->sel_version(arg);
    }
    else if(ini->get("project")!="")
    {
        b=p->sel_version(arg);
    }
    else if(ini->get("base")!="")
    {
        b=p->sel_version(arg);
    }
    else
    {
        osio::print("No version supposed to be here.\n");
    }
    if(!b)
    {
        osio::print("No element with name '%s' found.\n",arg);
    }
}

void select_project_line(Bm *p,const char *arg)
{
    bool b=true;
    int i=atoi(arg);
    if(ini->get("version")!="")
    {
        osio::print("No project supposed to be here.\n");
    }
    else if(ini->get("project")!="")
    {
        b=p->selline_project(i);
    }
    else if(ini->get("base")!="")
    {
        b=p->selline_project(i);
    }
    else
    {
        osio::print("No project supposed to be here.\n");
    }
    if(!b)
    {
        osio::print("could'nt select line %d.\n",i);
    }
}

void select_version_line(Bm *p,const char *arg)
{
    bool b=true;
    int i=atoi(arg);
    if(ini->get("version")!="")
    {
        b=p->selline_version(i);
    }
    else if(ini->get("project")!="")
    {
        b=p->selline_version(i);
    }
    else if(ini->get("base")!="")
    {
        b=p->selline_version(i);
    }
    else
    {
        osio::print("No version supposed to be here.\n");
    }
    if(!b)
    {
        osio::print("could'nt select line %d.\n",i);
    }
}

void runargs_select(int argc,char **argv)
{
    if(argc==3)
    {
        Bm *p=bmObject();
        if(p)select_element(p,argv[2]),delete p;
        else select_base(argv[2]);
    }
    else if(argc==4)
    {
        Bm *p=bmObject();
        if(strcmp(argv[2],"project")==0)
        {
            if(p)select_element_project(p,argv[3]);
        }
        else if(strcmp(argv[2],"version")==0)
        {
            if(p)select_element_version(p,argv[3]);
        }
        else if(strcmp(argv[2],"line")==0)
        {
            if(p)select_line(p,argv[3]);
        }
        else if(strcmp(argv[2],"file")==0)
        {
            //select_file(argv[3]);
        }
        else
        {
            osio::print("Unknown type '%s'.\n",argv[2]);
        }
        if(p)delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else if(argc==5)
    {
        Bm *p=bmObject();
        if(strcmp(argv[3],"line")==0)
        {
            if(strcmp(argv[2],"project")==0)
            {
                if(p)select_project_line(p,argv[4]);
            }
            else if(strcmp(argv[2],"version")==0)
            {
                if(p)select_version_line(p,argv[4]);
            }
            else if(strcmp(argv[2],"file")==0)
            {
                //select_file(argv[3]);
            }
            else
            {
                osio::print("Unknown type '%s'.\n",argv[2]);
            }
        }
        else
        {
            osio::print("Unknown argument '%s'.\n",argv[3]);
        }
        if(p)delete p;
        else osio::print("Noting selected.\nUse \"baseman select <basename>\" to select a base.");
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_set(int argc,char **argv)
{
    if(argc>=4)
    {
        std::string pstr="";
        int i=3;
        while(i<argc)
        {
            pstr+=argv[i++];
            if(i<argc)pstr+=" ";
        }
        if(strcmp(argv[2],"webspace")==0)
        {
            ini->set("webspace",pstr.c_str());
            ini->save("status.ini");
        }
        else if(strcmp(argv[2],"browser")==0)
        {
            ini->set("browser",pstr.c_str());
            ini->save("status.ini");
        }
        else if(strcmp(argv[2],"fileman")==0)
        {
            ini->set("fileman",pstr.c_str());
            ini->save("status.ini");
        }
        else if(strcmp(argv[2],"editor")==0)
        {
            ini->set("editor",pstr.c_str());
            ini->save("status.ini");
        }
        else if(strcmp(argv[2],"sblock")==0)
        {
            ini->setSelectedDefBlockName(pstr.c_str());
            ini->save("status.ini");
        }
        else if(strcmp(argv[2],"ignore")==0)
        {
            ini->set("ignore",pstr.c_str());
            ini->save("status.ini");
        }
        else
        {
            Bm *p=bmObject();
            if(p)p->set(argv[2],pstr.c_str()),delete p;
            else osio::print("Noting to store here.");
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_setiniblock(int argc,char **argv)
{
    if(argc==3)
    {
        ini->setSelectedDefBlockName(argv[2]);
        ini->save("status.ini");
    }
    else if(argc==2)
    {
        printf("%s\n",ini->getSelectedDefBlockName().c_str());
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_add_intro(int argc,char **argv)
{
    if(argc==3)
    {
        system("baseman simu target > target_list.txt");
        std::string command=(std::string)"add_intro target_list.txt intro_"+argv[2]+".txt "+ini->get("project")+" "+argv[2];
        system(command.c_str());
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}

void runargs_create(int argc,char **argv)
{
    if(argc==5)
    {
        if(ini->get("version")!="")
        {
            if(strcmp(argv[2],"version")==0)
            {
                Version p;
                p.create_version(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"file")==0)
            {
                Version p;
                p.create_file(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"base")==0)
            {
                create_base0(argv[3],argv[4]);
            }
            else
            {
                osio::print("Object of type %s can't be created here.",argv[2]);
            }
        }
        else if(ini->get("project")!="")
        {
            if(strcmp(argv[2],"version")==0)
            {
                Project p;
                p.create_version(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"project")==0)
            {
                Project p;
                p.create_project(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"file")==0)
            {
                Project p;
                p.create_file(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"base")==0)
            {
                create_base0(argv[3],argv[4]);
            }
            else
            {
                osio::print("Object of type %s can't be created here.",argv[2]);
            }
        }
        else if(ini->get("base")!="")
        {
            if(strcmp(argv[2],"version")==0)
            {
                Base p;
                p.create_version(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"project")==0)
            {
                Base p;
                p.create_project(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"file")==0)
            {
                Base p;
                p.create_file(argv[3],argv[4]);
            }
            else if(strcmp(argv[2],"base")==0)
            {
                create_base0(argv[3],argv[4]);
            }
            else
            {
                osio::print("Object of type %s can't be created here.",argv[2]);
            }
        }
        else
        {
            if(strcmp(argv[2],"base")==0)
            {
                create_base0(argv[3],argv[4]);
            }
            else
            {
                osio::print("Object of type %s can't be created here.",argv[2]);
            }
        }
    }
    else
    {
        osio::print("Wrong number of arguments.\n");
    }
}
