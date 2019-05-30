/*******************************************************************************
*                                                                              *
*  MergeControler.h                                                            *
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
#ifndef BASEMAN_MergeControler_H
#define BASEMAN_MergeControler_H

#include "../../macros/macros.h"

#include <stdio.h>
#include <time.h>

#include <map>
#include <vector>
#include <iostream>

#ifdef OS_LIN
#include <utime.h>
#endif

#define ACTION_DONOTHING 0
#define ACTION_EXPORT 1
#define ACTION_IMPORT 2
#define ACTION_EXPORT_BACKUP 3
#define ACTION_IMPORT_BACKUP 4
#define ACTION_CONFLICT_CHANGED 5
#define ACTION_CONFLICT_NEW 6
#define ACTION_INFO_DEL 7
#define ACTION_INFO_NEW 8
#define ACTION_DELETE 9
#define ACTION_DELETE_BACKUP 10
#define ACTION_PRINT_TARGET 11
#define ACTION_PRINT_SOURCE 12
#define ACTION_PRINT_INFO 13
#define ACTION_SOURCE_DELETE 14
#define ACTION_SOURCE_DELETE_BACKUP 15
#define ACTION_PACKAGE 16

#include "wwrap/osfile.h"
#include "wwrap/conststr.h"
#include "../../blib/date.h"

#include "BmCopyControl.h"

#include "../baseman.h"

template<class T> class MergeControler:public BmCondCopyControl<T>,public TreeWalkCallback<T>
{
protected:
    FILE *f;
    AbsCsvData *log;
    std::map<std::string,AbsCsvRecord *> recs;
    std::map<std::string,int> status;
    std::map<std::string,std::string> firstsource;
    std::vector<std::string> newfiles;
    int *casemeth;
    bool doCleanup;
    bool conslog;

    bool additional_printObsLogItems;
    bool additional_printNewTargetFiles;
    bool create_emptyDirs;
    bool delete_emptyDirs;

    std::vector<std::string> ignors;

    T sdate[48];
public:
    MergeControler(const T *logfile);
    MergeControler(const T *logfile,int *actions);
    MergeControler(const T *logfile,int *actions,int flags);
    MergeControler(const T *logfile_in,const T *logfile_out);
    MergeControler(const T *logfile_in,const T *logfile_out,int *actions);
    MergeControler(const T *logfile_in,const T *logfile_out,int *actions,int flags);
    void ini_MergeControler(const T *logfile);
    void ini_MergeControler(const T *logfile_in,const T *logfile_out);
    virtual ~MergeControler();
    virtual void setup(int flags);
    virtual void setup(bool clean,bool pnew,bool pobs,bool cons,bool deldir,bool makedirs);
    virtual void add_ign(std::string ign);
    virtual bool test_ign(const T *filename);
    virtual bool ignoreEmptyDir(const T *path);
    virtual void closeLog();
    virtual bool doCopyFile(const T *targetpath,const T *sourcepath);
    virtual void filecopied(const T *targetpath,const T *sourcepath,size_t bytes);
    virtual bool swapcopy(const T *targetpath,const T *sourcepath);
    virtual bool backupcopy_sf(const T *sourcepath,const T *backup_source_path);
    virtual bool backupcopy(const T *sourcepath,const T *backup_source_path);
    virtual bool tw_callback(const T *path);
    virtual void print_newfiles();
    virtual void importfiles(const T *project_path,const T *target_path);
    virtual int importfiles_extmode(const T *target_path,int depth,all_projects_info a);
    virtual void setcasemeth(int *meth);
    virtual bool runmeth(int fall,const T *targetpath,const T *sourcepath);
    virtual bool remove_file(const T *path);
    virtual bool test_match(const T *path,int depth,std::string basename,std::string projname,std::string versname);
};

template<class T> void MergeControler<T>::setcasemeth(int *meth)
{
    casemeth=meth;
}
template<class T> bool MergeControler<T>::runmeth(int fall,const T *targetpath,const T *sourcepath)
{
    switch(casemeth[fall])
    {
        case ACTION_DONOTHING:
            return false;
        case ACTION_EXPORT:
            osio::print("---> %s",targetpath);
            return true;
        case ACTION_IMPORT:
            osio::print("<--- %s",targetpath);
            return swapcopy(targetpath,sourcepath);
        case ACTION_EXPORT_BACKUP:
            osio::print("---> %s",targetpath);
            backupcopy(sourcepath,targetpath);
            return true;
        case ACTION_IMPORT_BACKUP:
            osio::print("<--- %s",targetpath);
            backupcopy(sourcepath,sourcepath);
            return swapcopy(targetpath,sourcepath);
        case ACTION_CONFLICT_NEW:
        case ACTION_CONFLICT_CHANGED:
            osio::print("-><- %s\n",targetpath);
            osio::print("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\nCONFLICT (SOURCE AND TARGET CHANGED):\nSOURCE: %s\nTARGET: %s\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n",sourcepath,targetpath);
            osio::print("comparing...");
            if(file::compare(targetpath,sourcepath))
            {
                osio::print("...true.\n");
                osio::print("updating logfile...");
                filecopied(targetpath,sourcepath,osfile::get_size(sourcepath));
                std::vector<std::string>::iterator i;
                for(i=newfiles.begin();i!=newfiles.end();i++)
                {
                    if(str::cmp((*i).c_str(),targetpath)==0)
                    {
                        newfiles.erase(i);
                        break;
                    }
                }
                osio::print("...OK\n");
            }
            else
            {
                osio::print("...false.\n");
            }
            return false;
        case ACTION_INFO_DEL:
            return false;
        case ACTION_INFO_NEW:
            return false;
        case ACTION_DELETE:
            osio::print("---- %s\n",targetpath);
            remove_file(targetpath);
            return false;
        case ACTION_DELETE_BACKUP:
            osio::print("---- %s\n",targetpath);
            backupcopy(sourcepath,targetpath);
            remove_file(targetpath);
            return false;
        case ACTION_SOURCE_DELETE:
            osio::print("---- %s\n",sourcepath);
            remove_file(sourcepath);
            return false;
        case ACTION_SOURCE_DELETE_BACKUP:
            osio::print("---- %s\n",sourcepath);
            backupcopy(sourcepath,sourcepath);
            remove_file(sourcepath);
            return false;
        case ACTION_PRINT_TARGET:
            osio::print("%s\n",targetpath);
            return false;
        case ACTION_PRINT_SOURCE:
            osio::print("%s\n",sourcepath);
            return false;
        case ACTION_PRINT_INFO:
            osio::print("----------\ncopy file\n");
            osio::print("from: %s\n",sourcepath);
            osio::print("to:   %s\n",targetpath);
            return false;
        case ACTION_PACKAGE:
            std::string ws=ini->get("webspace");
            osio::print(">>>> %s\n",sourcepath);
#ifdef OS_LIN
            osio::print("++++ %s\n",(ws+"package"+sourcepath).c_str());
            file::copyfile((ws+"package"+sourcepath).c_str(),sourcepath);
#endif
            return false;
    }
    return false;
}

template<class T> bool MergeControler<T>::remove_file(const T *path)
{
    if(delete_emptyDirs)
    {
        if(!file::remove_clean(path))
        {
            osio::print("     Could not delete this file!\n");
            return false;
        }
    }
    else
    {
        if(!osfile::rm(path))
        {
            osio::print("     Could not delete this file!\n");
            return false;
        }
    }
    return true;
}

template<class T> MergeControler<T>::MergeControler(const T *logfile)
{
    ini_MergeControler(logfile);
    setup(false,false,false,false,true,true);
    //--TODO--
    //setcasemeth(actions);
}

template<class T> MergeControler<T>::MergeControler(const T *logfile,int *actions)
{
    ini_MergeControler(logfile);
    setup(false,false,false,false,true,true);
    setcasemeth(actions);
}

template<class T> MergeControler<T>::MergeControler(const T *logfile,int *actions,int flags)
{
    ini_MergeControler(logfile);
    setup(flags);
    setcasemeth(actions);
}

template<class T> MergeControler<T>::MergeControler(const T *logfile_in,const T *logfile_out)
{
    ini_MergeControler(logfile_in,logfile_out);
    setup(false,false,false,false,true,true);
    //--TODO--
    //setcasemeth(actions);
}

template<class T> MergeControler<T>::MergeControler(const T *logfile_in,const T *logfile_out,int *actions)
{
    ini_MergeControler(logfile_in,logfile_out);
    setup(false,false,false,false,true,true);
    setcasemeth(actions);
}

template<class T> MergeControler<T>::MergeControler(const T *logfile_in,const T *logfile_out,int *actions,int flags)
{
    ini_MergeControler(logfile_in,logfile_out);
    setup(flags);
    setcasemeth(actions);
}

template<class T> void MergeControler<T>::ini_MergeControler(const T *logfile)
{
    ini_MergeControler(logfile,logfile);
}

template<class T> void MergeControler<T>::ini_MergeControler(const T *logfile_in,const T *logfile_out)
{
    //INPUT
    log=AbsCsvDataInterface::createCsvData();

    if(log->load(logfile_in))
    {
        osio::print("Missing file: %s\n",logfile_in);
        osio::print("Could'nt open log-file %s.\n",logfile_in);
    }
    else
    {
        log->useHeader(true);

        AbsCsvRecord **r=log->getAllRecords();
        int i=0;
        while(r[i])
        {
            if(r[i]->getField_f(0)[0]!=0)
            {
                recs[r[i]->getField(1)]=r[i];
                status[r[i]->getField(1)]=0;
            }
            i++;
        }
    }

    //OUTPUT
    T a[3];
    f=file::openfile(logfile_out,conststr::cast(a,"wb"));
    osio::print(f,"file,target,date,length\n");

    //DATESTRING
    date::get_bdn(sdate);
}

template<class T> MergeControler<T>::~MergeControler()
{
    closeLog();
    delete log;
    if(f)fclose(f);
}

template<class T> void MergeControler<T>::setup(int flags)
{
    setup(flags & RUN_CLEAN,flags & RUN_PRINTNEW,flags & RUN_PRINTOBS,flags & RUN_CONSLOG,flags & RUN_DELDIRS,flags & RUN_MKEMPTYDIRS);
}

template<class T> void MergeControler<T>::setup(bool clean,bool pnew,bool pobs,bool cons,bool deldir,bool makedirs)
{
    conslog=cons;
    doCleanup=clean;
    additional_printObsLogItems=pobs;
    additional_printNewTargetFiles=pnew;
    delete_emptyDirs=deldir;
    create_emptyDirs=makedirs;
}

template<class T> void MergeControler<T>::add_ign(std::string ign)
{
    ignors.push_back(ign);
}

template<class T> bool MergeControler<T>::test_ign(const T *filename)
{
    for(std::vector<std::string>::iterator i=ignors.begin();i!=ignors.end();i++)
    {
        if(strman::substrmatch((*i).c_str(),filename))
        {
            return true;
        }
    }
    return false;
}

template<class T> bool MergeControler<T>::ignoreEmptyDir(const T *)//path)
{
    return create_emptyDirs;
}

template<class T> void MergeControler<T>::closeLog()
{
    std::string obsfiles="";
    std::string targetpath;
    std::string sourcepath;

    bool printrec;

    if(additional_printNewTargetFiles)print_newfiles();

    for(std::map<std::string,AbsCsvRecord *>::iterator i=recs.begin();i!=recs.end();i++)
    {
        AbsCsvRecord *r=(*i).second;
        targetpath=r->getField(1);
        sourcepath=r->getField(0);

        printrec=false;

        if(doCleanup)
        {
            if(status[targetpath]==0)
            {
                if(file::testfile(sourcepath.c_str()))
                {
                    if(file::testfile(targetpath.c_str()))
                    {
                        //(fall Änderung der csv-Tabelle).
                        osio::print("~~~~ %s\n",targetpath.c_str());
                        backupcopy(sourcepath.c_str(),targetpath.c_str());
                        remove_file(targetpath.c_str());
                    }
                }
                else if(doCopyFile(targetpath.c_str(),sourcepath.c_str()))
                {
                    //doCopyFile() sollte hier im Normalfall false zurückgeben.
                    //copyfile() als Alternative.
                    file::copyfile(targetpath.c_str(),sourcepath.c_str());
                }
            }
            else
            {
                printrec=true;
            }
        }
        else
        {
            if(conslog)
            {
                if(status[targetpath]!=0)
                {
                    printrec=true;
                }
            }
            else
            {
                printrec=true;
            }


        }

        if(!doCleanup && additional_printObsLogItems)
        {
            if(status[targetpath]==0)
            {
                if(path::testpath(targetpath.c_str()))
                {
                    obsfiles+="---- "+targetpath+"\n";
                }
                else
                {
                    printrec=false;
                }
            }
        }

        if(printrec)r->print_ln(f);
    }

    if(obsfiles!="")
    {
        osio::print("There are (possibly) obsolete files:\n");
        osio::print("%s",obsfiles.c_str());
        osio::print("\nUse 'clean' to remove these files from the target directory.\n\n");
    }

    if(BmCondCopyControl<T>::getError())
    {
        osio::print("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        osio::print("See errors above!\n");
        osio::print("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        return;
    }
}

template<class T> bool MergeControler<T>::doCopyFile(const T *targetpath,const T *sourcepath)
{
    int update_time=0,target_time=0,source_time=0;
    unsigned long update_size=0,target_size=0,source_size=0;
    const char *t_utime;
    const char *t_usize;
    char usc[64];

    int fall=0;

    bool logged=false;
    bool target_exists=false;
    bool source_exists=false;
    bool target_unchanged=true;
    bool source_unchanged=true;

    if(MergeControler<T>::test_ign(sourcepath))return false;

    if(recs.count(targetpath)==1)
    {
        logged=true;
    }

    if(logged)
    {
        AbsCsvRecord *r=recs[targetpath];
        t_utime=r->getField(2);
        t_usize=r->getField(3);
        str::cpy(usc,t_usize);
        if(str::len(usc)>6)usc[str::len(usc)-6]=0;
        update_time=atoi(t_utime);
        update_size=atol(usc);
    }

    if(file::testfile(sourcepath))source_exists=true;
    if(file::testfile(targetpath))target_exists=true;

    if(source_exists)
    {
        source_size=osfile::get_size(sourcepath);
        source_time=osfile::get_time_write(sourcepath);
        if(source_size!=update_size || source_time>update_time)source_unchanged=false;
    }

    if(target_exists)
    {
        target_size=osfile::get_size(targetpath);
        target_time=osfile::get_time_write(targetpath);
        if(target_size!=update_size || target_time>update_time)target_unchanged=false;
    }

    if(firstsource.count(targetpath)==1)
    {
        if(firstsource[targetpath]!=sourcepath)
        {
            //bereits kopiert.
            std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
            std::cout << "Ignoring file." << std::endl;
            std::cout << "target = " << targetpath << std::endl;
            std::cout << "source = " << sourcepath << std::endl;
            std::cout << "This file has already been copied from: " << firstsource[targetpath] <<  std::endl;
            std::cout << "Check your files.csv table(s)." << std::endl;
            std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        firstsource[targetpath]=sourcepath;
    }

    if(logged && source_exists && source_unchanged && target_exists && target_unchanged)
    {
        fall=1;
    }
    else if(logged && source_exists && source_unchanged && target_exists && !target_unchanged)
    {
        fall=2;
    }
    else if(logged && source_exists && source_unchanged && !target_exists)
    {
        fall=3;
    }
    else if(logged && source_exists && !source_unchanged && target_exists && target_unchanged)
    {
        fall=4;
    }
    else if(logged && source_exists && !source_unchanged && target_exists && !target_unchanged)
    {
        fall=5;
    }
    else if(logged && source_exists && !source_unchanged && !target_exists)
    {
        fall=6;
    }
    else if(logged && !source_exists && target_exists && target_unchanged)
    {
        fall=7;
    }
    else if(logged && !source_exists && target_exists && !target_unchanged)
    {
        fall=8;
    }
    else if(logged && !source_exists && !target_exists)
    {
        fall=9;
    }
    else if(!logged && source_exists && target_exists)
    {
        fall=10;
    }
    else if(!logged && source_exists && !target_exists)
    {
        fall=11;
    }
    else if(!logged && !source_exists && target_exists)
    {
        fall=12;
    }

    //Log-Eintrag wurde bearbeitet
    status[targetpath]=1;

    return runmeth(fall,targetpath,sourcepath);

    //Unberücksichtigte Einträge im Logfile -- obsolete files

    //Neue Files im Taget -- new files
}

template<class T> void MergeControler<T>::filecopied(const T *targetpath,const T *sourcepath,size_t bytes)
{
    osio::print(" OK\n");
    if(recs.count(targetpath)!=1)
    {
        AbsCsvSettings *s=AbsCsvSettingsInterface::createCsvSettings(',','\n','\"');
        CsvField fld(s);
        fld.print(f,sourcepath);
        fprintf(f,"%c",',');
        fld.print(f,targetpath);
        fprintf(f,"%c",',');
        delete s;
#ifdef OS_LIN
        osio::print(f,"%ld,%lu Bytes\n",osfile::get_time_write(targetpath),bytes);
#elif defined OS_WIN
        osio::print(f,"%ld,%u Bytes\n",osfile::get_time_write(targetpath),bytes);
#endif
    }
    else
    {
        AbsCsvRecord *r=recs[targetpath];

        T a[64];
        osio::sprint(a,"%ld",osfile::get_time_write(targetpath));
        r->setField(2,a);

#ifdef OS_LIN
        osio::sprint(a,"%lu Bytes",bytes);
#elif defined OS_WIN
        osio::sprint(a,"%u Bytes",bytes);
#endif
        r->setField(3,a);
    }
}

template<class T> bool MergeControler<T>::swapcopy(const T *targetpath,const T *sourcepath)
{
    //swap copy.
    bool b=file::copyfile(sourcepath,targetpath);
    if(b)
    {
        //Eintrag in csv-Tabelle.
        filecopied(targetpath,sourcepath,osfile::get_size(sourcepath));
#ifdef OS_WIN
        //Datum aendern fuer OS_WIN
        char *spcopy=(char *)malloc((str::len(sourcepath)+1)*sizeof(char));
        str::cpy(spcopy,sourcepath);

        char *tpcopy=(char *)malloc((str::len(targetpath)+1)*sizeof(char));
        str::cpy(tpcopy,targetpath);

        HANDLE hs=osfile::myCreateFile(spcopy,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
        if(hs==INVALID_HANDLE_VALUE)
        {
            osio::print(">>>> Error: (INVALID_HANDLE_VALUE) %s\n",sourcepath);
        }
        else
        {
            FILETIME ft;
            HANDLE ht=osfile::myCreateFile(tpcopy,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
            if(hs==INVALID_HANDLE_VALUE)
            {
                osio::print(">>>> Error: (INVALID_HANDLE_VALUE) %s\n",targetpath);
            }
            else
            {
                if(!GetFileTime(ht,NULL,NULL,&ft))
                {
                    osio::print(">>>> Error: GetFileTime() %s\n",targetpath);
                }
                else
                {
                    if(!SetFileTime(hs,NULL,NULL,&ft))
                    {
                        osio::print(">>>> Error: SetFileTime() %s\n",sourcepath);
                    }
                }
                CloseHandle(ht);
            }
            CloseHandle(hs);
        }
        free(spcopy);
        free(tpcopy);
#elif defined OS_LIN
        //Datum aendern fuer OS_WIN
        utimbuf tb;
        tb.actime=file::get_time_write(targetpath);
        tb.modtime=tb.actime;
        utime(sourcepath,&tb);
#endif
        return false;//mit true: wieder ins Zeilverzeichnis kopieren. .... ev. zur Kontrolle sinnvoll.
    }
    else
    {
        osio::print("-><- COPY ERROR %s\n",targetpath);
        return false;
    }
}

template<class T> bool MergeControler<T>::backupcopy_sf(const T *sourcepath,const T *backup_source_path)
{
    T *backuppath;
    if(strman::isprefix(BmCondCopyControl<T>::get_base_path().c_str(),sourcepath))
    {
        backuppath=(T *)malloc((str::len(sourcepath)+BmCondCopyControl<T>::get_base_path().size()+128)*sizeof(T));
        str::cpy(backuppath,BmCondCopyControl<T>::get_base_path().c_str());
        str::cat(backuppath,"backup/");
        str::cat(backuppath,&sourcepath[BmCondCopyControl<T>::get_base_path().size()]);
        osio::sprint(&backuppath[str::len(backuppath)],"__%lu",time(0));

        bool b=file::copyfile(backuppath,backup_source_path);
        if(!b)
        {
            osio::print(">>>> Error: (COPY ERROR) No Backup Copy GENERATED FOR %s\n",backup_source_path);
            return false;
        }
    }
    else
    {
        osio::print(">>>> Error: (OUTSIDE OF BASE) No Backup Copy GENERATED FOR %s\n",backup_source_path);
    }
    return true;
}

template<class T> bool MergeControler<T>::backupcopy(const T *sourcepath,const T *backup_source_path)
{
    T *backuppath;
    std::string bpath;
    int i=0;
    while(i<BmCondCopyControl<T>::get_base_path_count())
    {
        bpath=BmCondCopyControl<T>::get_next_base_path();
        if(strman::isprefix(bpath.c_str(),sourcepath))
        {
            backuppath=(T *)malloc((str::len(sourcepath)+bpath.size()+128)*sizeof(T));
            str::cpy(backuppath,bpath.c_str());
            str::cat(backuppath,"backup/");
            str::cat(backuppath,sdate);
            str::cat(backuppath,"/");
            str::cat(backuppath,&sourcepath[bpath.size()]);

            bool b=file::copyfile(backuppath,backup_source_path);
            if(!b)
            {
                osio::print(">>>> Error: (COPY ERROR) No Backup Copy GENERATED FOR %s\n",backup_source_path);
                return false;
            }
            return true;
        }
        i++;
    }
    osio::print(">>>> Error: (OUTSIDE OF BASE) No Backup Copy GENERATED FOR %s\n",backup_source_path);
    osio::print("(base-path: %s)\n",bpath.c_str());
    return true;
}

template<class T> bool MergeControler<T>::tw_callback(const T *targetpath)
{
    if(path::pathtype(targetpath) & PATH_DIR)
    {
        return true;
    }
    if(recs.count(targetpath)!=1)
    {
        if(!MergeControler<T>::test_ign(targetpath))
            newfiles.push_back(targetpath);
    }
    return true;
}

template<class T> void MergeControler<T>::print_newfiles()
{
    if(newfiles.size()>0)
    {
        osio::print("There are new files:\n");
        for(std::vector<std::string>::iterator i=newfiles.begin();i!=newfiles.end();i++)
        {
            std::cout << "++++ " << (*i) << std::endl;
        }
        osio::print("\nUse 'import' to import these files here.\n\n");
    }
}

template<class T> void MergeControler<T>::importfiles(const T *project_path,const T *target_path)
{
    for(std::vector<std::string>::iterator i=newfiles.begin();i!=newfiles.end();i++)
    {
        if(strman::isprefix(target_path,(*i).c_str()))
        {
            std::string sp=(std::string)project_path+"files/"+(*i).substr(str::len(target_path),std::string::npos);

            if(doCopyFile((*i).c_str(),sp.c_str()))
            {
                //doCopyFile() ruft swapcopy() auf und liefert normalerweise false.
                //copyfile() als Alternative.
                file::copyfile((*i).c_str(),sp.c_str());
            }
        }
        else
        {
            osio::print("ERROR: Wrong target_path?");
        }
    }
    newfiles.clear();
}
template<class T> int MergeControler<T>::importfiles_extmode(const T *target_path,int depth,all_projects_info a)
{
    int skipcount=-1;
    for(int c_depth=0;c_depth<depth;c_depth++)
    {
        skipcount=0;
        for(std::vector<std::string>::iterator i=newfiles.begin();i!=newfiles.end();i++)
        {
            if(strman::isprefix(target_path,(*i).c_str()))
            {
                std::string project_path;
                //find matching project
                bool project_found=false;
                for(unsigned int k=0;k<a.project.size();k++)
                {
                    std::string basename=a.project[k].base;
                    std::string projname=a.project[k].project;
                    std::string versname=a.project[k].version;
                    if(test_match(&(*i).c_str()[str::len(target_path)],c_depth,basename,projname,versname))
                    {
                        project_found=true;
                        Bm *b=BmCondCopyControl<T>::bm->createBm(basename,projname,versname,true);
                        project_path=b->fullpath;

                        std::string sp=(std::string)project_path+"files/"+(*i).substr(str::len(target_path),std::string::npos);

                        if(doCopyFile((*i).c_str(),sp.c_str()))
                        {
                            //doCopyFile() ruft swapcopy() auf und liefert normalerweise false.
                            //copyfile() als Alternative.
                            file::copyfile((*i).c_str(),sp.c_str());
                        }

                        (*i)="";

                        k=a.project.size();
                    }
                }
                if(!project_found)
                {
                    skipcount++;
                }
            }
            else if((*i)!="")
            {
                skipcount++;
                osio::print("ERROR: Wrong target_path?");
            }
        }
        if(skipcount==0)break;
    }
    newfiles.clear();
    return skipcount;
}
template<class T> bool MergeControler<T>::test_match(const T *path,int depth,std::string basename,std::string projname,std::string versname)
{
    bool rval=false;
    std::string b0=basename;
    std::string p0=projname;
    std::string v0=versname;
    const char *b=b0.c_str();
    const char *p=p0.c_str();
    const char *v=v0.c_str();
    char **pp=strman::explode("/",p);
    char **vv=strman::explode("/",v);
    char **aa=strman::explode("/",path);
    for(int i=0;i<strman::explode_count(pp);i++)
    {
        if(strman::isprefix("mod_",pp[i]))
        {
            //This is allowed --> all substrings are within the buffer of path.
            pp[i]=&(pp[i][4]);
        }
    }
    //Test for toplevel project name
    char *pname=pp[strman::explode_count(pp)-1];
    for(int i=strman::explode_count(aa)-1;i>=std::max(0,strman::explode_count(aa)-1-depth);i--)
    {
        char **aaa=strman::explode("_.",aa[i]);
        for(int k=0;k<strman::explode_count(aaa);k++)
        {
            if(pname[0]!=0 && str::cmp(pname,aaa[k])==0
                && str::cmp(pname,"api")!=0)//ignore project 'api' ...... --TODO--
            {
                printf("++++ [%s --> %s --> %s]\n",b,p,v);
                rval=true;
                k=strman::explode_count(aaa);
                i=-1;//strman::explode_count(aa);
            }
        }
        free(aaa);
    }
    //Test for supper projects
    //Test for version names
    //test for basename
    free(pp);
    free(vv);
    free(aa);
    return rval;
}

#endif
