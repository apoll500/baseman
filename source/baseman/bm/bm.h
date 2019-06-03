/*******************************************************************************
*                                                                              *
*  bm.h                                                                        *
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
#ifndef BASEMAN_BM_H
#define BASEMAN_BM_H

#include <string>

#define RUN_DIRWALK 1
#define RUN_EXPORT 2
#define RUN_IMPORT 4
#define RUN_CLEAN 8
#define RUN_PRINTOBS 16
#define RUN_PRINTNEW 32
#define RUN_CONSLOG 64
#define RUN_DELDIRS 128
#define RUN_MKEMPTYDIRS 256
#define RUN_EXTMODE 512

void select_project(const char *project);
void select_version(const char *version);

#include "../baseman.h"
#include "macros/macros.h"
#include "wwrap/osexe.h"

extern AbsMultiSettings *ini;

char *mstr(std::string s);

//classes for experimental extended import
class this_project_info
{
public:
    std::string base;
    std::string project;
    std::string version;
};
class all_projects_info
{
public:
    std::vector<this_project_info> project;
};

/*********************************************************************
*                                                                    *
*  CondCopyControllers                                               *
*                                                                    *
*********************************************************************/
template<class T> class BmCondCopyControl;
template<class T> class MergeControler;
/*********************************************************************
*                                                                    *
*  Bm                                                                *
*                                                                    *
*********************************************************************/
class Bm
{
protected:
    std::string key_name;
    std::string key_value;
    std::string tabtype;
    std::string tabname;
    std::string flag;
    Bm *plevelitem;
    Bm *parent;
    std::string path;
    std::string target;
    std::string desc;
    bool do_package_export;
    int error;
public:
    std::string fullpath;
    virtual ~Bm()
    {
        //do_package_export=false;
    }
    virtual int getError()
    {
        if(error)return error;
        if(parent)
        {
            return parent->getError();
        }
        else if(plevelitem)
        {
            return plevelitem->getError();
        }
        return 0;
    }
    virtual void set_do_package_export(bool b)
    {
        do_package_export=b;
    }
    virtual std::string get_export_log_file_path()
    {
        std::string p=(std::string)".baseman/export/"+virtual_path()+"log.csv";
        return p;
    }
    virtual std::string get_snapshot_log_file_path()
    {
        std::string p=(std::string)".baseman/snapshot/"+virtual_path()+"log.csv";
        return p;
    }
    virtual void delete_log_file()
    {
        std::string log_filename=get_export_log_file_path();
        file::remove(log_filename.c_str());
    }
    virtual void set_values(AbsCsvRecord *r)=0;
    virtual void info()=0;
    void load();
    AbsCsvData *load_data(const char *filename);
    AbsCsvData *load_data_quiet(const char *filename);
    AbsCsvRecord *get_record(AbsCsvData *data,const char *sfld,const char *name,const char *flag);
    /*****************************************************************
    *                                                                *
    *  path()                                                        *
    *                                                                *
    *****************************************************************/
    void package_export_tabs(std::string export_dir);
    std::string tabpath(std::string tab);
    std::string abspath();
    std::string virtual_path();
    std::string project_name();
    std::string project_target();
    std::string version_name();
    std::string base_name();
    Bm *createBm(std::string basename,std::string projname,std::string versname,bool download);
    std::string targetpath(std::string filetarget);
    std::string filetargetpath(std::string projecttarget,std::string filetarget);
    std::string abstarget();
    std::string projecttarget();
    std::string webtarget();
    //std::string runtarget();
    std::string basetarget();
    std::string basepath();
    std::string filepath(std::string pathname,std::string filename);
    /*****************************************************************
    *                                                                *
    *  set()                                                         *
    *                                                                *
    *****************************************************************/
    bool set_field(const char *tab,const char *sfld,const char *item,const char *name,const char *value,const char *flag);
    void set(const char *name,const char *value);
    /*****************************************************************
    *                                                                *
    *  select()                                                      *
    *                                                                *
    *****************************************************************/
    bool select(const char *tab,const char *key,const char *selected_name,void (*select_function)(const char *));
    bool select_line(const char *tab,const char *key,int selected_line,void (*select_function)(const char *));
    bool sel_project(const char *selected_name);
    bool sel_version(const char *selected_name);
    bool selline_project(int selected_line);
    bool selline_version(int selected_line);
    /*****************************************************************
    *                                                                *
    *  list()                                                        *
    *                                                                *
    *****************************************************************/
    void list(const char *title,const char *tab,const char *key);
    void list_files(const char *title,const char *tab);
    void list_projects();
    void list_versions();
    void list_files();
    void list_existing();
    /*****************************************************************
    *                                                                *
    *  clear()                                                       *
    *                                                                *
    *****************************************************************/
    void clear(const char *tab,const char *header);
    void clear_projects();
    void clear_versions();
    void clear_files();
    void clear_log();
    /*****************************************************************
    *                                                                *
    *  print_path()                                                  *
    *                                                                *
    *****************************************************************/
    void print_path();
    /*****************************************************************
    *                                                                *
    *  create()                                                      *
    *                                                                *
    *****************************************************************/
    void create(const char *tab,const char *key,const char *name,const char *path);
    void create_project(const char *name,const char *path);
    void create_version(const char *name,const char *path);
    void create_file(const char *name,const char *path);
    /*****************************************************************
    *                                                                *
    *  run()                                                         *
    *                                                                *
    *****************************************************************/
    void run_web();
    /*****************************************************************
    *                                                                *
    *  open()                                                        *
    *                                                                *
    *****************************************************************/
    void open_folder_os();
    void open_csv();
    /*****************************************************************
    *                                                                *
    *  export()                                                      *
    *                                                                *
    *****************************************************************/
    template<class T> void copy_item(std::string source_path,std::string target_path,BmCondCopyControl<T> *cc);
    template<class T> void run(const T *target_path_overwrite,int flags,int *actions);
    template<class T> void run_snap(const T *target_path_overwrite,int flags,int *actions);
    template<class T> void run_diff(const T *target_path_overwrite,int flags,int *actions);
    template<class T> void runsimulation(const T *target_path_overwrite);
    template<class T> void runsimulation_source(const T *target_path_overwrite);
    template<class T> void runsimulation_target(const T *target_path_overwrite);
    template<class T> void runexport(const T *target_path_overwrite,int flags,int *actions,MergeControler<T> *cc);
    template<class T> void runexport(std::string target_path_overwrite,BmCondCopyControl<T> *cc);
    template<class T> void runexport(const char *tab,std::string target_path_overwrite,BmCondCopyControl<T> *cc);
    virtual std::string getrun();
    all_projects_info get_all_projects();
};

