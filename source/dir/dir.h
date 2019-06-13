/*******************************************************************************
*                                                                              *
*  dir.h                                                                       *
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
#ifndef MOD_dir_H
#define MOD_dir_H
#include <stdlib.h>
//#include "wwrap/str.h"
#include "wwrap/osio.h"
//#include "wwrap/osdir.h"
#include "wwrap/conststr.h"
//#include "osdir/osdir.h"
#ifdef OS_LIN
#include <dirent.h>
#endif
#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER
//#include "str/str.h"
//#include "dir/dir.hh"
//#include "file/file.hh"
#include "dir/import/prokee.h"
// --TODO --
class dir
{
public:
    
    
    template<class T> static int createdir(const T *path);
    
    template<class T> static bool testdir(const T *path);
    
    template<class T> static bool deletedir(const T *path);
    
    
    template<class T> static DIRECTORY<T> *opendir(const T *path);
    
    template<class T> static T *getNextItem(DIRECTORY<T> *d);
    
    template<class T> static int getItemCount(const T *path);
    
    template<class T> static bool isEmpty(const T *path);
    
    
    template<class T> static bool closedir(DIRECTORY<T> *d);
    
    
    template<class T> static bool printtree(const T *path,int depth);
    template<class T> static bool walktree(const T *path,TreeWalkCallback<T> *cb);
    template<class T> static bool walktree(const T *path,TreeWalkCallback<T> *cb,int level,int maxlevel);
    template<class T> static bool walkflat(const T *path,TreeWalkCallback<T> *cb);
    
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,const T *directory);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,const T *directory,CondCopyControl<T> *cc);
};
#include "dir/import/modules.h"
#ifdef OS_WIN
template<class T> class DIRECTORY_Impl:public DIRECTORY<T>
{
public:
    HANDLE hfind;
    myWIN32_FIND_DATA filedata;
    T *dirpath;
    DIRECTORY_Impl(const T *path);
    ~DIRECTORY_Impl();
    T *read();
    bool item_isdir();
    void dirsep();
private:
    void readdir_setup();
    T *readfirst();
};
#elif defined OS_LIN
template<class T> class DIRECTORY_Impl:public DIRECTORY<T>
{
    struct dirent *diritem;
    DIR *ddir;
    char *dirpath;
    char currentItemName[1024];
public:
    DIRECTORY_Impl(const char *path);
    DIRECTORY_Impl(const wchar_t *);
    ~DIRECTORY_Impl();
    T *read();
    bool item_isdir();
    void dirsep();
};
#endif

template<class T> int dir::createdir(const T *path)
{
    int retval=0;
    //Dateinamen ggf. aus Pfad abschneiden
    T *directory=path::dnopath(path);
    if(dir::testdir(directory)==0)
    {
        //Testen, ob das übergeordnete Verzeichnis existiert.
        T *pdir=path::pnopath(directory);
        if(dir::testdir(pdir)==0)
        {
            //Übergeordnetes Verzeichnis anlegen.
            retval=createdir(pdir);
        }
        if(retval==0)
        {
            //Verzeichnis anlegen.
            retval=osdir::mk(directory);
        }
        free(pdir);
    }
    free(directory);
    return retval;
}
template<class T> bool dir::testdir(const T *path)
{
    //Testet ob das angegebene Verzeichnis existiert.
#ifdef OS_WIN
    
    //-------------------------------------------------
    //VERSION B:
    //  Notwendig fuer Ext2Fsd.
    //  Leere Verzeichnisse enthalten normalerweise die
    //  Eintraege ./ und ../. Daher liefert die Suche
    //  nach /"*" mit FindFirstFile() einen Treffer.
    //  Mit dem Ext2Fsd-Treiber werden ./ und ../ nicht
    //  ausgegeben. Somit liefert FindFirstFile()
    //  keinen Treffer. Daher erfolgt hier die Suche
    //  nach dem Verzeichnis im Parent-Verzeichnis.
    //  Achtung: Laufzeitproblem.
    //-------------------------------------------------
    if(path::pathtype(path) & PATH_LAB)
    {
        return label::testlabel(path);
    }
    T *parentpath=path::pnopath(path);
    const T *directory=path::onopath(path);
    DIRECTORY<T> *sd=dir::opendir(parentpath);
    T *a=0;
    while(a==0 || a[0]!=0)
    {
        a=dir::getNextItem(sd);
        if(path::pathcmp(a,directory))
        {
            dir::closedir(sd);
            free(parentpath);
            return true;
        }
    }
    dir::closedir(sd);
    free(parentpath);
    return false;
#elif defined OS_LIN
    if(path[0]==0)return true;
    struct stat st;//={0};
    if(osdir::_stat(path,&st)==-1)
        return false;
    return true;
#endif
}
template<class T> bool dir::deletedir(const T *path)
{
    //OS_WIN
    if(path::pathtype(path) & PATH_LAB)
    {
        return false;
    }
    //OS_LIN
    if(path[0]==0)
    {
        return false;
    }
    if(dir::isEmpty(path))
    {
        //osio::print("%s EMPTY\n",path);
        bool b=(osdir::rm(path)==0);
        if(b)
        {
            if(path::testpath(path))
            {
                osio::print("Directory %s has been successfully deleted, but it still exists.\n",path);
                osio::print("Trying a second time...");
                b=(osdir::rm(path)==0);
                if(b)
                {
                    osio::print("...Directory deleted again.\n");
                }
                else
                {
                    osio::print("...Second deletion failed.\n");
                }
                if(!path::testpath(path))
                {
                    osio::print("Ok, now it appears to be gone.\n");
                    return true;
                }
                else
                {
                    osio::print("Sorry, it's still there.\n");
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    else
    {
        //osio::print("%s NOT EMPTY\n",path);
        return false;
    }
}
template<class T> DIRECTORY<T> *dir::opendir(const T *path)
{
    DIRECTORY<T> *d=new DIRECTORY_Impl<T>(path);
    //d->readdir_setup();
    return d;
}
template<class T> T *dir::getNextItem(DIRECTORY<T> *d)
{
    T a[4];
    T *item=d->read();
    while(str::cmp(item,conststr::cast(a,"./"))==0 ||
          str::cmp(item,conststr::cast(a,"../"))==0)
    {
        item=d->read();
    }
    return item;
}
template<class T> int dir::getItemCount(const T *path)
{
    int cnt=0;
    DIRECTORY<T> *d=new DIRECTORY_Impl<T>(path);
    T *a=0;
    while(a==0 || a[0]!=0)
    {
        a=dir::getNextItem(d);
        if(a[0]!=0)
        {
            cnt++;
        }
    }
    delete d;
    return cnt;
}
template<class T> bool dir::isEmpty(const T *path)
{
    bool retVal=true;
    DIRECTORY<T> *d=new DIRECTORY_Impl<T>(path);
    T *a=dir::getNextItem(d);
    if(a[0]!=0)
    {
        retVal=false;
    }
    delete d;
    return retVal;
}

template<class T> bool dir::closedir(DIRECTORY<T> *d)
{
    delete d;
    return true;
}

template<class T> bool dir::printtree(const T *path,int depth)
{
    if(path::pathtype(path) & PATH_DIR)
    {
        DIRECTORY<T> *sd=dir::opendir(path);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            if(a[0]!=0)
            {
                for(int i=0;i<depth;i++)osio::print("  ");
                osio::print("%s\n",a);
                if(path::pathtype(a) & PATH_DIR)
                {
                    //--TODO-- wchar_t version
                    //printtree(((string)path+a).c_str(),depth+1);
                }
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        osio::print("%s\n",path);
        return false;
    }
}
template<class T> bool dir::walktree(const T *path,TreeWalkCallback<T> *cb)
{
    if(path::pathtype(path) & PATH_DIR)
    {
        DIRECTORY<T> *sd=dir::opendir(path);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            //osio::print("%s\n",a);
            if(a[0]!=0)
            {
                T *np=(T *)malloc((str::len(path)+str::len(a)+1)*sizeof(T));
                str::cpy(np,path);
                str::cat(np,a);
                if(!cb->tw_callback(np))
                {
                    free(np);
                    dir::closedir(sd);
                    return false;
                }
                if(path::pathtype(a) & PATH_DIR)
                {
                    walktree(np,cb);
                }
                free(np);
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        //osio::print("%s\n\n",path);
        cb->tw_callback(path);
        return false;
    }
}
template<class T> bool dir::walktree(const T *path,TreeWalkCallback<T> *cb,int level,int maxlevel)
{
    if(path::pathtype(path) & PATH_DIR)
    {
        DIRECTORY<T> *sd=dir::opendir(path);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            //osio::print("%s\n",a);
            if(a[0]!=0)
            {
                T *np=(T *)malloc((str::len(path)+str::len(a)+1)*sizeof(T));
                str::cpy(np,path);
                str::cat(np,a);
                if(!cb->tw_callback(np))
                {
                    free(np);
                    dir::closedir(sd);
                    return false;
                }
                if(level<=maxlevel && path::pathtype(a) & PATH_DIR)
                {
                    walktree(np,cb,level+1,maxlevel);
                }
                free(np);
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        //osio::print("%s\n\n",path);
        cb->tw_callback(path);
        return false;
    }
}
template<class T> bool dir::walkflat(const T *path,TreeWalkCallback<T> *cb)
{
    if(path::pathtype(path) & PATH_DIR)
    {
        DIRECTORY<T> *sd=dir::opendir(path);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            //osio::print("%s\n",a);
            if(a[0]!=0)
            {
                T *np=(T *)malloc((str::len(path)+str::len(a)+1)*sizeof(T));
                str::cpy(np,path);
                str::cat(np,a);
                if(!cb->tw_callback(np))
                {
                    free(np);
                    dir::closedir(sd);
                    return false;
                }
                free(np);
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        //osio::print("%s\n\n",path);
        cb->tw_callback(path);
        return false;
    }
}
template<class T> bool dir::copydir(const T *targetpath,const T *sourcepath)
{
    if((path::pathtype(sourcepath) & PATH_DIR) && (path::pathtype(targetpath) & PATH_DIR))
    {
        //in case of empty directories.
        dir::createdir(targetpath);
        DIRECTORY<T> *sd=dir::opendir(sourcepath);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            if(a[0]!=0 && !path::copy(targetpath,sourcepath,a))
            {
                dir::closedir(sd);
                return false;
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        return false;
    }
}
template<class T> bool dir::copydir(const T *targetpath,const T *sourcepath,const T *directory)
{
    T *a=(T *)malloc((str::len(sourcepath)+str::len(directory)+2)*sizeof(T));
    T *b=(T *)malloc((str::len(targetpath)+str::len(directory)+2)*sizeof(T));
    str::cpy(a,sourcepath);
    str::cat(a,directory);
    str::cpy(b,targetpath);
    str::cat(b,directory);
    bool retVal=dir::copydir(b,a);
    free(a);
    free(b);
    return retVal;
}
template<class T> bool dir::copydir(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc)
{
    if((path::pathtype(sourcepath) & PATH_DIR) && (path::pathtype(targetpath) & PATH_DIR))
    {
        if(!cc->ignoreEmptyDir(targetpath))
            dir::createdir(targetpath);
        DIRECTORY<T> *sd=dir::opendir(sourcepath);
        T *a=0;
        while(a==0 || a[0]!=0)
        {
            a=dir::getNextItem(sd);
            if(a[0]!=0 && !path::copy(targetpath,sourcepath,a,cc))
            {
                dir::closedir(sd);
                return false;
            }
        }
        dir::closedir(sd);
        return true;
    }
    else
    {
        return false;
    }
}
template<class T> bool dir::copydir(const T *targetpath,const T *sourcepath,const T *directory,CondCopyControl<T> *cc)
{
    T *a=(T *)malloc((str::len(sourcepath)+str::len(directory)+2)*sizeof(T));
    T *b=(T *)malloc((str::len(targetpath)+str::len(directory)+2)*sizeof(T));
    str::cpy(a,sourcepath);
    str::cat(a,directory);
    str::cpy(b,targetpath);
    str::cat(b,directory);
    bool retVal=dir::copydir(b,a,cc);
    free(a);
    free(b);
    return retVal;
}
#ifdef OS_WIN
template<class T> DIRECTORY_Impl<T>::DIRECTORY_Impl(const T *path)
{
    osdir::ini_myWIN32_FIND_DATA(&filedata,(T *)0);
    dirpath=(T *)malloc((str::len(path)+5)*sizeof(T));
    str::cpy(dirpath,path);
    hfind=0;
    readdir_setup();
}
template<class T> DIRECTORY_Impl<T>::~DIRECTORY_Impl()
{
    free(dirpath);
    if(hfind!=0)FindClose(hfind);
    osdir::free_myWIN32_FIND_DATA(&filedata);
}
template<class T> T *DIRECTORY_Impl<T>::read()
{
    if(hfind==0)
    {
        return readfirst();
    }
    else
    {
        if(osdir::myFindNextFile(hfind,&filedata))
        {
            if(hfind!=0 && hfind!=INVALID_HANDLE_VALUE)
            {
                dirsep();
            }
            else
            {
                osdir::setnull_cFileName(&filedata);
            }
        }
        else
        {
            osdir::setnull_cFileName(&filedata);
        }
        return osdir::get_cFileName(&filedata,(T *)0);
    }
}
template<class T> bool DIRECTORY_Impl<T>::item_isdir()
{
    return (osdir::get(&filedata,(T *)0)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
}
template<class T> void DIRECTORY_Impl<T>::dirsep()
{
    if(item_isdir())
    {
        T a[2];
        osdir::append_cFileName(&filedata,conststr::dirsep1(a));
    }
}
template<class T> void DIRECTORY_Impl<T>::readdir_setup()
{
    T a[2];
    str::cat(dirpath,conststr::cast(a,"*"));
    osdir::setnull_cFileName(&filedata);
}
template<class T> T *DIRECTORY_Impl<T>::readfirst()
{
    hfind=osdir::myFindFirstFile(dirpath,&filedata);
    if(hfind!=INVALID_HANDLE_VALUE)// && filedata.cFileName[0]!=0)
    {
        dirsep();
    }
    else
    {
        osdir::setnull_cFileName(&filedata);
    }
    return osdir::get_cFileName(&filedata,(T *)0);
}
#elif defined OS_LIN
template<class T> DIRECTORY_Impl<T>::DIRECTORY_Impl(const char *path)
{
    dirpath=(char *)malloc((str::len(path)+1)*sizeof(char));
    str::cpy(dirpath,path);
    ddir=opendir(path);
}
template<class T> DIRECTORY_Impl<T>::DIRECTORY_Impl(const wchar_t *)
{
    // --TODO--
}
template<class T> DIRECTORY_Impl<T>::~DIRECTORY_Impl()
{
    if(ddir)closedir(ddir);
    free(dirpath);
}
template<class T> T *DIRECTORY_Impl<T>::read()
{
    if(ddir)
    {
        diritem=readdir(ddir);
        if(!diritem)
        {
            currentItemName[0]=0;
            return (T *)currentItemName;
        }
        dirsep();
    }
    else
    {
        currentItemName[0]=0;
    }
    return (T *)currentItemName;
}
template<class T> bool DIRECTORY_Impl<T>::item_isdir()
{
    struct stat sb;
    char *a=(char *)malloc((str::len(dirpath)+str::len(diritem->d_name)+1)*sizeof(char));
    str::cpy(a,dirpath);
    str::cat(a,diritem->d_name);
    if(lstat(a,&sb)==-1)
    {
        free(a);
        perror("stat");
        return false;
    }
    free(a);
    if((sb.st_mode & S_IFMT)==S_IFDIR)
    {
        return true;
    }
    return false;
}
template<class T> void DIRECTORY_Impl<T>::dirsep()
{
    str::cpy(currentItemName,diritem->d_name);
    if(item_isdir())
    {
        char a[2];
        str::cat(currentItemName,conststr::dirsep1(a));
    }
}
#endif
#endif
