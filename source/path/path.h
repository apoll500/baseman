/*******************************************************************************
*                                                                              *
*  path.h                                                                      *
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


/*********************************************************************
*                                                                    *
*  Path-Functions                                                    *
*                                                                    *
*********************************************************************/
class path
{
public:
    /*****************************************************************
    *                                                                *
    *  pathtype()                                                    *
    *                                                                *
    *****************************************************************/
    //Ermittelt ob der String path eine absolute oder relative Pfadangabe enthält
    //und ob der Pfad auf eine Datei oder ein Verzeichnis zeigt.
    template<class T> static int pathtype(const T *path,int system);
    template<class T> static int pathtype(const T *path,const T dirsep);
    template<class T> static int pathtype(const T *path,const T dirsep,const T labelsep);
    template<class T> static int pathtype(const T *path,const T *dirsep,const T *labelsep);
    template<class T> static int pathtype(const T *path,const T *dirsep,const T *labelsep,const T *rootsym);
    template<class T> static int pathtype(const T *path);
    /*****************************************************************
    *                                                                *
    *  onopath()                                                     *
    *                                                                *
    *****************************************************************/
    //Gibt einen Zeiger auf den Namen des Objektes innerhalb des Pfades zurück.
    template<class T> static const T *onopath(const T *path,const T dirsep);
    template<class T> static const T *onopath(const T *path,const T *dirsep);
    template<class T> static const T *onopath(const T *path);
    /*****************************************************************
    *                                                                *
    *  fnopath()                                                     *
    *                                                                *
    *****************************************************************/
    //Gibt einen Zeiger auf den Dateinamen innerhalb des Pfades zurück.
    template<class T> static const T *fnopath(const T *path,const T dirsep);
    template<class T> static const T *fnopath(const T *path,const T *dirsep);
    template<class T> static const T *fnopath(const T *path);
    /*****************************************************************
    *                                                                *
    *  dnopath()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static T *dnopath(const T *path,const T dirsep);
    template<class T> static T *dnopath(const T *path,const T *dirsep);
    template<class T> static T *dnopath(const T *path);
    /*****************************************************************
    *                                                                *
    *  pnopath()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static T *pnopath(const T *path,const T dirsep);
    template<class T> static T *pnopath(const T *path,const T *dirsep);
    template<class T> static T *pnopath(const T *path);
    /*****************************************************************
    *                                                                *
    *  sxopath()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static const T *sxopath(const T *path,const T dirsep,const T labelsep,const T susep);
    template<class T> static const T *sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep);
    template<class T> static const T *sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep,const T *rootsym);
    template<class T> static const T *sxopath(const T *path);
    /*****************************************************************
    *                                                                *
    *  makeabspath()                                                 *
    *                                                                *
    *****************************************************************/
    template<class T> static T *makeabspath(const T *path);
    template<class T> static T *makeabspath(const T *path,const T *cd);
    template<class T> static T *makeabspath(const T *path,const T *cd,const T *dirsep);
    /*****************************************************************
    *                                                                *
    *  testpath()                                                    *
    *                                                                *
    *****************************************************************/
    template<class T> static bool testpath(const T *path);
    /*****************************************************************
    *                                                                *
    *  copy()                                                        *
    *                                                                *
    *****************************************************************/
    template<class T> static bool copy(const T *targetpath,const T *sourcepath);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object,CondCopyControl<T> *cc);
    /*****************************************************************
    *                                                                *
    *  pathcmp()                                                     *
    *                                                                *
    *****************************************************************/
    template<class T> static bool pathcmp(const T *a,const T *b);
    /*****************************************************************
    *                                                                *
    *  compresspath()                                                *
    *                                                                *
    *****************************************************************/
    template<class T> static T *compresspath(T *path);
    template<class T> static T *compresspath(T *path,const T *dirsep);
};

#include "path/import/modules.h"

