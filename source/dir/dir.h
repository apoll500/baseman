/*******************************************************************************
*                                                                              *
*  dir.h                                                                       *
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
// dir.h
#ifndef MOD_dir_H
#define MOD_dir_H

/*
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <io.h>

#include <math.h>
#include <time.h>
#include <limits.h>

//für _getdrives()
#include<direct.h>
*/

#include <stdlib.h>

#include "wwrap/str.h"
#include "wwrap/osio.h"
#include "wwrap/osdir.h"
#include "wwrap/conststr.h"

#ifdef OS_LIN
#include <dirent.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>

#endif

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER
#include "dir/dir.hh"

#include "file/file.hh"

#include "dir/import/prokee.h"

#ifdef OS_WIN
template<class T> class DIRECTORY_Impl:public DIRECTORY<T>
{
public:
    HANDLE hfind;
    myWIN32_FIND_DATA *filedata;
    T *dirpath;
    DIRECTORY_Impl(const T *path)
    {
        filedata=new myWIN32_FIND_DATA((T *)0);
        dirpath=(T *)malloc((str::len(path)+5)*sizeof(T));
        str::cpy(dirpath,path);
        hfind=0;

        readdir_setup();
    }
    ~DIRECTORY_Impl()
    {
        free(dirpath);
        if(hfind!=0)FindClose(hfind);
        delete filedata;
    }
    T *read()
    {
        if(hfind==0)
        {
            return readfirst();
        }
        else
        {
            if(osdir::myFindNextFile(hfind,filedata))
            {
                if(hfind!=0 && hfind!=INVALID_HANDLE_VALUE)
                {
					dirsep();
                }
                else
                {
                    filedata->setnull_cFileName();
                }
            }
            else
            {
                filedata->setnull_cFileName();
            }
            return filedata->get_cFileName((T *)0);
        }
    }
    bool item_isdir()
    {
        return (filedata->get((T *)0)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
    }
    void dirsep()
    {
        if(item_isdir())
        {
            T a[2];
            filedata->append_cFileName(conststr::dirsep1(a));
        }
    }
private:
    void readdir_setup()
    {
        T a[2];
        str::cat(dirpath,conststr::cast(a,"*"));
        filedata->setnull_cFileName();
    }
    T *readfirst()
    {
        hfind=osdir::myFindFirstFile(dirpath,filedata);
        if(hfind!=INVALID_HANDLE_VALUE)// && filedata->cFileName[0]!=0)
        {
            dirsep();
        }
        else
        {
            filedata->setnull_cFileName();
        }
        return filedata->get_cFileName((T *)0);
    }
};
#elif defined OS_LIN
template<class T> class DIRECTORY_Impl:public DIRECTORY<T>
{
    struct dirent *diritem;
    DIR *ddir;
    char *dirpath;
    char currentItemName[1024];
public:
    DIRECTORY_Impl(const char *path)
    {
        dirpath=(char *)malloc((str::len(path)+1)*sizeof(char));
        str::cpy(dirpath,path);
        ddir=opendir(path);
    }
    DIRECTORY_Impl(const wchar_t *)
    {
        // --TODO--
    }
    ~DIRECTORY_Impl()
    {
        if(ddir)closedir(ddir);
        free(dirpath);
    }
    T *read()
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
    bool item_isdir()
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
    void dirsep()
    {
        str::cpy(currentItemName,diritem->d_name);
        if(item_isdir())
        {
            char a[2];
            str::cat(currentItemName,conststr::dirsep1(a));
        }
    }
};
/*
class DIRECTORY_Impl:public DIRECTORY<wchar_t>
{
public:
    DIRECTORY_Impl(const wchar_t *)
    {
    }
    ~DIRECTORY_Impl()
    {
    }
    T *read()
    {
        return 0;
    }
    bool item_isdir()
    {
        return false;
    }
    void dirsep()
    {
    }
};
*/
/*
template<class T> class DIRECTORY_Impl:public DIRECTORY<T>
{
    struct dirent *diritem;
    DIR *ddir;
    T *dirpath;
    T currentItemName[1024];
public:
    DIRECTORY_Impl(const char *path)
    {
        dirpath=(T *)malloc((str::len(path)+1)*sizeof(T));
        str::cpy(dirpath,path);
        ddir=opendir(path);
    }
    DIRECTORY_Impl(const wchar_t *)
    {
        // --TODO--
    }
    ~DIRECTORY_Impl()
    {
        if(ddir)closedir(ddir);
        free(dirpath);
    }
    T *read()
    {
        if(ddir)
        {
            diritem=readdir(ddir);
            if(!diritem)
            {
                currentItemName[0]=0;
                return currentItemName;
            }
            dirsep();
        }
        else
        {
            currentItemName[0]=0;
        }
        return currentItemName;
    }
    bool item_isdir()
    {
        struct stat sb;
        T *a=(T *)malloc((str::len(dirpath)+str::len(diritem->d_name)+1)*sizeof(T));
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
    void dirsep()
    {
        str::cpy(currentItemName,diritem->d_name);
        if(item_isdir())
        {
            T a[2];
            str::cat(currentItemName,conststr::dirsep1(a));
        }
    }
};
*/
#endif

/*********************************************************************
*                                                                    *
*  Directory-Functions                                               *
*                                                                    *
*********************************************************************/
class dir
{
public:
    /*****************************************************************
    *                                                                *
    *  getProgramDirectory()                                         *
    *                                                                *
    *****************************************************************/
    template<class T> static T *getProgramDirectory(const T *param);
    /*****************************************************************
    *                                                                *
    *  createdir()                                                   *
    *                                                                *
    *****************************************************************/
    template<class T> static int createdir(const T *path);
    /*****************************************************************
    *                                                                *
    *  testdir()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static bool testdir(const T *path);
    /*****************************************************************
    *                                                                *
    *  deletedir()                                                   *
    *                                                                *
    *****************************************************************/
    template<class T> static bool deletedir(const T *path);
    /*****************************************************************
    *                                                                *
    *  listdir()                                                     *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  opendir()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static DIRECTORY<T> *opendir(const T *path);
    /*****************************************************************
    *                                                                *
    *  getNextItem()                                                 *
    *                                                                *
    *****************************************************************/
    template<class T> static T *getNextItem(DIRECTORY<T> *d);
    /*****************************************************************
    *                                                                *
    *  getItemCount()                                                *
    *                                                                *
    *****************************************************************/
    template<class T> static int getItemCount(const T *path);
    /*****************************************************************
    *                                                                *
    *  inEmpty()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static bool isEmpty(const T *path);
    /*****************************************************************
    *                                                                *
    *  resetdir()                                                    *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  getAllItems()                                                 *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  closedir()                                                    *
    *                                                                *
    *****************************************************************/
    template<class T> static bool closedir(DIRECTORY<T> *d);
    /*****************************************************************
    *                                                                *
    *  renamedir()                                                   *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  movedir()                                                     *
    *                                                                *
    *****************************************************************/
    /*****************************************************************
    *                                                                *
    *  tree()                                                        *
    *                                                                *
    *****************************************************************/
    template<class T> static bool printtree(const T *path,int depth);
    template<class T> static bool walktree(const T *path,TreeWalkCallback<T> *cb);
    template<class T> static bool walktree(const T *path,TreeWalkCallback<T> *cb,int level,int maxlevel);
    template<class T> static bool walkflat(const T *path,TreeWalkCallback<T> *cb);
    /*****************************************************************
    *                                                                *
    *  copydir()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,const T *directory);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copydir(const T *targetpath,const T *sourcepath,const T *directory,CondCopyControl<T> *cc);
};

#include "dir/import/modules.h"

/*****************************************************************
*                                                                *
*  getProgramDirectory()                                         *
*                                                                *
*****************************************************************/
template<class T> T *dir::getProgramDirectory(const T *param)
{
    T *path=path::pnopath(param);
    //In case, if a relative path is given. (prepend current working directory)
    if(!(path::pathtype(path) & PATH_ABS))
    {
        //finding out current directory:
        //  POSIX:   getcwd()
        //  ISO:     _getcwd() and _wgetcwd() ... (Not included in C-Runtime Library?)
        //  WINDOWS: GetCurrentDirectory()
        T *cwd=osdir::oscwd((T *)0,0);//Argument 0 lets the Funktion allocate the required memory.
        if(cwd!=0)
        {
            T a[CONSTSTR_MAXSEPS];
            cwd=(T *)realloc(cwd,(str::len(cwd)+str::len(path)+2)*sizeof(T));
            str::cat(cwd,conststr::dirsep1(a));
            str::cat(cwd,path);
            free(path);
            path=cwd;
        }
    }
    return path;
}
/*****************************************************************
*                                                                *
*  createdir()                                                   *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  testdir()                                                     *
*                                                                *
*****************************************************************/
template<class T> bool dir::testdir(const T *path)
{
    //Testet ob das angegebene Verzeichnis existiert.
#ifdef OS_WIN
    /*
    //-------------------------------------------------
    //VERSION A:
    //  Suche nach /"*". (Problem mit Ext2Fsd)
    //-------------------------------------------------
    bool h=false;
    HANDLE hfind=0;
    myWIN32_FIND_DATA filedata((T *)0);
    T *directory=(T *)malloc((str::len(path)+5)*sizeof(T));
    //Suchpfad
    str::cpy(directory,path);
    // * für Suchpfad anhängen
    T a[3];
    str::cat(directory,conststr::cast(a,"*"));
    //Verzeichnis einlesen
    filedata.get((T *)0)->cFileName[0]=0;
    hfind=osdir::myFindFirstFile(directory,filedata.get((T *)0));
    //ersten Eintrag einlesen
    if(hfind!=INVALID_HANDLE_VALUE)// && filedata.cFileName[0]!=0)
    {
        h=true;
    }
    if(hfind!=0)FindClose(hfind);
    free(directory);
    return h;
    */
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
/*****************************************************************
*                                                                *
*  deletedir()                                                   *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  listdir()                                                     *
*                                                                *
*****************************************************************/
template<class T> DIRECTORY<T> *dir::opendir(const T *path)
{
    DIRECTORY<T> *d=new DIRECTORY_Impl<T>(path);
    //d->readdir_setup();
    return d;
}
/*****************************************************************
*                                                                *
*  getNextItem()                                                 *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  getItemCount()                                                *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  inEmpty()                                                     *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  resetdir()                                                    *
*                                                                *
*****************************************************************/
/*****************************************************************
*                                                                *
*  getAllItems()                                                 *
*                                                                *
*****************************************************************/
/*****************************************************************
*                                                                *
*  closedir()                                                    *
*                                                                *
*****************************************************************/
template<class T> bool dir::closedir(DIRECTORY<T> *d)
{
    delete d;
    return true;
}
/*****************************************************************
*                                                                *
*  renamedir()                                                   *
*                                                                *
*****************************************************************/
/*****************************************************************
*                                                                *
*  movedir()                                                     *
*                                                                *
*****************************************************************/
/*****************************************************************
*                                                                *
*  tree()                                                        *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  copydir()                                                     *
*                                                                *
*****************************************************************/
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

#endif
