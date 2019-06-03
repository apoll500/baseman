/*******************************************************************************
*                                                                              *
*  bm.cpp                                                                      *
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
#include "bm.h"

#include "version.h"
#include "project.h"
#include "base.h"

char *mstr(std::string s)
{
    char *a=(char *)malloc((s.length()+1)*sizeof(char));
    str::cpy(a,s.c_str());
    return a;
}

void Bm::load()
{
    if(getError())
    {
        return;
    }

    if(key_value.c_str()[0]==0)
    {
        osio::xprint("No item selected\nUse \"baseman select\" to select an item.");
        error=2;
        return;
    }

    AbsCsvData *data=load_data(tabname.c_str());
    if(!data)
    {
        osio::xprint("Could'nt open file %s.\n",tabname.c_str());
        error=3;
        return;
    }

    const char *cols[3]={key_name.c_str(),"flag",0};
    const char *vals[3];
    vals[0]=key_value.c_str();
    vals[1]=flag.c_str();
    vals[2]=0;

    AbsCsvRecord *r=data->getRecord(cols,vals);
    if(r!=0)
    {
        set_values(r);
    }
    else
    {
        osio::xprint("Could'nt select record with name='%s' and flag='%s'.\nFile: %s\n",key_value.c_str(),flag.c_str(),tabname.c_str());
        error=4;
    }

    delete data;
}
AbsCsvData *Bm::load_data(const char *filename)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();
    if(data->load(filename))
    {
        osio::xprint("Missing file: %s\n",filename);
        delete data;
        error=3;
        return 0;
    }
    data->useHeader(true);
    return data;
}
AbsCsvData *Bm::load_data_quiet(const char *filename)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();
    if(data->load(filename))
    {
        delete data;
        error=3;
        return 0;
    }
    data->useHeader(true);
    return data;
}
AbsCsvRecord *Bm::get_record(AbsCsvData *data,const char *sfld,const char *name,const char *flag)
{
    const char *cols[3]={sfld,"flag",0};
    const char *vals[3];
    vals[0]=name;
    vals[1]=flag;
    vals[2]=0;
    AbsCsvRecord *record=data->getRecord(cols,vals);
    return record;
}
/*****************************************************************
*                                                                *
*  path()                                                        *
*                                                                *
*****************************************************************/
std::string Bm::tabpath(std::string tab)
{
    if(parent)
    {
        return parent->abspath()+tab;
    }
    else if(plevelitem)
    {
        return plevelitem->abspath()+tab;
    }
    else
    {
        return tab;
    }
}
std::string Bm::abspath()
{
    if(path::pathtype(path.c_str()) & PATH_ABS)
    {
        return path;
    }
    else
    {
        if(parent)
        {
            return parent->abspath()+path;
        }
        else if(plevelitem)
        {
            return plevelitem->abspath()+path;
        }
        else
        {
            return path;
        }
    }
}
std::string Bm::virtual_path()
{
    if(parent)
    {
        return parent->virtual_path()+key_value+"/";
    }
    else if(plevelitem)
    {
        return plevelitem->virtual_path()+key_value+"/";
    }
    else
    {
        return key_value+"/";
    }
}
void Bm::package_export_tabs(std::string export_dir)
{
    osio::xprint(">>>> TAB: %s\n",tabname.c_str());
    osio::xprint("++++ TAB: %s\n",(export_dir+"package"+tabname).c_str());
    file::copyfile((export_dir+"package"+tabname).c_str(),tabname.c_str());
    if(parent)
    {
        return parent->package_export_tabs(export_dir);
    }
    else if(plevelitem)
    {
        return plevelitem->package_export_tabs(export_dir);
    }
    //do_package_export=false;
}
std::string Bm::project_name()
{
    std::string r="";
    if(parent)
    {
        r=parent->project_name();
    }
    else if(plevelitem)
    {
        r=plevelitem->project_name();
    }
    if(parent || plevelitem)
    {
        if(key_name=="name")
        {
            if(r!="")r+="/";
            r+=key_value;
        }
    }
    return r;
}
std::string Bm::project_target()
{
    std::string r="";
    if(parent)
    {
        r=parent->project_target();
    }
    else if(plevelitem)
    {
        r=plevelitem->project_target();
    }
    if(parent || plevelitem)
    {
        if(key_name=="name")
        {
            if(r!="")r+="/";
            r+=target;
        }
    }
    return r;
}
std::string Bm::version_name()
{
    std::string r="";
    if(parent)
    {
        r=parent->version_name();
    }
    else if(plevelitem)
    {
        r=plevelitem->version_name();
    }
    if(key_name=="version")
    {
        if(r!="")r+="/";
        r+=key_value;
    }
    return r;
}
std::string Bm::base_name()
{
    if(parent)
    {
        return parent->base_name();
    }
    else if(plevelitem)
    {
        return plevelitem->base_name();
    }
    return key_value;
}