/*****************************************************************
*                                                                *
*  pathtype()                                                    *
*                                                                *
*****************************************************************/
//Ermittelt ob der String path eine absolute oder relative Pfadangabe enthält
//und ob der Pfad auf eine Datei oder ein Verzeichnis zeigt.
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
template<class T> int path::pathtype(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS];
    return pathtype(path,conststr::dirsep(a),conststr::labelsep(b),conststr::rootsym(c));
}
/*****************************************************************
*                                                                *
*  onopath()                                                     *
*                                                                *
*****************************************************************/
//Gibt einen Zeiger auf den Namen des Objektes innerhalb des Pfades zurück.
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
template<class T> const T *path::onopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return onopath(path,conststr::dirsep(a));
}
/*****************************************************************
*                                                                *
*  fnopath()                                                     *
*                                                                *
*****************************************************************/
//Gibt einen Zeiger auf den Dateinamen innerhalb des Pfades zurück.
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
template<class T> const T *path::fnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return fnopath(path,conststr::dirsep(a));
}
/*****************************************************************
*                                                                *
*  dnopath()                                                     *
*                                                                *
*****************************************************************/
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
template<class T> T *path::dnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return dnopath(path,conststr::dirsep(a));
}
/*****************************************************************
*                                                                *
*  pnopath()                                                     *
*                                                                *
*****************************************************************/
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
template<class T> T *path::pnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return pnopath(path,conststr::dirsep(a));
}
/*****************************************************************
*                                                                *
*  sxopath()                                                     *
*                                                                *
*****************************************************************/
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
        /*
        h=0;
        found=false;
        while(susep[h])
        {
            if(path[i]==susep[h++])
            {
                found=true;
                goto m1;
            }
        }
        h=0;
        while(dirsep[h])
        {
            if(path[i]==dirsep[h++])
            {
                found=true;
                goto m1;
            }
        }
        h=0;
        while(labelsep[h])
        {
            if(path[i]==labelsep[h++])
            {
                found=true;
                goto m1;
            }
        }
m1:
        if(found)
        */
        if(strman::matchsymbol(path,i,susep,dirsep,labelsep,rootsym))
        {
            k=i;
            i=0;
        }
    }
    return &path[k+1];
    //Extention umkopieren
    /*
    for(i=k+1;i<n;i++)
    {
        sx[i-k-1]=path[i];
    }
    sx[i-k-1]=0;
    return sx;
    */
}
template<class T> const T *path::sxopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS],d[CONSTSTR_MAXSEPS];
    return sxopath(path,conststr::dirsep(a),conststr::labelsep(b),conststr::susep(c),conststr::rootsym(d));
}
/*****************************************************************
*                                                                *
*  makeabspath()                                                 *
*                                                                *
*****************************************************************/
template<class T> T *path::makeabspath(const T *path)
{
    T *cd=osdir::oscwd((T *)0,0);
    T *ap=makeabspath(path,cd);
    free(cd);
    return ap;
}
template<class T> T *path::makeabspath(const T *path,const T *cd)
{
    T a[CONSTSTR_MAXSEPS];
    return makeabspath(path,cd,conststr::dirsep(a));
}
template<class T> T *path::makeabspath(const T *path,const T *cd,const T *dirsep)
{
    //Pfad komprimieren
    //compresspath(path);

    T *abspath;

    //Pfad-Typ ermitteln (abs. od. relativer Pfad)
    int t=pathtype(path);

    //In abs. Pfad umwandeln (nur wenn rel. Pfad)
    if(t==0 || t==2)
    {
        //aktuelles Verzeichnis abfragen
        //T *cd=getcdstring();//Pointer auf Original-String daher nicht freigeben.
        //T *cd=osdir::oscwd((T *)0,0);

        //absoluten Pfad zusammenbauen
        abspath=(T *)malloc((str::len(cd)+str::len(path)+2)*sizeof(T));
        str::cpy(abspath,cd);

        int h=0;
        bool found=false;
        while(dirsep[h])
        {
            if(abspath[str::len(abspath)-1]==dirsep[h++])
            {
                found=true;
                break;
            }
        }

        if(!found)
        {
            T a[2];a[0]=dirsep[0];a[1]=0;
            str::cat(abspath,a);
        }

        str::cat(abspath,path);

        //free(cd);
    }
    else
    {
        //absoluten Pfad nur umkopieren (keine Änderung)
        abspath=(T *)malloc((str::len(path)+1)*sizeof(T));
        str::cpy(abspath,path);
    }

    return abspath;
}
/*****************************************************************
*                                                                *
*  testpath()                                                    *
*                                                                *
*****************************************************************/
template<class T> bool path::testpath(const T *path)
{
    //Testet ob der angegebene Pfad (d.h. das Verzeichnis oder die Datei) existiert.
    if(path::pathtype(path) & PATH_DIR)
    {
        return dir::testdir(path);
    }
    return file::testfile(path);
}
/*****************************************************************
*                                                                *
*  copy()                                                        *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  pathcmp()                                                     *
*                                                                *
*****************************************************************/
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
/*****************************************************************
*                                                                *
*  compresspath()                                                *
*                                                                *
*****************************************************************/
template<class T> T *path::compresspath(T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return compresspath(path,conststr::dirsep(a));
}
template<class T> T *path::compresspath(T *path,const T *dirsep)
{
    int h;bool found;

    int n=str::len(path);
    T *b=(T *)malloc((n+5)*sizeof(T));
    b[0]=0;

    int i=0,j=0;
    int mode=0;

    int repcount=0;

    //osio::print("PATH_0: %s\n",path);

    while(i<n)
    {
        // "./" immer ueberspringen
        if(i+1<n && path[i]=='.')// && (path[i+1]==DIRSEPERATOR || path[i+1]==DIRSEPERATOR2))
        {
            h=0;found=false;
            while(dirsep[h])
            {
                if(path[i+1]==dirsep[h++])
                {
                    found=true;
                    break;
                }
            }

            if(found)
            {
                i=i+2;
            }
        }
        if(mode==0)
        {
            //Am Anfang alle "../" umkopieren.
            if(i+2<n && path[i]=='.' && path[i+1]=='.')// && (path[i+2]==DIRSEPERATOR || path[i+2]==DIRSEPERATOR2))
            {
                h=0;found=false;
                while(dirsep[h])
                {
                    if(path[i+2]==dirsep[h++])
                    {
                        found=true;
                        break;
                    }
                }

                if(found)
                {
                    T up[4];up[0]='.';up[1]='.';up[3]='/';up[3]=0;
                    str::cat(b,up);
                    i=i+3;
                    j=j+3;
                }
                else
                {
                    mode=1;
                }
            }
            else
            {
                /*
                h=0;found=false;
                while(dirsep[h])
                {
                    if(path[i+2]==dirsep[h++])
                    {
                        found=true;
                        break;
                    }
                }
                */
                //if(!found)
                //{
                    mode=1;
                //}
            }
            //osio::print("\n0:%s i=%d j=%d mode=%d rc=%d\n",b,i,j,mode,repcount);
        }
        if(mode==1)
        {
            /*
            if(path[i]==DIRSEPERATOR || path[i]==DIRSEPERATOR2)
            {
                repcount=repcount+1;
            }
            */

            h=0;found=false;
            while(dirsep[h])
            {
                if(path[i]==dirsep[h++])
                {
                    found=true;
                    break;
                }
            }

            if(found)
            {
                repcount=repcount+1;
            }

            b[j]=path[i];
            i=i+1;
            j=j+1;
            while(repcount>0 && i+2<n && path[i]=='.' && path[i+1]=='.')// && (path[i+2]==DIRSEPERATOR || path[i+2]==DIRSEPERATOR2))
            {
                h=0;found=false;
                while(dirsep[h])
                {
                    if(path[i+2]==dirsep[h++])
                    {
                        found=true;
                        break;
                    }
                }

                if(!found)
                {
                    break;
                }

                //if(repcount>0 && i+2<n && path[i]=='.' && path[i+1]=='.')// && (path[i+2]==DIRSEPERATOR || path[i+2]==DIRSEPERATOR2))
                //{
                    i=i+3;
                    j=j-2;
                    while(j>=0)// && b[j]!=DIRSEPERATOR && b[j]!=DIRSEPERATOR2)
                    {
                        h=0;found=false;
                        while(dirsep[h])
                        {
                            if(b[j]==dirsep[h++])
                            {
                                found=true;
                                break;
                            }
                        }

                        if(found)
                        {
                            break;
                        }

                        j=j-1;
                    }
                    j=j+1;
                    if(j==0)
                    {
                        mode=0;
                    }
                    repcount=repcount-1;
                //}
                b[j]=0;
                //osio::print("\n1:%s i=%d j=%d mode=%d rc=%d\n",b,i,j,mode,repcount);
            }
            b[j]=0;
        }
        //osio::print("\n%s\n",b);
    }

    j=0;
    while(b[j]!=0)
    {
        path[j]=b[j];
        j=j+1;
    }
    path[j]=0;

    //osio::print("PATH_1: %s\n",path);

    free(b);
    return path;
}

#endif
