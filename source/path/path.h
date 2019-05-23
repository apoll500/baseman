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
    template<class T> static T *makeabspath(const T *path);
    template<class T> static T *makeabspath(const T *path,const T *cd);
    template<class T> static T *makeabspath(const T *path,const T *cd,const T *dirsep);
    template<class T> static bool testpath(const T *path);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copy(const T *targetpath,const T *sourcepath,const T *object,CondCopyControl<T> *cc);
    template<class T> static bool pathcmp(const T *a,const T *b);
    template<class T> static T *compresspath(T *path);
    template<class T> static T *compresspath(T *path,const T *dirsep);
};

#include "path/import/modules.h"

/**bmc
DEF param_path:ctp
{
    name="path";
    direction="IN";
    desc="The path (as null-terminated string).";
}
DEF param_system:i
{
    name="system";
    desc="Specifies the format of the path according to the operating system. Set this value to 1 for paths on Unix and 2 for paths on Windows files systems.";
}
DEF param_dirsep:t
{
    name="dirsep";
    desc="The symbol used to separate directory names.";
}
DEF param_labelsep:t
{
    name="labelsep";
    desc="The symbol used to mark the end of the label.";
}
DEF param_susep:t
{
    name="susep";
    desc="The symbol used to mark the beginning of the file extension.";
}
DEF param_dirsep2:ctp
{
    name="dirsep";
    direction="IN";
    desc="The symbols used to separate directory names.";
}
DEF param_labelsep2:ctp
{
    name="labelsep";
    direction="IN";
    desc="The symbols used to mark the end of the label.";
}
DEF param_susep2:ctp
{
    name="susep";
    direction="IN";
    desc="The symbols used to mark the beginning of the file extension.";
}
DEF param_rootsym2:ctp
{
    name="rootsym";
    direction="IN";
    desc="The symbols used for root.";
}
*/
//------------------------------------------------------------------------------
//
//  #begin pathtype
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_pathtype
{
    class="path";
    brief="Determines if a string specifies an absolute or relative path and if it is a path to a file or a path to a directory (or a path which contains only a label). See section <a href='#sec_types'>Types of Paths</a> for more information.";
}
*/
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    sep_bevore="0px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> int path::pathtype(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS];
    return pathtype(path,conststr::dirsep(a),conststr::labelsep(b),conststr::rootsym(c));
}
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_system{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
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
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> int path::pathtype(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[CONSTSTR_MAXSEPS];
    return pathtype(path,a,conststr::labelsep(b),a);
}
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="4";
    param:param_path{}
    param:param_dirsep{}
    param:param_labelsep{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> int path::pathtype(const T *path,const T dirsep,const T labelsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[2];b[0]=labelsep;b[1]=0;
    return pathtype(path,a,b,a);
}
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="5";
    param:param_path{}
    param:param_dirsep2{}
    param:param_labelsep2{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> int path::pathtype(const T *path,const T *dirsep,const T *labelsep)
{
    return pathtype(path,dirsep,labelsep,dirsep);
}
/**bmc
DEF pathtype:TEMPLATE,inc_pathtype
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="6";
    param:param_path{}
    param:param_dirsep2{}
    param:param_labelsep2{}
    param:param_rootsym2{}
    return:i="Returns the type of the path.@remark_pathtype.text";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin onopath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_onopath
{
    class="path";
    brief="Returns a pointer to the object the path points to. This is the last named component of the path.";
}
*/
/**bmc
DEF onopath:TEMPLATE,inc_onopath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    return:ctp="Returns a pointer to the first character of the last named component within the path string.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::onopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return onopath(path,conststr::dirsep(a));
}
/**bmc
DEF onopath:TEMPLATE,inc_onopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_dirsep{}
    return:ctp="Returns a pointer to the first character of the last named component within the path string.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::onopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return onopath(path,a);
}
/**bmc
DEF onopath:TEMPLATE,inc_onopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep2{}
    return:ctp="Returns a pointer to the first character of the last named component within the path string.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::onopath(const T *path,const T *dirsep)
{
    int i,n=str::len(path);
    for(i=n-2;i>0;i--)
    {
        if(strman::matchsymbol(path,i,dirsep))return &path[i+1];
    }
    return path;
}
//------------------------------------------------------------------------------
//  #end
//  #begin fnopath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_fnopath
{
    class="path";
    brief="Returns a pointer to the file-name the path points to.";
}
*/
/**bmc
DEF fnopath:TEMPLATE,inc_fnopath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    return:ctp="Returns a pointer to the first character of the file-name.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::fnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return fnopath(path,conststr::dirsep(a));
}
/**bmc
DEF fnopath:TEMPLATE,inc_fnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_dirsep{}
    return:ctp="Returns a pointer to the first character of the file-name.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::fnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return fnopath(path,a);
}
/**bmc
DEF fnopath:TEMPLATE,inc_fnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep2{}
    return:ctp="Returns a pointer to the first character of the file-name.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::fnopath(const T *path,const T *dirsep)
{
    int i,n=str::len(path);
    for(i=n-1;i>0;i--)
    {
        if(strman::matchsymbol(path,i,dirsep))return &path[i+1];
    }
    return path;
}
//------------------------------------------------------------------------------
//  #end
//  #begin dnopath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_dnopath
{
    class="path";
    brief="Returns the path to the directory the path points to. If the path is a path to a directory, this function returns a copy of the path. If it is a path to a file, the function returns the path to the directory of this file.";
}
*/
/**bmc
DEF dnopath:TEMPLATE,inc_dnopath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::dnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return dnopath(path,conststr::dirsep(a));
}
/**bmc
DEF dnopath:TEMPLATE,inc_dnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_dirsep{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::dnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return dnopath(path,a);
}
/**bmc
DEF dnopath:TEMPLATE,inc_dnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep2{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin pnopath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_pnopath
{
    class="path";
    brief="Returns the path to the parent directory.";
}
*/
/**bmc
DEF pnopath:TEMPLATE,inc_pnopath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the parent directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::pnopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return pnopath(path,conststr::dirsep(a));
}
/**bmc
DEF pnopath:TEMPLATE,inc_pnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_dirsep{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the parent directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::pnopath(const T *path,const T dirsep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    return pnopath(path,a);
}
/**bmc
DEF pnopath:TEMPLATE,inc_pnopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep2{}
    remark:remark_free{}
    return:tp="Returns a pointer to the newly allocated buffer, that holds the path to the parent directory.";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin sxopath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_sxopath
{
    class="path";
    brief="Returns a pointer to the file extension.";
}
*/
/**bmc
DEF sxopath:TEMPLATE,inc_sxopath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    return:ctp="Returns a pointer to the first character of the file-extension.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::sxopath(const T *path)
{
    T a[CONSTSTR_MAXSEPS],b[CONSTSTR_MAXSEPS],c[CONSTSTR_MAXSEPS],d[CONSTSTR_MAXSEPS];
    return sxopath(path,conststr::dirsep(a),conststr::labelsep(b),conststr::susep(c),conststr::rootsym(d));
}
/**bmc
DEF sxopath:TEMPLATE,inc_sxopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_dirsep{}
    param:param_labelsep{}
    param:param_susep{}
    return:ctp="Returns a pointer to the first character of the file-extension.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::sxopath(const T *path,const T dirsep,const T labelsep,const T susep)
{
    T a[2];a[0]=dirsep;a[1]=0;
    T b[2];b[0]=labelsep;b[1]=0;
    T c[2];c[0]=susep;c[1]=0;
    return sxopath(path,a,b,c,a);
}
/**bmc
DEF sxopath:TEMPLATE,inc_sxopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_dirsep2{}
    param:param_labelsep2{}
    param:param_susep2{}
    return:ctp="Returns a pointer to the first character of the file-extension.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
template<class T> const T *path::sxopath(const T *path,const T *dirsep,const T *labelsep,const T *susep)
{
    return sxopath(path,dirsep,labelsep,susep,dirsep);
}
/**bmc
DEF sxopath:TEMPLATE,inc_sxopath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="4";
    param:param_path{}
    param:param_dirsep2{}
    param:param_labelsep2{}
    param:param_susep2{}
    param:param_rootsym2{}
    return:ctp="Returns a pointer to the first character of the file-extension.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin makeabspath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_makeabspath
{
    class="path";
    brief="Constructs the absolute path.";
}
*/
/**bmc
DEF param_cd:ctp
{
    name="cd";
    direction="IN";
    desc="The current working directory (as null-terminated string).";
}
*/
/**bmc
DEF makeabspath:TEMPLATE,inc_makeabspath
{
    sep_bevore="10px";
    //cap_bevore="more";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path{}
    return:tp="Returns the absolute path.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::makeabspath(const T *path)
{
    T *cd=osdir::oscwd((T *)0,0);
    T *ap=makeabspath(path,cd);
    free(cd);
    return ap;
}
/**bmc
DEF makeabspath:TEMPLATE,inc_makeabspath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path{}
    param:param_cd{}
    return:tp="Returns the absolute path.";
    docu
    {
        THEINTERFACE;
    }
}
*/
template<class T> T *path::makeabspath(const T *path,const T *cd)
{
    T a[CONSTSTR_MAXSEPS];
    return makeabspath(path,cd,conststr::dirsep(a));
}
/**bmc
DEF makeabspath:TEMPLATE,inc_makeabspath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_path{}
    param:param_cd{}
    param:param_dirsep2{}
    return:tp="Returns the absolute path.";
    docu
    {
        THEINTERFACE;
    }
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin testpath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_testpath
{
    class="path";
    brief="Tests if a path exists.";
}
*/
/**bmc
DEF testpath:TEMPLATE,inc_testpath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    param:param_path{}
    return:b="Returns @kw.true, if the path exists and @kw.false otherwise.";
    docu
    {
        THEINTERFACE;
    }
    require:require_file_dir{};
}
*/
template<class T> bool path::testpath(const T *path)
{
    //Testet ob der angegebene Pfad (d.h. das Verzeichnis oder die Datei) existiert.
    if(path::pathtype(path) & PATH_DIR)
    {
        return dir::testdir(path);
    }
    return file::testfile(path);
}
//------------------------------------------------------------------------------
//  #end
//  #begin copy
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_copy
{
    class="path";
    brief="Copies the content from sourcepath to targetpath.";
}
*/
/**bmc
DEF param_targetpath:ctp
{
    name="targetpath";
    direction="IN";
    desc="The path (as null-terminated string).";
}
DEF param_sourcepath:ctp
{
    name="sourcepath";
    direction="IN";
    desc="The path (as null-terminated string).";
}
DEF param_object:ctp
{
    name="object";
    direction="IN";
    desc="The name of the object (as null-terminated string).";
}
DEF param_CondCopyControl:manu
{
    name="ccc";
    direction="IN";
    desc="Pointer to an instance of an implementation of CondCopyControl.<br>See <a href='@param_classinfo[]_@version[]_CondCopyControl\.php'>@param_classinfo\:CondCopyControl</a>.";
    param_classname="CondCopyControl";
    param_templateclass="TRUE";
    param_classinfo="file";
}
*/
/**bmc
DEF copy:TEMPLATE,inc_copy
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_targetpath{}
    param:param_sourcepath{}
    return:b="Returns @kw.true, if successful and otherwise @kw.false\.";
    docu
    {
        THEINTERFACE;
    }
    require:require_file_dir{};
}
*/
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
/**bmc
DEF copy:TEMPLATE,inc_copy
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_targetpath{}
    param:param_sourcepath{}
    param:param_object{}
    return:b="Returns @kw.true, if successful and otherwise @kw.false\.";
    docu
    {
        THEINTERFACE;
    }
    require:require_file_dir{};
}
*/
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
/**bmc
DEF copy:TEMPLATE,inc_copy
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="3";
    param:param_targetpath{}
    param:param_sourcepath{}
    param:param_CondCopyControl{}
    return:b="Returns @kw.true, if successful and otherwise @kw.false\.";
    docu
    {
        THEINTERFACE;
    }
    require:require_file_dir{};
}
*/
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
/**bmc
DEF copy:TEMPLATE,inc_copy
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="4";
    param:param_targetpath{}
    param:param_sourcepath{}
    param:param_object{}
    param:param_CondCopyControl{}
    return:b="Returns @kw.true, if successful and otherwise @kw.false\.";
    docu
    {
        THEINTERFACE;
    }
    require:require_file_dir{};
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin pathcmp
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_pathcmp
{
    class="path";
    brief="Compares two paths, if they are equal.";
    xinfo
    {
        ->
        You may want to call <a href="@modname[]_@version[]\.php&num;compresspath1">compresspath()</a> bevore calling pathcmp().<br>
        <ul style="margin-top:0px;margin-bottom:-20px;">
            <li><code>pathcmp("test/sub/../","test/")</code> returns @kw.false\.</li>
            <li><code>pathcmp(compresspath("test/sub/../"),"test/")</code> returns @kw.true\.</li>
        </ul>
        <-
    }
    xinfo
    {
        ->
        Mind that the paths <code>test/</code> and <code>test</code> are not equal.
        <-
    }
    xinfo
    {
        ->
        The method <a href="@modname[]_@version[]\.php&num;makeabspath1">makeabspath()</a> may be helpful to compare paths of the actual file system. 
        <-
    }
}
*/
/**bmc
DEF param_path_a:ctp
{
    name="path_a";
    direction="IN";
    desc="The path (as null-terminated string).";
}
DEF param_path_b:ctp
{
    name="path_b";
    direction="IN";
    desc="The path (as null-terminated string).";
}
*/
/**bmc
DEF pathcmp:TEMPLATE,inc_pathcmp
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path_a{}
    param:param_path_b{}
    return:b="Returns @kw.true, if both paths are identical, and otherwise @kw.false\.";
    docu
    {
        THEINTERFACE;
    }
    require:require_strman{};
}
*/
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
//------------------------------------------------------------------------------
//  #end
//  #begin compresspath
//
//------------------------------------------------------------------------------
/**bmc
DEF inc_compresspath
{
    class="path";
    brief="Simplifies a path by removing <code>./</code> and <code>../</code> from the path where possible. (One ore more <code>../</code> directories at the beginning of the path are not removed.)";
}
DEF param_path_v:tp
{
    name="path";
    direction="IN/OUT";
    desc="The path (as null-terminated string).";
}
remark_rewrite_path:REMARK
{
    text="The provided path will be overwritten with the simplified path. (The length of the simplified path is always shorter or equal to the length of the provided path.)";
}
*/
/**bmc
DEF compresspath:TEMPLATE,inc_compresspath
{
    sep_bevore="10px";
    path="TRUE";
    function="@this.parent.NAME";
    suffix="1";
    param:param_path_v{}
    return:tp="Returns a pointer to the compressed path.";
    docu
    {
        THEINTERFACE;
    }
    remark:remark_rewrite_path{};
}
*/
template<class T> T *path::compresspath(T *path)
{
    T a[CONSTSTR_MAXSEPS];
    return compresspath(path,conststr::dirsep(a));
}
/**bmc
DEF compresspath:TEMPLATE,inc_compresspath
{
    path="TRUE";
    function="@this.parent.NAME";
    suffix="2";
    param:param_path_v{}
    param:param_dirsep2{}
    return:tp="Returns a pointer to the compressed path.";
    docu
    {
        THEINTERFACE;
    }
    remark:remark_rewrite_path{};
}
*/
template<class T> T *path::compresspath(T *path,const T *dirsep)
{
    int h;bool found;

    int n=str::len(path);
    T *b=(T *)malloc((n+5)*sizeof(T));
    b[0]=0;

    int i=0,j=0;
    int mode=0;
    int repcount=0;

    while(i<n)
    {
        // "./" immer ueberspringen
        if(i+1<n && path[i]=='.')
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
            if(i+2<n && path[i]=='.' && path[i+1]=='.')
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
        }
        if(mode==1)
        {
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
            while(repcount>0 && i+2<n && path[i]=='.' && path[i+1]=='.')
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

                //if(repcount>0 && i+2<n && path[i]=='.' && path[i+1]=='.')
                //{
                    i=i+3;
                    j=j-2;
                    while(j>=0)
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
            }
            b[j]=0;
        }
    }

    j=0;
    while(b[j]!=0)
    {
        path[j]=b[j];
        j=j+1;
    }
    path[j]=0;

    free(b);
    return path;
}

//------------------------------------------------------------------------------
//  #end
//------------------------------------------------------------------------------

#endif