/*********************************************************************
*                                                                    *
*  CondCopyControllers                                               *
*                                                                    *
*********************************************************************/
#include "../controllers/MergeControler.h"

/*****************************************************************
*                                                                *
*  export()                                                      *
*                                                                *
*****************************************************************/
template<class T> void Bm::copy_item(std::string source_path,std::string target_path,BmCondCopyControl<T> *cc)
{
    //osio::xprint("-------------------------------------------\ncopy_item()\n");
    //osio::xprint("von:  %s\nnach: %s\n",source_path.c_str(),target_path.c_str());

    if(path::pathtype(source_path.c_str()) & PATH_DIR)
    {
        if(path::pathtype(target_path.c_str()) & PATH_DIR)
        {
            //--TODO-- check for missing directories
            dir::copydir(target_path.c_str(),source_path.c_str(),cc);
        }
        else
        {
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            osio::xprint("Cannot copy directory to file.\n");
            osio::xprint("DIR: %s\n",source_path.c_str());
            osio::xprint("TO:  %s\n",target_path.c_str());
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        }
    }
    else
    {
        //--TODO-- add cases
        //--TODO-- check for missing files
        file::copyfile(target_path.c_str(),source_path.c_str(),cc);
    }
}
template<class T> void Bm::run(const T *target_path_overwrite,int flags,int *actions)
{
    std::string log_filename=get_export_log_file_path();
    MergeControler<T> cc(log_filename.c_str(),actions,flags);
    runexport(target_path_overwrite,flags,actions,&cc);
}
template<class T> void Bm::run_snap(const T *target_path_overwrite,int flags,int *actions)
{
    std::string snap_filename=get_snapshot_log_file_path();
    MergeControler<T> cc(snap_filename.c_str(),actions,flags);
    runexport(target_path_overwrite,flags,actions,&cc);
}
template<class T> void Bm::run_diff(const T *target_path_overwrite,int flags,int *actions)
{
    std::string snap_filename=get_snapshot_log_file_path();
    std::string log_filename=get_export_log_file_path();
    MergeControler<T> cc(snap_filename.c_str(),log_filename.c_str(),actions,flags);
    runexport(target_path_overwrite,flags,actions,&cc);
}
template<class T> void Bm::runexport(const T *target_path_overwrite,int flags,int *actions,MergeControler<T> *cc)
{
    std::string ign=ini->get("ignore")+";";
    unsigned int i=0,p=0;
    while(ign.c_str()[i])
    {
        if(ign.c_str()[i]==';')
        {
            if(i>p)cc->add_ign(ign.substr(p,i-p));
            p=i+1;
        }
        i++;
    }

    for(i=0;i<13;i++)
    {
        if(actions[i]==ACTION_PACKAGE)
        {
            do_package_export=true;
            break;
        }
    }
    if(flags & RUN_DIRWALK || flags & RUN_IMPORT || flags & RUN_PRINTNEW || actions[12]!=ACTION_DONOTHING)
        dir::walktree(targetpath("").c_str(),cc);

    if(flags & RUN_EXPORT)
        runexport(target_path_overwrite,cc);

    if(flags & RUN_IMPORT)
    {
        if(flags & RUN_EXTMODE)
        {
            all_projects_info a;
            a=get_all_projects();
            /*
            for(unsigned int i=0;i<a.project.size();i++)
            {
                osio::xprint("%d) %s --> %s --> %s\n",i,a.project[i].base.c_str(),a.project[i].project.c_str(),a.project[i].version.c_str());
            }
            */
            cc->importfiles_extmode(targetpath("").c_str(),10,a);
        }
        else
        {
            cc->importfiles(fullpath.c_str(),targetpath("").c_str());
        }
    }
}
template<class T> void Bm::runexport(std::string target_path_overwrite,BmCondCopyControl<T> *cc)
{
    std::string p=fullpath+"files.csv";
    if(file::testfile(p.c_str()))
    {
        runexport(p.c_str(),target_path_overwrite,cc);
    }
    else
    {
        std::string target_path;
        if(target_path_overwrite=="")
        {
            target_path=targetpath("");
        }
        else
        {
            target_path=target_path_overwrite;
        }

        std::string source_path=fullpath;

        copy_item(source_path,target_path,cc);
    }
}
template<class T> void Bm::runexport(const char *tab,std::string target_path_overwrite,BmCondCopyControl<T> *cc)
{
    AbsCsvData *data=load_data(tab);
    if(!data)
    {
        osio::xprint("Could'nt open file %s.\n",tab);
        cc->setError(5);
        return;
    }

    if(do_package_export)package_export_tabs(ini->get("webspace"));
    if(do_package_export)
    {
        osio::xprint(">>>> TAB: %s\n",tab);
        osio::xprint("++++ TAB: %s\n",(ini->get("webspace")+"package"+tab).c_str());
        file::copyfile((ini->get("webspace")+"package"+tab).c_str(),tab);
    }

    int hid_base=data->getHeaderId("base");
    int hid_proj=data->getHeaderId("project");
    int hid_vers=data->getHeaderId("version");
    int hid_path=data->getHeaderId("path");
    int hid_file=data->getHeaderId("filename");
    int hid_targ=data->getHeaderId("target");
    int hid_desc=data->getHeaderId("description");

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        std::string basename=rec[i]->getField(hid_base);
        std::string projname=rec[i]->getField(hid_proj);
        std::string versname=rec[i]->getField(hid_vers);
        std::string pathname=rec[i]->getField(hid_path);
        std::string filename=rec[i]->getField(hid_file);
        std::string targname=rec[i]->getField(hid_targ);
        std::string descript=rec[i]->getField(hid_desc);

        if(!(pathname=="" || (path::pathtype(pathname.c_str()) & PATH_DIR)))
        {
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            osio::xprint("Ignoring record.\n");
            osio::xprint("file  = %s\n",tab);
            osio::xprint("line  = %d\n",i);
            osio::xprint("field = path\n");
            osio::xprint("value = %s\n",pathname.c_str());
            osio::xprint("This should be empty or a directory, not a file.\n");
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            i++;
            continue;
        }

        if(path::pathtype(filename.c_str()) & PATH_ABS)
        {
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            osio::xprint("Ignoring record.\n");
            osio::xprint("file  = %s\n",tab);
            osio::xprint("line  = %d\n",i);
            osio::xprint("field = filename\n");
            osio::xprint("value = %s\n",filename.c_str());
            osio::xprint("This cannot be an absolute path.\n");
            osio::xprint("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
            i++;
            continue;
        }

        std::string target_path;
        if(target_path_overwrite=="")
        {
            target_path=targetpath(targname);
        }
        else
        {
            if(path::pathtype(targname.c_str()) & PATH_ABS)
            {
                target_path=targname;
            }
            else
            {
                target_path=target_path_overwrite+targname;
            }
        }

        std::string source_path=filepath(pathname,filename);

        if(basename=="this" && projname=="this" && versname=="this")
        {
            cc->setBm(this);
            if(path::pathtype(target_path.c_str()) & PATH_DIR)target_path+=filename;
            copy_item(source_path,target_path,cc);
        }
        else
        {
            Bm *b=createBm(basename,projname,versname,true);
            if(b)
            {
                b->set_do_package_export(do_package_export);
                cc->setBm(b);
                if(pathname=="" && filename=="")
                {
                    b->runexport(target_path,cc);
                }
                else
                {
                    source_path=b->filepath(pathname,filename);
                    if(path::pathtype(target_path.c_str()) & PATH_DIR)target_path+=filename;
                    copy_item(source_path,target_path,cc);
                }
                delete b;
            }
            else
            {
                cc->setError(5);
                osio::xprint("[ERROR] baseman: Project not available.\n[ERROR] baseman: missing %s/%s/%s\n",basename.c_str(),projname.c_str(),versname.c_str());
            }
        }
        i++;
    }
    free(rec);
    delete data;
}

#endif