Bm *Bm::createBm(std::string basename,std::string projname,std::string versname,bool do_download)
{
    Bm *b=0;

    if(basename=="this")basename=base_name();
    if(projname=="this")projname=project_name();

    if(versname!="")
    {
        if(projname!="")
        {
            if(basename!="")
            {
                b=new Version(basename,projname,versname);
            }
            else
            {
                osio::xprint("no base specified.\n");
            }
        }
        else
        {
            osio::xprint("no project specified.\n");
        }
    }
    else if(projname!="")
    {
        if(basename!="")
        {
            b=new Project(basename,projname);
        }
        else
        {
            osio::xprint("no base specified.\n");
        }
    }
    else if(basename!="")
    {
        b=new Base(basename);
    }
    else
    {
        osio::xprint("no base specified.\n");
    }

    if(b->getError())
    {
        delete b;

        //--TODO--
        //Error handling?

        if(do_download)
        {
            std::string downloads_activated=ini->get("main","downloads");
            osio::xprint("downloads_activated=%s\n",downloads_activated.c_str());
            if(downloads_activated=="true")
            {
                //in case of missing project
                //run downloader/installer
                //std::string command="bmsetup install "+basename+"/"+projname+"/"+versname;
                //osio::xprint("> %s\n",command.c_str());
                //system(command.c_str());

                std::string un=ini->get("main","username");
                std::string up=ini->get("main","password");
                std::string package=""+basename+"/"+projname+"/"+versname;
                if(bmsetup_download2(package.c_str(),".baseman/packages/",false,un.c_str(),up.c_str())==1)
                {
                    osio::xprint("[ERROR] bmsetup: Download failed.");
                }
                else bmsetup_install(package.c_str(),".baseman/packages/",true);

                //retry
                Bm *bb=createBm(basename,projname,versname,false);
                if(bb)
                {
                    return bb;
                }
            }
        }

        error=5;
        return 0;
    }

    return b;
}
std::string Bm::targetpath(std::string filetarget)
{
    if(path::pathtype(filetarget.c_str()) & PATH_ABS)
    {
        return filetarget;
    }
    std::string abst=abstarget();
    std::string prot=projecttarget();
    //std::cout << abst << endl << prot << endl;
    if(prot=="")
    {
        abst+=project_name()+"/";
    }
    abst+=filetarget;
    return abst;
}
std::string Bm::filetargetpath(std::string projecttarget,std::string filetarget)
{
    if(path::pathtype(filetarget.c_str()) & PATH_ABS)
    {
        return filetarget;
    }
    return targetpath(projecttarget)+filetarget;
}
std::string Bm::abstarget()
{
    if(path::pathtype(target.c_str()) & PATH_ABS)
    {
        return target;
    }
    else
    {
        if(parent)
        {
            return parent->abstarget()+target;
        }
        else if(plevelitem)
        {
            return plevelitem->abstarget()+target;
        }
        else
        {
            return target;
        }
    }
}
std::string Bm::projecttarget()
{
    if(path::pathtype(target.c_str()) & PATH_ABS)
    {
        if(parent || plevelitem)
        {
            return target;
        }
        else
        {
            return "";
        }
    }
    else
    {
        if(parent)
        {
            return parent->projecttarget()+target;
        }
        else if(plevelitem)
        {
            return plevelitem->projecttarget()+target;
        }
        else
        {
            return "";
        }
    }
}
/*
std::string Bm::webtargetpath(std::string filetarget)
{
    if(filetarget=="")
    {
        return webtarget()+project_name()+"/";
    }
    else if(path::pathtype(filetarget.c_str()) & PATH_ABS)
    {
        return filetarget;
    }
    return webtarget()+filetarget;
}
*/
std::string Bm::webtarget()
{
    if(path::pathtype(target.c_str()) & PATH_ABS)
    {
        return target;
    }
    else
    {
        if(parent)
        {
            return parent->webtarget()+target;
        }
        else if(plevelitem)
        {
            return plevelitem->webtarget()+target;
        }
        else
        {
            return "";
        }
    }
}
/*
std::string Bm::runtarget()
{
    if(run!="")
    {
        return run;
    }
    else
    {
        if(parent)
        {
            return parent->runtarget();
        }
        else if(plevelitem)
        {
            return plevelitem->runtarget();
        }
        else
        {
            return run;
        }
    }
}
*/
std::string Bm::basetarget()
{
    if(path::pathtype(target.c_str()) & PATH_ABS)
    {
        return target;
    }
    else
    {
        if(parent)
        {
            return parent->basetarget();
        }
        else if(plevelitem)
        {
            return plevelitem->basetarget();
        }
        else
        {
            return target;
        }
    }
}
std::string Bm::basepath()
{
    if(parent)
    {
        return parent->basepath();
    }
    else if(plevelitem)
    {
        return plevelitem->basepath();
    }
    else
    {
        return path;
    }
}
std::string Bm::filepath(std::string pathname,std::string filename)
{
    if(path::pathtype(filename.c_str()) & PATH_ABS)
    {
        return filename;
    }
    if(path::pathtype(pathname.c_str()) & PATH_ABS)
    {
        return pathname+filename;
    }
    return fullpath+pathname+filename;
}

