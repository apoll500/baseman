/*******************************************************************************
*                                                                              *
*  path.h                                                                      *
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
#ifndef MOD_path_H
#define MOD_path_H
#include <stdio.h>
#include <stdlib.h>
#include "wwrap/str.h"
#include "wwrap/conststr.h"
#include "wwrap/osdir.h"
template<class T> class CondCopyControl;
#define PATH_SYSTEM_LINUX 1
#define PATH_SYSTEM_WINDOWS 2
#define PATH_ABS 1
#define PATH_DIR 2
#define PATH_LAB 4
template<class T> class DIRECTORY;
template<class T> class TreeWalkCallback;
#include "path/import/prokee.h"
class path
{
public:
    template<class T> static int pathtype(const T *path,int system);
    template<class T> static int pathtype(const T *path,const T dirsep);
    template<class T> static int pathtype(const T *path,const T dirsep,const T labelsep);
    template<class T> static int pathtype(const T *path,const T *dirsep,const T *labelsep);
    template<class T> static int pathtype(const T *path,const T *dirsep,const T *labelsep,const T *rootsym);
    template<class T> static int pathtype(const T *path);
    template<class T> static const T *onopath(const T *path,const T dirsep);
    template<class T> static const T *onopath(const T *path,const T *dirsep);
    template<class T> static const T *onopath(const T *path);
    template<class T> static const T *fnopath(const T *path,const T dirsep);
    template<class T> static const T *fnopath(const T *path,const T *dirsep);
    template<class T> static const T *fnopath(const T *path);
    template<class T> static T *dnopath(const T *path,const T dirsep);
    template<class T> static T *dnopath(const T *path,const T *dirsep);
    template<class T> static T *dnopath(const T *path);
    template<class T> static T *pnopath(const T *path,const T dirsep);
    template<class T> static T *pnopath(const T *path,const T *dirsep);
    template<class T> static T *pnopath(const T *path);
    template<class T> static const T *sxopath(const T *path,const T dirsep,const T labelsep,const T susep);
    template<class T> static const T *sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep);
    template<class T> static const T *sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep,const T *rootsym);
    template<class T> static const T *sxopath(const T *path);
    
    template<class T> static bool testpath(const T *path);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object,CondCopyControl<T> *cc);
    template<class T> static bool pathcmp(const T *a,const T *b);
    
};
#include "path/import/modules.h"

template<class T> int path::pathtype(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS];
    return pathtype(path,conststr::dirsep(a),conststr::labelsep(b),conststr::rootsym(c));
}

template<class T> int path::pathtype(const T *path,int system)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS];
    switch(system)
    {
        case PATH_SYSTEM_LINUX:
            return pathtype(path,conststr::dirsep1(a),conststr::labelsep(b),conststr::rootsym(c));
        case PATH_SYSTEM_WINDOWS:
            return pathtype(path,conststr::dirsep2(a),conststr::labelsep(b),conststr::rootsym(c));
        default:
            return pathtype(path,conststr::dirsep(a),conststr::labelsep(b),conststr::rootsym(c));
    }
}

template<class T> int path::pathtype(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[CONSTSTR_MAXSEPS];
    return pathtype(path,a,conststr::labelsep(b),a);
}

template<class T> int path::pathtype(const T *path,const T dirsep,const T labelsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[2];b[0]=labelsep;b[1]=0;
    return pathtype(path,a,b,a);
}

template<class T> int path::pathtype(const T *path,const T *dirsep,const T *labelsep)
{
    return pathtype(path,dirsep,labelsep,dirsep);
}

template<class T> int path::pathtype(const T *path,const T *dirsep,const T *labelsep,const T *rootsym)
{
    bool isabs=false;
    bool isdir=false;
    bool islab=false;
    int i,n=str::len(path);
    if(strman::matchsymbol(path,n-1,dirsep))isdir=true;
    if(strman::matchsymbol(path,0,rootsym))isabs=true;
    if(!isabs)
    {
        for(i=0;i<n;i++)
        {
            if(strman::matchsymbol(path,i,dirsep))break;
            if(strman::matchsymbol(path,i,labelsep))
            {
                isabs=true;
                //
                i++;
                while(i<n && strman::matchsymbol(path,i,labelsep))i++;
                while(i<n && strman::matchsymbol(path,i,dirsep))i++;
                if(n==i)islab=true;
                break;
            }
        }
    }
    return isabs*PATH_ABS+isdir*PATH_DIR+islab*PATH_LAB;
}

template<class T> const T *path::onopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return onopath(path,conststr::dirsep(a));
}

template<class T> const T *path::onopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return onopath(path,a);
}

template<class T> const T *path::onopath(const T *path,const T *dirsep)
{
    int i,n=str::len(path);
    for(i=n-2;i>0;i--)
    {
        if(strman::matchsymbol(path,i,dirsep))return &path[i+1];
    }
    return path;
}

template<class T> const T *path::fnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return fnopath(path,conststr::dirsep(a));
}

template<class T> const T *path::fnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return fnopath(path,a);
}

template<class T> const T *path::fnopath(const T *path,const T *dirsep)
{
    int i,n=str::len(path);
    for(i=n-1;i>0;i--)
    {
        if(strman::matchsymbol(path,i,dirsep))return &path[i+1];
    }
    return path;
}

template<class T> T *path::dnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return dnopath(path,conststr::dirsep(a));
}

template<class T> T *path::dnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return dnopath(path,a);
}

template<class T> T *path::dnopath(const T *path,const T *dirsep)
{
    //Gibt Verzeichnis aus einem Pfad zurück.
    //Falls path ein Pfad auf einen Ordner ist, wird eine Kopie von path zurückgegeben.
    //Falls path ein Pfad auf eine Datei ist, wird der Dateiname abgeschnitten.
    int h,i,k=-1,n=str::len(path);
    T *rp=(T *)malloc((n+1)*sizeof(T));
    rp[0]=0;
    //Testen, ob es sich um einen Pfad auf eine Datei handelt
    int pt=pathtype(path);
    if(pt==0 || pt==1)
    {//pfad auf Datei
        //Letztes auftreten eines Dirseperators ermitteln
        for(i=n-1;i>0;i--)
        {
            h=0;
            while(dirsep[h])
            {
                if(path[i]==dirsep[h++])
                {
                    k=i;
                    i=0;
                    break;
                }
            }
        }
        //Pfad bis inkl. Position k umkopieren
        for(i=0;i<=k;i++)
        {
            rp[i]=path[i];
        }
        rp[i]=0;
    }
    else
    {//pfad auf Verzeichnis
        str::cpy(rp,path);
    }
    return rp;
}

template<class T> T *path::pnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return pnopath(path,conststr::dirsep(a));
}

template<class T> T *path::pnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return pnopath(path,a);
}

template<class T> T *path::pnopath(const T *path,const T *dirsep)
{
    //Gibt Parent-Verzeichnis aus einem Pfad zurück.
    int h,i,k=-1,n=str::len(path);
    T *rp=(T *)malloc((n+1)*sizeof(T));
    rp[0]=0;
    //Letztes auftreten eines Dirseperators ermitteln (ausgenommen letztes Zeichen, falls Pfad auf Verzeichnis)
    for(i=n-2;i>0;i--)
    {
        h=0;
        while(dirsep[h])
        {
            if(path[i]==dirsep[h++])
            {
                k=i;
                i=0;
                break;
            }
        }
    }
    //Pfad bis inkl. Position k umkopieren
    for(i=0;i<=k;i++)
    {
        rp[i]=path[i];
    }
    rp[i]=0;
    return rp;
}

template<class T> const T *path::sxopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS],d[CONSTSTR_MAXSEPS];
    return sxopath(path,conststr::dirsep(a),conststr::labelsep(b),conststr::susep(c),conststr::rootsym(d));
}

template<class T> const T *path::sxopath(const T *path,const T dirsep,const T labelsep,const T susep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[2];b[0]=labelsep;b[1]=0;
    T c[2];c[0]=susep;c[1]=0;
    return sxopath(path,a,b,c,a);
}

template<class T> const T *path::sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep)
{
    return sxopath(path,dirsep,labelsep,susep,dirsep);
}

template<class T> const T *path::sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep,const T *rootsym)
{
    //Gibt die File-Extention aus einem Pfad zurück.
    //Falls der Pfad auf ein Verzeichnis zeigt, wird ein Leerstring zurückgegeben.
    //Bei Dateinamen ohne Extention wird der gesamte Dateiname zurückgegeben.
    //bool found;
    int i,k=-1,n=str::len(path);
    //T *sx=(T *)malloc((n+1)*sizeof(T));
    //sx[0]=0;
    //vom Ende, bis zum ersten Dirseperatorzeichen, Punkt (".") oder Label (":") durchlaufen
    for(i=n-1;i>0;i--)
    {
        
        if(strman::matchsymbol(path,i,susep,dirsep,labelsep,rootsym))
        {
            k=i;
            i=0;
        }
    }
    return &path[k+1];
    //Extention umkopieren
    
}

template<class T> bool path::testpath(const T *path)
{
    //Testet ob der angegebene Pfad (d.h. das Verzeichnis oder die Datei) existiert.
    if(path::pathtype(path) & PATH_DIR)
    {
        return dir::testdir(path);
    }
    return file::testfile(path);
}

template<class T> bool path::copy(const T *targetpath,const T *sourcepath)
{
    if(path::pathtype(sourcepath) & PATH_DIR)
    {
        return dir::copydir(targetpath,sourcepath);
    }
    else
    {
        return file::copyfile(targetpath,sourcepath);
    }
}

template<class T> bool path::copy(const T *targetpath,const T *sourcepath,const T *object)
{
    if((path::pathtype(sourcepath) & PATH_DIR) && (path::pathtype(targetpath) & PATH_DIR))
    {
        if(path::pathtype(object) & PATH_DIR)
        {
            return dir::copydir(targetpath,sourcepath,object);
        }
        else
        {
            return file::copyfile(targetpath,sourcepath,object);
        }
    }
    else
    {
        return false;
    }
}

template<class T> bool path::copy(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc)
{
    if(path::pathtype(sourcepath) & PATH_DIR)
    {
        return dir::copydir(targetpath,sourcepath,cc);
    }
    else
    {
        return file::copyfile(targetpath,sourcepath,cc);
    }
}

template<class T> bool path::copy(const T *targetpath,const T *sourcepath,const T *object,CondCopyControl<T> *cc)
{
    if((path::pathtype(sourcepath) & PATH_DIR) && (path::pathtype(targetpath) & PATH_DIR))
    {
        if(path::pathtype(object) & PATH_DIR)
        {
            return dir::copydir(targetpath,sourcepath,object,cc);
        }
        else
        {
            return file::copyfile(targetpath,sourcepath,object,cc);
        }
    }
    else
    {
        return false;
    }
}

template<class T> bool path::pathcmp(const T *a,const T *b)
{
    T s[CONSTSTR_MAXSEPS];conststr::dirsep(s);
    int i=-1;
    do
    {
        i++;
        if(!(a[i]==b[i] || (strman::matchsymbol(a,i,s) && strman::matchsymbol(b,i,s))))
            return false;
    }while(a[i]);
    return true;
}

#endif
