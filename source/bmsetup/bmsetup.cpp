/*******************************************************************************
*                                                                              *
*  bmsetup.cpp                                                                 *
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
#include "bmsetup.h"
template<class T> class TW_export:public TreeWalkCallback<T>
{
public:
    virtual bool tw_callback(const T *path)
    {
        if(path::pathtype(path) & PATH_DIR)
        {
            //do nothing
        }
        else
        {
            if(str::cmp(path::onopath(path),".")==0 || str::cmp(path::onopath(path),"..")==0)
            {
                return true;
            }
            const char *name=path::onopath(path);
            if(str::cmp(name,"projects.csv")==0)
            {
                printf("export %s\n",path);
                export_projects(path);
            }
            else if(str::cmp(name,"versions.csv")==0)
            {
                printf("export %s\n",path);
                export_versions(path);
            }
        }
        return true;
    }
};
template<class T> class TW_import:public TreeWalkCallback<T>
{
public:
    virtual bool tw_callback(const T *path)
    {
        if(path::pathtype(path) & PATH_DIR)
        {
            //do nothing
        }
        else
        {
            if(str::cmp(path::onopath(path),".")==0 || str::cmp(path::onopath(path),"..")==0)
            {
                return true;
            }
            if(strman::findsubstr(".git/",path)!=strlen(path))
            {
                return true;
            }
            const char *suffix=path::sxopath(path);
            if(str::cmp(suffix,"info")==0)
            {
                printf("import %s\n",path);
                import_info(path);
            }
        }
        return true;
    }
};
int run_script(const char *baseman_project_path,const char *package_path,const char *run_token)
{
    char *unique_package_name=construct_package_path(baseman_project_path,"","");
    char *command=(char *)malloc((strlen(unique_package_name)+strlen(package_path)+strlen(run_token)+32)*sizeof(char));
    sprintf(command,BMSETUP_INSTALLATION_PATH"bmsetup_%s.sh %s %s",run_token,package_path,unique_package_name);
    system(command);
    free(command);
    free(unique_package_name);
    return 0;
}
int run_script2(const char *baseman_project_path,const char *package_path,const char *run_token,const char *username,const char *userpass)
{
    char *unique_package_name=construct_package_path(baseman_project_path,"","");
    char *command=(char *)malloc((strlen(unique_package_name)+strlen(package_path)+strlen(run_token)+32)*sizeof(char));
    char *un=base64::encode(username);
    char *up=base64::encode(userpass);
    sprintf(command,BMSETUP_INSTALLATION_PATH"bmsetup_%s.sh %s %s %s %s",run_token,package_path,unique_package_name,un,up);
    free(un);
    free(up);
    system(command);
    free(command);
    free(unique_package_name);
    return 0;
}
int download(const char *baseman_project_path,const char *package_path,bool update)
{
    int ret=0;
    printf("downloading %s:\n",baseman_project_path);
    char *base_path;
    char *project_path;
    char *version_path;
    char **loc=get_all_paths(baseman_project_path,&base_path,&project_path,&version_path);
    if(base_path)
    {
        char *plocal=construct_package_path(baseman_project_path,package_path,".tar.gz");
        if(!file::testfile(plocal))
        {
            run_script(baseman_project_path,package_path,"download");
        }
        else
        {
            if(update)
            {
                file::remove(plocal);
                char *filename=construct_package_path(baseman_project_path,package_path,".tar.gz.sig");
                file::remove(filename);
                free(filename);
                run_script(baseman_project_path,package_path,"download");
            }
        }
        if(!file::testfile(plocal))
        {
            ret=1;
        }
        free(plocal);
    }
    if(version_path)free(version_path);
    if(project_path)free(project_path);
    if(base_path)free(base_path);
    strman::explode_free(loc);
    return ret;
}
int download2(const char *baseman_project_path,const char *package_path,bool update,const char *username,const char *userpass)
{
    int ret=0;
    printf("downloading %s:\n",baseman_project_path);
    char *base_path;
    char *project_path;
    char *version_path;
    char **loc=get_all_paths(baseman_project_path,&base_path,&project_path,&version_path);
    if(base_path)
    {
        char *plocal=construct_package_path(baseman_project_path,package_path,".tar.gz");
        if(!file::testfile(plocal))
        {
            run_script2(baseman_project_path,package_path,"download",username,userpass);
        }
        else
        {
            if(update)
            {
                run_script2(baseman_project_path,package_path,"download",username,userpass);
            }
        }
        if(!file::testfile(plocal))
        {
            ret=1;
        }
        free(plocal);
    }
    if(version_path)free(version_path);
    if(project_path)free(project_path);
    if(base_path)free(base_path);
    strman::explode_free(loc);
    return ret;
}
int exporter()
{
    TW_export<char> tw;
    dir::walktree("./",&tw);
    return 0;
}
int importer()
{
    TW_import<char> tw;
    dir::walktree("./",&tw);
    return 0;
}
int exporter2(const char *baseman_project_path)
{
    TW_export<char> tw;
    char *base_path;
    char *project_path;
    char *version_path;
    char **loc=get_all_paths(baseman_project_path,&base_path,&project_path,&version_path);
    if(base_path)
    {
        dir::walktree(version_path,&tw);
    }
    if(version_path)free(version_path);
    if(project_path)free(project_path);
    if(base_path)free(base_path);
    strman::explode_free(loc);
    return 0;
}
int importer2(const char *baseman_project_path)
{
    TW_import<char> tw;
    char *base_path;
    char *project_path;
    char *version_path;
    char **loc=get_all_paths(baseman_project_path,&base_path,&project_path,&version_path);
    if(base_path)
    {
        dir::walktree(version_path,&tw);
    }
    if(version_path)free(version_path);
    if(project_path)free(project_path);
    if(base_path)free(base_path);
    strman::explode_free(loc);
    return 0;
}
int import_info(const char *infopath)
{
    AbsSettings *s=AbsSettingsInterface::createSettings();
    if(!s->loadfile(infopath))
    {
        delete s;
        return 1;
    }
    int n=s->getDefBlockCount();
    for(int i=0;i<n;i++)
    {
        std::string blockname=s->getNextDefBlockName();
        const char *b=blockname.c_str();
        if(strcmp(b,"project")==0)
        {
            AbsCsvData *data=AbsCsvDataInterface::createCsvData();
            char *csvpath=path::dnopath(infopath);
            csvpath=(char *)realloc(csvpath,(strlen(csvpath)+16)*sizeof(char));
            strcat(csvpath,"projects.csv");
            data->load(csvpath,"name,path,flag,target,run,description");
            data->useHeader(true);
            int name_id=data->getHeaderId("name");
            int path_id=data->getHeaderId("path");
            int flag_id=data->getHeaderId("flag");
            int targ_id=data->getHeaderId("target");
            int rrun_id=data->getHeaderId("run");
            int desc_id=data->getHeaderId("description");
            std::string name=s->get("project","name");
            std::string path=s->get("project","path");
            std::string flag=s->get("project","flag");
            std::string targ=s->get("project","target");
            std::string rrun=s->get("project","run");
            std::string desc=s->get("project","description");
            AbsCsvRecord **rec=data->getAllRecords("name",name.c_str());
            bool record_set=false;
            if(rec)
            {
                if(csv::record_count(rec)==1)
                {
                    rec[0]->setField(name_id,name.c_str());
                    rec[0]->setField(path_id,path.c_str());
                    rec[0]->setField(flag_id,flag.c_str());
                    rec[0]->setField(targ_id,targ.c_str());
                    rec[0]->setField(rrun_id,rrun.c_str());
                    rec[0]->setField(desc_id,desc.c_str());
                    record_set=true;
                }
                else if(csv::record_count(rec)>1)
                {
                    printf("ERROR: check %s, see %s\n",csvpath,infopath);
                }
            }
            free(rec);
            if(!record_set)
            {
                int row=data->addRecord(6);
                data->setField(row,name_id,name.c_str());
                data->setField(row,path_id,path.c_str());
                data->setField(row,flag_id,flag.c_str());
                data->setField(row,targ_id,targ.c_str());
                data->setField(row,rrun_id,rrun.c_str());
                data->setField(row,desc_id,desc.c_str());
            }
            data->save(csvpath);
            free(csvpath);
            delete data;
        }
        else if(strcmp(b,"version")==0)
        {
            AbsCsvData *data=AbsCsvDataInterface::createCsvData();
            char *csvpath=path::dnopath(infopath);
            csvpath=(char *)realloc(csvpath,(strlen(csvpath)+16)*sizeof(char));
            strcat(csvpath,"versions.csv");
            data->load(csvpath,"version,path,flag,date,description");
            data->useHeader(true);
            int vers_id=data->getHeaderId("version");
            int path_id=data->getHeaderId("path");
            int flag_id=data->getHeaderId("flag");
            int date_id=data->getHeaderId("date");
            int desc_id=data->getHeaderId("description");
            std::string vers=s->get("version","version");
            std::string path=s->get("version","path");
            std::string flag=s->get("version","flag");
            std::string date=s->get("version","date");
            std::string desc=s->get("version","description");
            AbsCsvRecord **rec=data->getAllRecords("version",vers.c_str());
            bool record_set=false;
            if(rec)
            {
                if(csv::record_count(rec)==1)
                {
                    rec[0]->setField(vers_id,vers.c_str());
                    rec[0]->setField(path_id,path.c_str());
                    rec[0]->setField(flag_id,flag.c_str());
                    rec[0]->setField(date_id,date.c_str());
                    rec[0]->setField(desc_id,desc.c_str());
                    record_set=true;
                }
                else if(csv::record_count(rec)>1)
                {
                    printf("ERROR: check %s, see %s\n",csvpath,infopath);
                }
            }
            free(rec);
            if(!record_set)
            {
                int row=data->addRecord(5);
                data->setField(row,vers_id,vers.c_str());
                data->setField(row,path_id,path.c_str());
                data->setField(row,flag_id,flag.c_str());
                data->setField(row,date_id,date.c_str());
                data->setField(row,desc_id,desc.c_str());
                printf("version=%s\n",vers.c_str());
            }
            data->save(csvpath);
            free(csvpath);
            delete data;
        }
    }
    delete s;
    return 0;
}
int export_projects(const char *csvpath)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();
    data->load(csvpath);
    data->useHeader(true);
    int name_id=data->getHeaderId("name");
    int path_id=data->getHeaderId("path");
    int flag_id=data->getHeaderId("flag");
    int targ_id=data->getHeaderId("target");
    int rrun_id=data->getHeaderId("run");
    int desc_id=data->getHeaderId("description");
    AbsCsvRecord **rec=data->getAllRecords();
    if(rec)
    {
        int rec_count=csv::record_count(rec);
        for(int i=0;i<rec_count;i++)
        {
            const char *name=rec[i]->getField_f(name_id);
            const char *path=rec[i]->getField_f(path_id);
            const char *flag=rec[i]->getField_f(flag_id);
            const char *targ=rec[i]->getField_f(targ_id);
            const char *rrun=rec[i]->getField_f(rrun_id);
            const char *desc=rec[i]->getField_f(desc_id);
            if(name[0])
            {
                AbsSettings *s=AbsSettingsInterface::createSettings();
                s->set("project","name",name);
                s->set("project","path",path);
                s->set("project","flag",flag);
                s->set("project","target",targ);
                s->set("project","run",rrun);
                s->set("project","description",desc);
                char *a=path::dnopath(csvpath);
                a=(char *)realloc(a,(strlen(a)+strlen(name)+10)*sizeof(char));
                strcat(a,name);
                strcat(a,".info");
                s->save2(a);
                free(a);
                delete s;
            }
        }
    }
    free(rec);
    delete data;
    return 0;
}
int export_versions(const char *csvpath)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();
    data->load(csvpath);
    data->useHeader(true);
    int vers_id=data->getHeaderId("version");
    int path_id=data->getHeaderId("path");
    int flag_id=data->getHeaderId("flag");
    int date_id=data->getHeaderId("date");
    int desc_id=data->getHeaderId("description");
    AbsCsvRecord **rec=data->getAllRecords();
    if(rec)
    {
        int rec_count=csv::record_count(rec);
        for(int i=0;i<rec_count;i++)
        {
            const char *vers=rec[i]->getField_f(vers_id);
            const char *path=rec[i]->getField_f(path_id);
            const char *flag=rec[i]->getField_f(flag_id);
            const char *date=rec[i]->getField_f(date_id);
            const char *desc=rec[i]->getField_f(desc_id);
            if(vers[0])
            {
                AbsSettings *s=AbsSettingsInterface::createSettings();
                s->set("version","version",vers);
                s->set("version","path",path);
                s->set("version","flag",flag);
                s->set("version","date",date);
                s->set("version","description",desc);
                char *a=path::dnopath(csvpath);
                a=(char *)realloc(a,(strlen(a)+strlen(vers)+10)*sizeof(char));
                strcat(a,vers);
                strcat(a,".info");
                s->save2(a);
                free(a);
                delete s;
            }
        }
    }
    free(rec);
    delete data;
    return 0;
}
char **get_all_paths(const char *baseman_project_path,char **base_path,char **project_path,char **version_path)
{
    char **loc=strman::explode("/",baseman_project_path);
    int pos=1;
    if(base_path)*base_path=0;
    if(project_path)*project_path=0;
    if(version_path)*version_path=0;
    if(loc[0] && base_path)
    {
        *base_path=get_base_path(loc[0]);
        if(*base_path)
        {
            //printf("file system paths:\n");
            //printf("-->    base = %s\n",*base_path);
            if(project_path)
            {
                *project_path=get_project_path(*base_path,loc,&pos);
                if(*project_path)
                {
                    //printf("--> project = %s\n",*project_path);
                }
                else
                {
                    printf("project not found\n");
                }
            }
            if(*project_path && version_path)
            {
                *version_path=get_version_path(*project_path,loc,&pos);
                if(*version_path)
                {
                    //printf("--> version = %s\n",*version_path);
                }
                else
                {
                    printf("version not found\n");
                }
            }
        }
        else
        {
            printf("base not found\n");
        }
    }
    else
    {
        printf("invalid command line parameters\n");
    }
    return loc;
}
char *construct_package_path(const char *baseman_project_path,const char *package_path,const char *append)
{
    char *pname=(char *)malloc((strlen(baseman_project_path)*2+strlen(package_path)+strlen(append)+20+1)*sizeof(char));
    strcpy(pname,package_path);
    int p=strlen(pname);
    for(unsigned int i=0;i<strlen(baseman_project_path);i++)
    {
        if(baseman_project_path[i]=='/')
        {
            pname[p++]='-';
            pname[p++]='-';
        }
        else
        {
            pname[p++]=baseman_project_path[i];
        }
    }
    pname[p]=0;
    strcat(pname,append);
    return pname;
}
int install(const char *baseman_project_path,const char *package_path,bool dotar)
{
    printf("installing %s:\n",baseman_project_path);
    char *pname=construct_package_path(baseman_project_path,package_path,"/");
    if(dotar)
    {
        //unpack tar
        run_script(baseman_project_path,package_path,"unpack");
    }
    strcat(pname,"setup.info");
    AbsSettings *s=AbsSettingsInterface::createSettings();
    if(s->loadfile(pname))
    {
        std::string base=s->get("setup","base");// has to exist in baselist.csv
        std::string path=s->get("setup","file-system-path");// path rel. to base path.
        char *base_path=get_base_path(base.c_str());
        if(base_path)
        {
            char *version_path=(char *)malloc((strlen(base_path)+strlen(path.c_str())+1)*sizeof(char));
            strcpy(version_path,base_path);
            strcat(version_path,path.c_str());
            //copy project files
            pname[strlen(pname)-10]=0;
            dir::copydir(version_path,pname);
            int n=s->getNameCount("info-files");
            for(int i=0;i<n;i++)
            {
                std::string info_filename=s->getNextName("info-files");
                std::string info_contents=s->get("info-files",info_filename);
                std::string info_filepath=base_path;
                info_filepath=info_filepath+info_filename;
                unsigned int content_length=base64::decode_length(info_contents.c_str());
                void *content=base64::decode(info_contents.c_str());
                // content ist not null-terminated!
                printf("create file %s ... ",info_filepath.c_str());
                file::writefile(info_filepath.c_str(),content,content_length);
                free(content);
                //import
                import_info(info_filepath.c_str());
            }
            free(version_path);
            free(base_path);
        }
        else
        {
            printf("The package belongs to an unknown base. Add this base in baselist.csv.");
        }
    }
    else
    {
        printf("Setup file is missing. Cannot find %s.\n",pname);
    }
    delete s;
    free(pname);
    return 0;
}
int publish(const char *baseman_project_path,const char *publish_path,bool dotar)
{
    printf("publishing %s:\n",baseman_project_path);
    char *base_path;
    char *project_path;
    char *version_path;
    char **loc=get_all_paths(baseman_project_path,&base_path,&project_path,&version_path);
    if(base_path)
    {
        char *pname=construct_package_path(baseman_project_path,publish_path,"/");
        //copy project files
        dir::copydir(pname,version_path);
        //copy .info files
        AbsSettings *s=AbsSettingsInterface::createSettings();
        s->set("setup","base",loc[0]);
        s->set("setup","baseman-location",baseman_project_path);
        s->set("setup","file-system-path",&version_path[strlen(base_path)]);
        s->set("setup","package-path",pname);
        unsigned int len;
        char **v=strman::explode("/",&version_path[strlen(base_path)]);
        char *currpath=(char *)malloc((strlen(version_path)*2+1)*sizeof(char));
        strcpy(currpath,base_path);
        for(int i=0;i<strman::explode_count(v)-1;i++)
        {
            strcat(currpath,v[i]);
            strcat(currpath,".info");
            len=0;
            void *info=file::readfile(currpath,&len);
            if(info)
            {
                char *b64=base64::encode(info,len);
                s->set("info-files",&currpath[strlen(base_path)],b64);
                free(b64);
                free(info);
            }
            currpath[strlen(currpath)-5]=0;
            strcat(currpath,"/");
        }
        strman::explode_free(v);
        free(currpath);
        strcat(pname,"setup.info");
        s->save2(pname);
        delete s;
        pname[strlen(pname)-10]=0;
        if(dotar)
        {
            //create tar
            run_script(baseman_project_path,publish_path,"pack");
        }
        free(pname);
    }
    if(version_path)free(version_path);
    if(project_path)free(project_path);
    if(base_path)free(base_path);
    strman::explode_free(loc);
    return 0;
}
char *get_base_path(const char *base_name)
{
    AbsCsvData *data=AbsCsvDataInterface::createCsvData();
    data->load(BMSETUP_BASELIST_PATH);
    data->useHeader(true);
    int path_id=data->getHeaderId("path");
    AbsCsvRecord **rec=data->getAllRecords("name",base_name);
    if(rec)
    {
        int rec_count=csv::record_count(rec);
        if(rec_count==1)
        {
            const char *path=rec[0]->getField_f(path_id);
            char *a=(char *)malloc((strlen(path)+1)*sizeof(char));
            strcpy(a,path);
            free(rec);
            delete data;
            return a;
        }
        else
        {
            printf("[ERROR] bmsetup: rec_count=%d\nMultiple occurrences of base '%s' found in " BMSETUP_BASELIST_PATH ".\n",rec_count,base_name);
        }
        free(rec);
    }
    else printf("[ERROR] bmsetup: Base '%s' not found in " BMSETUP_BASELIST_PATH ".\n",base_name);
    delete data;
    return 0;
}
char *get_project_path(char *base_path,char **loc,int *pos)
{
    unsigned int current_path_memlen=256+strlen(base_path);
    char *current_path=(char *)malloc((current_path_memlen+1)*sizeof(char));
    strcpy(current_path,base_path);
    for(;*pos<strman::explode_count(loc);(*pos)++)
    {
        AbsCsvData *data=AbsCsvDataInterface::createCsvData();
        bool project_found=false;
        bool error_status=false;
        char *project_file_path=(char *)malloc((current_path_memlen+12+1)*sizeof(char));
        strcpy(project_file_path,current_path);
        strcat(project_file_path,"projects.csv");
        data->load(project_file_path);
        data->useHeader(true);
        int path_id=data->getHeaderId("path");
        AbsCsvRecord **rec=data->getAllRecords("name",loc[*pos]);
        if(rec)
        {
            int rec_count=csv::record_count(rec);
            if(rec_count==1)
            {
                const char *path=rec[0]->getField_f(path_id);
                if(strlen(current_path)+strlen(path)>=current_path_memlen)
                {
                    current_path_memlen=strlen(current_path)+strlen(path)+256;
                    current_path=(char *)realloc(current_path,(current_path_memlen+1)*sizeof(char));
                }
                if(path::pathtype(path) & 1)
                {
                    strcpy(current_path,path);
                }
                else
                {
                    strcat(current_path,path);
                }
                project_found=true;
            }
            else
            {
                printf("[ERROR] bmsetup: rec_count=%d for %s.\n[ERROR] bmsetup: More than one records found for this project.\n",rec_count,loc[*pos]);
                error_status=true;
            }
            free(rec);
        }
        else
        {
            //Else branch not required here, assuming loc[*pos] names a version.
            //printf("[ERROR] bmsetup: Error while selecting records for name='%s' from projects.csv.\n[ERROR] bmsetup: Project with this name is missing.\n",loc[*pos]);
            //error_status=true;
        }
        delete data;
        free(project_file_path);
        if(!project_found)
        {
            return current_path;
        }
        if(error_status)
        {
            free(current_path);
            return 0;
        }
    }
    return current_path;
}
char *get_version_path(char *project_path,char **loc,int *pos)
{
    unsigned int current_path_memlen=256+strlen(project_path);
    char *current_path=(char *)malloc((current_path_memlen+1)*sizeof(char));
    strcpy(current_path,project_path);
    for(;*pos<strman::explode_count(loc);(*pos)++)
    {
        AbsCsvData *data=AbsCsvDataInterface::createCsvData();
        bool version_found=false;
        char *version_file_path=(char *)malloc((current_path_memlen+12+1)*sizeof(char));
        strcpy(version_file_path,current_path);
        strcat(version_file_path,"versions.csv");
        data->load(version_file_path);
        data->useHeader(true);
        int path_id=data->getHeaderId("path");
        AbsCsvRecord **rec=data->getAllRecords("version",loc[*pos]);
        if(rec)
        {
            int rec_count=csv::record_count(rec);
            if(rec_count==1)
            {
                const char *path=rec[0]->getField_f(path_id);
                if(strlen(current_path)+strlen(path)>=current_path_memlen)
                {
                    current_path_memlen=strlen(current_path)+strlen(path)+256;
                    current_path=(char *)realloc(current_path,(current_path_memlen+1)*sizeof(char));
                }
                if(path::pathtype(path) & 1)
                {
                    strcpy(current_path,path);
                }
                else
                {
                    strcat(current_path,path);
                }
                version_found=true;
            }
            else
            {
                printf("[ERROR] bmsetup: rec_count=%d for %s.\n[ERROR] bmsetup: More than one records found for this version.\n",rec_count,loc[*pos]);
            }
            free(rec);
        }
        else
        {
            printf("[ERROR] bmsetup: Error while selecting records for version='%s' from versions.csv.\n[ERROR] bmsetup: The version with this name is missing.\n",loc[*pos]);
        }
        delete data;
        free(version_file_path);
        if(!version_found)
        {
            free(current_path);
            return 0;
        }
    }
    return current_path;
}
void bmsetup::print_usage()
{
    printf(BMSETUP_USAGE);
}
void bmsetup::patch_basemanpath_parameter(char *path)
{
    if(path[strlen(path)-1]=='/')path[strlen(path)-1]=0;
    if(path[0]=='@' && path[1] && path[2]==':' && path[3]=='/')
    {
        int i=4;
        while(path[i])
        {
            path[i-4]=path[i];
            i++;
        }
        path[i-4]=0;
    }
    if(path[0]=='@' && path[1] && path[2] && path[3]==':' && path[4]=='/')
    {
        int i=5;
        while(path[i])
        {
            path[i-5]=path[i];
            i++;
        }
        path[i-5]=0;
    }
    if(path[0]=='/')
    {
        int i=1;
        while(path[i])
        {
            path[i-1]=path[i];
            i++;
        }
        path[i-1]=0;
    }
}
void bmsetup::print_error_line(const char *msg)
{
    bool instr=true;
    for(int i=0;i<60;i++)
    {
        int r=130+i*2;
        int g=i*2;
        int b=i;
        printf("%c[%d;2;%d;%d;%dm",27,38,r,r,r);
        printf("%c[%d;2;%d;%d;%dm",27,48,r,g,b);
        if(i-2>=0 && msg[i-2]==0)
        {
            instr=false;
        }
        if(i-2>=0 && instr)
        {
            printf("%c",msg[i-2]);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}
void bmsetup::print_error(const char *msg)
{
    print_error_line("");
    print_error_line("");
    printf("%c[%dA",27,1);
    print_error_line(msg);
    print_error_line("");
    printf("%c[%dD",27,2);
    printf("%c[%dm",27,0);
    printf("Use 'bmsetup help' for more information.\n");
}
int bmsetup::main(int argc,char **argv)
{
    if(argc==1)
    {
        //no command
        print_error("--- no command given ---");
    }
    else if(argc==2)
    {
        //param 1: command
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"import-cfg")==0)
        {
            importer();
        }
        else if(strcmp(argv[1],"export-cfg")==0)
        {
            exporter();
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"check")==0)
        {
            print_error("--- not jet implemented ---");
        }
        else if(strcmp(argv[1],"help")==0)
        {
            print_usage();
        }
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else if(argc==3)
    {
        //param 1: command
        //param 2: path
        //----------------------------------------------------------------------
        patch_basemanpath_parameter(argv[2]);
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"download")==0)
        {
            if(download(argv[2],".baseman/packages/",true)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
        }
        else if(strcmp(argv[1],"install")==0)
        {
            if(download(argv[2],".baseman/packages/",false)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
            else install(argv[2],".baseman/packages/",true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"publish")==0)
        {
            publish(argv[2],"packages/",true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"pull")==0)
        {
            install(argv[2],"packages/",false);
        }
        else if(strcmp(argv[1],"push")==0)
        {
            publish(argv[2],"packages/",false);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"import-cfg")==0)
        {
            importer2(argv[2]);
        }
        else if(strcmp(argv[1],"export-cfg")==0)
        {
            exporter2(argv[2]);
        }
        //----------------------------------------------------------------------
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else if(argc==4)
    {
        //param 1: command
        //param 2: target
        //param 3: path
        //----------------------------------------------------------------------
        patch_basemanpath_parameter(argv[3]);
        //----------------------------------------------------------------------
        if(strcmp(argv[1],"download")==0)
        {
            if(download(argv[3],argv[2],true)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
        }
        else if(strcmp(argv[1],"install")==0)
        {
            if(download(argv[3],argv[2],false)==1)
            {
                print_error("[ERROR] bmsetup: Download failed.");
            }
            else install(argv[3],argv[2],true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"publish")==0)
        {
            publish(argv[3],argv[2],true);
        }
        //----------------------------------------------------------------------
        else if(strcmp(argv[1],"pull")==0)
        {
            install(argv[3],argv[2],false);
        }
        else if(strcmp(argv[1],"push")==0)
        {
            publish(argv[3],argv[2],false);
        }
        //----------------------------------------------------------------------
        else
        {
            //unknown command
            print_error("--- unknown command ---");
        }
    }
    else
    {
        //wrong command line parameter
        print_error("--- wrong command line parameter ---");
    }
    return EXIT_SUCCESS;
}