std::string Bm::getrun()
{
    if(parent)
    {
        return parent->getrun();
    }
    else if(plevelitem)
    {
        return plevelitem->getrun();
    }
    else
    {
        return "";
    }
}

/*****************************************************************
*                                                                *
*  set()                                                         *
*                                                                *
*****************************************************************/
bool Bm::set_field(const char *tab,const char *sfld,const char *item,const char *name,const char *value,const char *flag)
{
    if(item[0]==0)
    {
        osio::xprint("No item selected\nUse \"baseman select\" to select an item.");
        return false;
    }

    AbsCsvData *data=load_data(tab);
    if(!data)
    {
        osio::xprint("Could'nt open file %s.\n",tab);
        return false;
    }

    AbsCsvRecord *record=get_record(data,sfld,item,flag);
    if(!record)
    {
        osio::xprint("Could'nt select record with name='%s' and flag='%s'.\n",item,flag);
        delete data;
        return false;
    }

    bool b=record->setField(data->getHeaderId(name),value);
    if(b)b=data->save(tab);
    else osio::xprint("Could'nt set field %s to %s.\n",name,value);

    if(!b)osio::xprint("Could'nt save file %s.\n",tab);

    delete data;
    return true;
}
void Bm::set(const char *name,const char *value)
{
    set_field(tabname.c_str(),key_name.c_str(),key_value.c_str(),name,value,flag.c_str());
}
/*****************************************************************
*                                                                *
*  select()                                                      *
*                                                                *
*****************************************************************/
bool Bm::select(const char *tab,const char *key,const char *selected_name,
            void (*select_function)(const char *))
{
    AbsCsvData *data=load_data_quiet(tab);
    if(!data)
    {
        return false;
    }

    int hid_name=data->getHeaderId(key);

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        const char *name=rec[i]->getField(hid_name);
        if(str::cmp(name,selected_name)==0)
        {
            select_function(selected_name);
            delete data;
            return true;
        }
        i++;
    }
    free(rec);
    delete data;
    return false;
}
bool Bm::select_line(const char *tab,const char *key,int selected_line,
            void (*select_function)(const char *))
{
    AbsCsvData *data=load_data_quiet(tab);
    if(!data)
    {
        return false;
    }

    int hid_name=data->getHeaderId(key);

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        if(i==selected_line-1)
        {
            const char *name=rec[i]->getField(hid_name);
            select_function(name);
            delete data;
            return true;
        }
        i++;
    }
    free(rec);
    delete data;
    return false;
}
bool Bm::sel_project(const char *selected_name)
{
    return select((fullpath+"projects.csv").c_str(),"name",selected_name,select_project);
}
bool Bm::sel_version(const char *selected_name)
{
    return select((fullpath+"versions.csv").c_str(),"version",selected_name,select_version);
}
bool Bm::selline_project(int selected_line)
{
    return select_line((fullpath+"projects.csv").c_str(),"name",selected_line,select_project);
}
bool Bm::selline_version(int selected_line)
{
    return select_line((fullpath+"versions.csv").c_str(),"version",selected_line,select_version);
}
/*****************************************************************
*                                                                *
*  list()                                                        *
*                                                                *
*****************************************************************/
void Bm::list(const char *title,const char *tab,const char *key)
{
    AbsCsvData *data=load_data(tab);
    if(!data)
    {
        osio::xprint("Could'nt open file %s.\n",tab);
        return;
    }

    int hid_name=data->getHeaderId(key);

    int col_list[2];
    col_list[0]=hid_name;
    col_list[1]=INT_MAX;

    osio::xprint("\n%s:\n----------------------------------------------------------------------\n",title);

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        osio::xprint("    ");
        if(i<9)osio::xprint(" ");
        if(i<99)osio::xprint(" ");
        osio::xprint("%d: ",i+1);
        rec[i++]->print_ln(stdout,col_list);
    }
    free(rec);
    delete data;
}
void Bm::list_files(const char *title,const char *tab)
{
    AbsCsvData *data=load_data(tab);
    if(!data)
    {
        osio::xprint("Could'nt open file %s.\n",tab);
        return;
    }

    int hid_base=data->getHeaderId("base");
    int hid_proj=data->getHeaderId("project");
    int hid_vers=data->getHeaderId("version");
    int hid_path=data->getHeaderId("path");
    int hid_name=data->getHeaderId("filename");

    int col_list[6];
    col_list[0]=hid_base;
    col_list[1]=hid_proj;
    col_list[2]=hid_vers;
    col_list[3]=hid_path;
    col_list[4]=hid_name;
    col_list[5]=INT_MAX;

    osio::xprint("\n%s:\n----------------------------------------------------------------------\n",title);
    osio::xprint("         base,project,version,path,filename\n");
    osio::xprint("                                           \n");

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        osio::xprint("    ");
        if(i<9)osio::xprint(" ");
        if(i<99)osio::xprint(" ");
        osio::xprint("%d: ",i+1);
        rec[i++]->print_ln(stdout,col_list);
    }
    free(rec);
    delete data;
}
void Bm::list_projects()
{
    list("Projects",(fullpath+"projects.csv").c_str(),"name");
}
void Bm::list_versions()
{
    list("Versions",(fullpath+"versions.csv").c_str(),"version");
}
void Bm::list_files()
{
    list_files("Files",(fullpath+"files.csv").c_str());
}
void Bm::list_existing()
{
    std::string p=fullpath+"projects.csv";
    if(file::testfile(p.c_str()))list("Projects",p.c_str(),"name");
    p=fullpath+"versions.csv";
    if(file::testfile(p.c_str()))list("Versions",p.c_str(),"version");
    p=fullpath+"files.csv";
    if(file::testfile(p.c_str()))list_files("Files",p.c_str());
}
/*****************************************************************
*                                                                *
*  clear()                                                       *
*                                                                *
*****************************************************************/
void Bm::clear(const char *tab,const char *header)
{
    FILE *f=file::openfile(tab,"wb");
    if(!f)
    {
        osio::xprint("Could'nt create the file %s.\nCheck permissions and availability.",tab);
        return;
    }
    osio::print(f,"%s",header);
    fclose(f);
}
void Bm::clear_projects()
{
    clear((fullpath+"projects.csv").c_str(),"name,path,flag,target,run,description");
}
void Bm::clear_versions()
{
    clear((fullpath+"versions.csv").c_str(),"version,path,flag,date,parent,description");
}
void Bm::clear_files()
{
    clear((fullpath+"files.csv").c_str(),"base,project,version,path,filename,flag,target,description\nthis,this,this,files/,,1,,");
}
void Bm::clear_log()
{
    std::string log_filename=get_export_log_file_path();
    clear(log_filename.c_str(),"file,target,date,length");
}
/*****************************************************************
*                                                                *
*  print_path()                                                  *
*                                                                *
*****************************************************************/
void Bm::print_path()
{
    osio::xprint("%s\n",fullpath.c_str());
}
/*****************************************************************
*                                                                *
*  create()                                                      *
*                                                                *
*****************************************************************/
void Bm::create(const char *tab,const char *key,const char *name,const char *path)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();

    data->load(tab);

    data->useHeader(true);
    int hid_name=data->getHeaderId(key);

    AbsCsvRecord **rec=data->getAllRecords("flag","1");
    int i=0;
    while(rec[i]!=0)
    {
        if(strcmp(rec[i++]->getField(hid_name),name)==0)
        {
            osio::xprint("Can't create %s. Object already exists here.",name);
            delete data;
            return;
        }
    }
    free(rec);

    int row=data->addRecord();
    if(!data->setField(row,key,name))osio::xprint("!-");
    if(!data->setField(row,"path",path))osio::xprint("!-");
    if(!data->setField(row,"flag","1"))osio::xprint("!-");

    data->save(tab);

    delete data;
}
void Bm::create_project(const char *name,const char *path)
{
    create((fullpath+"projects.csv").c_str(),"name",name,path);
}
void Bm::create_version(const char *name,const char *path)
{
    create((fullpath+"versions.csv").c_str(),"version",name,path);
}
void Bm::create_file(const char *name,const char *path)
{
    create((fullpath+"files.csv").c_str(),"name",name,path);
}
/*****************************************************************
*                                                                *
*  run()                                                         *
*                                                                *
*****************************************************************/
void Bm::run_web()
{
    std::string webspace=ini->get("main","webspace");
    std::string target_path=abstarget();
    if(project_target()=="")target_path+=project_name();
    if(target_path.substr(0,webspace.size())==webspace)
    {
        std::string url="http://localhost/"
                            +target_path.substr(webspace.size(),std::string::npos)
                            +getrun();
        osio::xprint("open %s\n",url.c_str());
        osexe::myShellExecute(NULL,"open",url.c_str(),NULL,NULL,SW_SHOW);
    }
    else
    {
        osio::xprint("Unknown project type\n");
    }
}
/*****************************************************************
*                                                                *
*  open()                                                        *
*                                                                *
*****************************************************************/
void Bm::open_folder_os()
{
    osexe::myShellExecute(NULL,"open",fullpath.c_str(),NULL,NULL,SW_SHOW);
}
void Bm::open_csv()
{
    std::string p=fullpath+"projects.csv";
    if(file::testfile(p.c_str()))
        osexe::myShellExecute(NULL,"edit",p.c_str(),NULL,NULL,SW_SHOW);

    p=fullpath+"versions.csv";
    if(file::testfile(p.c_str()))
        osexe::myShellExecute(NULL,"edit",p.c_str(),NULL,NULL,SW_SHOW);

    p=fullpath+"files.csv";
    if(file::testfile(p.c_str()))
        osexe::myShellExecute(NULL,"edit",p.c_str(),NULL,NULL,SW_SHOW);
}
all_projects_info Bm::get_all_projects()
{
    all_projects_info a;
    std::string files_tabname=fullpath+"files.csv";
    if(file::testfile(files_tabname.c_str()))
    {
        //check items of files.csv
        //osio::xprint("loading %s\n",files_tabname.c_str());
        //open files.csv file.
        AbsCsvData *data=load_data(files_tabname.c_str());
        if(!data)
        {
            osio::xprint("Could'nt open file %s.\n",files_tabname.c_str());
            return a;
        }
        int hid_base=data->getHeaderId("base");
        int hid_proj=data->getHeaderId("project");
        int hid_vers=data->getHeaderId("version");
        AbsCsvRecord **rec=data->getAllRecords("flag","1");
        int i=0;
        while(rec[i]!=0)
        {
            std::string basename=rec[i]->getField(hid_base);
            std::string projname=rec[i]->getField(hid_proj);
            std::string versname=rec[i]->getField(hid_vers);
            if(basename=="this" && projname=="this" && versname=="this")
            {
                //ignore this here (no other files.csv to load file from here)
            }
            else
            {
                //osio::xprint("load project: %s --> %s --> %s\n",basename.c_str(),projname.c_str(),versname.c_str());
                Bm *b=createBm(basename,projname,versname,true);
                if(b)
                {
                    all_projects_info a2=b->get_all_projects();
                    for(unsigned int k=0;k<a2.project.size();k++)
                    {
                        a.project.push_back(a2.project[k]);
                        //osio::xprint(">>>> | %s | %s | %s |\n",a2.project[k].base.c_str(),a2.project[k].project.c_str(),a2.project[k].version.c_str());
                    }
                }
                else
                {
                    //error
                    osio::xprint("[ERROR] baseman: Project not available.\n[ERROR] baseman: missing %s/%s/%s\n",basename.c_str(),projname.c_str(),versname.c_str());
                }
            }
            i++;
        }
        free(rec);
        delete data;
    }
    //add this project to output
    this_project_info t;
    t.base=base_name();
    t.project=project_name();
    t.version=version_name();
    a.project.push_back(t);

    return a;
}
