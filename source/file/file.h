/*******************************************************************************
*                                                                              *
*  file.h                                                                      *
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
// file.h
#ifndef MOD_file_H
#define MOD_file_H
#include <stdlib.h>
#include "wwrap/osfile.h"
//#include "wwrap/osdir.h"
//#include "wwrap/str.h"
#include "wwrap/conststr.h"
#include "wwrap/osio.h"
#ifdef OS_WIN
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
//_findfirst
#include <io.h>
#include <math.h>
#include <time.h>
#include <limits.h>
//für _getdrives()
#include<direct.h>
#endif
#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER
#include "file/file.hh"
template<class T> class DIRECTORY;
template<class T> class TreeWalkCallback;
#include "file/import/prokee.h"

class file
{
public:
    
    template<class T> static FILE *openfile(const T *path,const T *name,const T *mode);
    template<class T> static FILE *openfile(const T *filename,const T *mode);
    template<class T> static FILE *openfile(const T *filename);
    
    template<class T> static void *readfile(const T *filename,unsigned int *length);
    template<class T> static char *readfile_as_string(const T *filename,unsigned int *length);
    template<class T> static void *readfile(const T *filename,void *data,unsigned int *ln);
    static void *readfile(FILE *f,void *data,unsigned int *ln);
    
    
    template<class T> static bool writefile(const T *filename,void *data,unsigned int length);
    template<class T> static bool appendfile(const T *filename,void *data,unsigned int length);
    static int writefilef(FILE *file,void *data,unsigned int length);
    static int writefilef(int file,void *data,unsigned int length);
    template<class T> static T *write_newfile(const T *filename,void *data,unsigned int length);
    
    
    template<class T> static bool testfile(const T *path);
    template<class T> static bool testfile_open(const T *path);
    
    template<class T> static bool copyfile(const T *targetpath,const T *sourcepath);
    template<class T> static bool copyfile(const T *targetpath,const T *sourcepath,const T *filename);
    static bool copyfile(FILE *targetfile,FILE *sourcefile);
    static bool copyfile(int targetfile,int sourcefile);
    template<class T> static bool copyfile(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc);
    template<class T> static bool copyfile(const T *targetpath,const T *sourcepath,const T *filename,CondCopyControl<T> *cc);
    template<class T> static size_t copyfile(FILE *targetfile,FILE *sourcefile,CondCopyControl<T> *cc);
    template<class T> static size_t copyfile(int targetfile,int sourcefile,CondCopyControl<T> *cc);
    
    template<class T> static bool compare(const T *patha,const T *pathb);
    
    template<class T> static time_t get_time_write(const T *filename);
    template<class T> static unsigned long get_size(const T *filename);
    
    template<class T> static bool remove(const T *filename);
    template<class T> static bool remove_clean(const T *filename);
};
#include "file/import/modules.h"
template<class T> FILE *file::openfile(const T *path,const T *name,const T *mode)
{
    T *filename=(T *)malloc((str::len(path)+str::len(name)+1)*sizeof(T));
    str::cpy(filename,path);
    str::cat(filename,name);
    FILE *f=file::openfile(filename,mode);
    free(filename);
    return f;
}
template<class T> FILE *file::openfile(const T *filename,const T *mode)
{
    T a[3];conststr::cast(a,"w");
    T b[3];conststr::cast(b,"a");
    if(mode[0]==a[0] || mode[0]==b[0])//str::cmp(mode,conststr::cast(a,"wb"))==0 || str::cmp(mode,conststr::cast(a,"wt"))==0)
    {
        dir::createdir(filename);
    }
    return osfile::open(filename,mode);
}
template<class T> FILE *file::openfile(const T *filename)
{
    T a[3];
    return file::openfile(filename,conststr::cast(a,"rb"));
}
template<class T> void *file::readfile(const T *filename,unsigned int *length)
{
    unsigned int file_length=osfile::get_size(filename);
    if(length)*length=file_length;
    char *data=(char *)malloc((file_length+1)*sizeof(char));
    if(file::readfile(filename,data,0))return data;
    free(data);
    if(length)*length=0;
    return 0;
}
template<class T> char *file::readfile_as_string(const T *filename,unsigned int *length)
{
    unsigned int file_length=osfile::get_size(filename);
    if(length)*length=file_length;
    char *data=(char *)malloc((file_length+1)*sizeof(char));
    if(file::readfile(filename,data,0))
    {
        data[file_length]=0;
        return data;
    }
    free(data);
    if(length)*length=0;
    return 0;
}
template<class T> void *file::readfile(const T *filename,void *data,unsigned int *ln)
{
    FILE *f=file::openfile(filename);
    if(!f)return 0;
    file::readfile(f,data,ln);
    fclose(f);
    return data;
}
template<class T> bool file::writefile(const T *filename,void *data,unsigned int length)
{
    T a[3];
    FILE *f=file::openfile(filename,conststr::cast(a,"wb"));
    if(f)
    {
        int i=writefilef(f,data,length);
        printf("wrote %d bytes\n",i);
        fclose(f);
        return true;
    }
    return false;
}
template<class T> bool file::appendfile(const T *filename,void *data,unsigned int length)
{
    T a[3];
    FILE *f=file::openfile(filename,conststr::cast(a,"ab"));
    if(f)
    {
        int i=writefilef(f,data,length);
        printf("wrote %d bytes\n",i);
        fclose(f);
        return true;
    }
    return false;
}
template<class T> T *file::write_newfile(const T *filename,void *data,unsigned int length)
{
    T a[6];
    conststr::cast(a,".()0_");
    T *newfilename=(T *)malloc((str::len(filename)+100)*sizeof(T));
    str::cpy(newfilename,filename);
    if(testfile(newfilename))
    {
        unsigned int pos;
        int counter=0;
        T *path=path::dnopath(filename);
        const T *cname=path::fnopath(filename);
        T *name=(T *)malloc((str::len(cname)+1)*sizeof(T));
        str::cpy(name,cname);
        const T *suffix=path::sxopath(filename);
        int i=str::len(name)-1;
        while(i>0)
        {
            if(name[i]==a[0])
            {
                name[i]=0;
                break;
            }
            i--;
        }
        while(true)
        {
            str::cpy(newfilename,path);
            str::cat(newfilename,name);
            pos=str::len(newfilename);
            newfilename[pos]=a[4];
            newfilename[pos+1]=a[1];
            newfilename[pos+2]=0;
            if(counter<1000)
            {
                newfilename[pos+2]=a[3];
                newfilename[pos+3]=0;
            }
            if(counter<100)
            {
                newfilename[pos+3]=a[3];
                newfilename[pos+4]=0;
            }
            if(counter<10)
            {
                newfilename[pos+4]=a[3];
                newfilename[pos+5]=0;
            }
            //--TODO--
            //osio::sprint(&newfilename[str::len(newfilename)],"%d",counter);
            pos=str::len(newfilename);
            newfilename[pos]=a[2];
            newfilename[pos+1]=a[0];
            newfilename[pos+2]=0;
            str::cat(newfilename,suffix);
            if(!testfile(newfilename))
            {
                break;
            }
            counter++;
        }
        free(name);
    }
    if(writefile(newfilename,data,length))
    {
        return newfilename;
    }
    return 0;
}

template<class T> bool file::testfile_open(const T *path)
{
    //Testet ob die angegebene Datei geoeffnet werden kann.
    T a[3];
    FILE *f=file::openfile(path,conststr::cast(a,"rb"));
    if(f)
    {
        fclose(f);
        return true;
    }
    return false;
}
template<class T> bool file::testfile(const T *path)
{
    return osfile::testfile(path);
}
template<class T> bool file::copyfile(const T *targetpath,const T *sourcepath)
{
    FILE *targetfile;
    FILE *sourcefile;
    bool retVal=false;
    T a[3];
    if(path::pathtype(sourcepath) & PATH_DIR)
    {
        return false;
    }
    else
    {
        sourcefile=file::openfile(sourcepath,conststr::cast(a,"rb"));
        if(!sourcefile)return false;
    }
    if(path::pathtype(targetpath) & PATH_DIR)
    {
        targetfile=file::openfile(targetpath,path::fnopath(sourcepath),conststr::cast(a,"wb"));
    }
    else
    {
        targetfile=file::openfile(targetpath,conststr::cast(a,"wb"));
    }
    if(targetfile)
    {
        retVal=file::copyfile(targetfile,sourcefile);
        fclose(targetfile);
    }
    fclose(sourcefile);
    return retVal;
}
template<class T> bool file::copyfile(const T *targetpath,const T *sourcepath,const T *filename)
{
    T *a=(T *)malloc((str::len(sourcepath)+str::len(filename)+2)*sizeof(T));
    T *b=(T *)malloc((str::len(targetpath)+str::len(filename)+2)*sizeof(T));
    str::cpy(a,sourcepath);
    str::cat(a,filename);
    str::cpy(b,targetpath);
    str::cat(b,filename);
    bool retVal=file::copyfile(b,a);
    free(a);
    free(b);
    return retVal;
}
template<class T> bool file::copyfile(const T *targetpath,const T *sourcepath,CondCopyControl<T> *cc)
{
    FILE *targetfile;
    FILE *sourcefile;
    bool retVal=false;
    T a[3];
    T *tp=(T *)malloc((str::len(targetpath)+str::len(sourcepath)+2)*sizeof(T));
    str::cpy(tp,targetpath);
    if(path::pathtype(targetpath) & PATH_DIR)
    {
        str::cat(tp,path::fnopath(sourcepath));
    }
    if(!cc->doCopyFile(tp,sourcepath))
    {
        free(tp);
        return true;
    }
    if(path::pathtype(sourcepath) & PATH_DIR)
    {
        free(tp);
        return false;
    }
    else
    {
        sourcefile=file::openfile(sourcepath,conststr::cast(a,"rb"));
        if(!sourcefile)
        {
            free(tp);
            return false;
        }
    }
    targetfile=file::openfile(tp,conststr::cast(a,"wb"));
    if(targetfile)
    {
        int ln=file::copyfile(targetfile,sourcefile,cc);
        fclose(targetfile);
        if(ln!=-1)
        {
            cc->filecopied(tp,sourcepath,ln);
            retVal=true;
        }
    }
    fclose(sourcefile);
    free(tp);
    return retVal;
}
template<class T> bool file::copyfile(const T *targetpath,const T *sourcepath,const T *filename,CondCopyControl<T> *cc)
{
    T *a=(T *)malloc((str::len(sourcepath)+str::len(filename)+2)*sizeof(T));
    T *b=(T *)malloc((str::len(targetpath)+str::len(filename)+2)*sizeof(T));
    str::cpy(a,sourcepath);
    str::cat(a,filename);
    str::cpy(b,targetpath);
    str::cat(b,filename);
    bool retVal=file::copyfile(b,a,cc);
    free(a);
    free(b);
    return retVal;
}
template<class T> size_t file::copyfile(FILE *targetfile,FILE *sourcefile,CondCopyControl<T> *cc)
{
    char a[BUFSIZ];
    size_t ln=1;
    size_t fbytes=cc->feedback_bytes();
    size_t bytecount=0;
    while(ln)
    {
        ln=fread(a,1,BUFSIZ,sourcefile);
        fwrite(a,1,ln,targetfile);
        bytecount+=ln;
        if(bytecount%fbytes<BUFSIZ)cc->feedback();
    }
    return bytecount;
}
template<class T> size_t file::copyfile(int targetfile,int sourcefile,CondCopyControl<T> *cc)
{
    char a[BUFSIZ];
    size_t ln=1;
    size_t fbytes=cc->feedback_bytes();
    size_t bytecount=0;
    while(ln>0)
    {
        ln=read(sourcefile,a,BUFSIZ);
        write(targetfile,a,ln);
        bytecount+=ln;
        if(bytecount%fbytes<BUFSIZ)cc->feedback();
    }
    return bytecount;
}
template<class T> bool file::compare(const T *patha,const T *pathb)
{
    unsigned long al=osfile::get_size(patha);
    unsigned long bl=osfile::get_size(pathb);
    if(al!=bl)return false;
    T m[3];
    conststr::cast(m,"rb");
    FILE *fa=osfile::open(patha,m);
    if(!fa)return false;
    FILE *fb=osfile::open(pathb,m);
    if(!fb){fclose(fa);return false;}
    char a[BUFSIZ];
    char b[BUFSIZ];
    size_t lna=1,lnb=1;
    unsigned int i;
    while(lna)
    {
        lna=fread(a,1,BUFSIZ,fa);
        lnb=fread(b,1,BUFSIZ,fb);
        if(lna!=lnb){fclose(fa);fclose(fb);return false;}
        for(i=0;i<lna;i++)
        {
            if(a[i]!=b[i]){fclose(fa);fclose(fb);return false;}
        }
    }
    fclose(fa);
    fclose(fb);
    return true;
}
template<class T> time_t file::get_time_write(const T *filename)
{
    return osfile::get_time_write(filename);
}
template<class T> unsigned long file::get_size(const T *filename)
{
    return osfile::get_size(filename);
}
template<class T> bool file::remove(const T *filename)
{
    return osfile::rm(filename);
}
template<class T> bool file::remove_clean(const T *filename)
{
    bool b=true;
    bool retval=osfile::rm(filename);
    if(retval)
    {
        T *tmp=(T *)malloc((str::len(filename)+1)*sizeof(T));
        str::cpy(tmp,filename);
        while(b)
        {
            T *dirpath=path::pnopath(tmp);
            b=dir::deletedir(dirpath);
            str::cpy(tmp,dirpath);
            free(dirpath);
        }
        free(tmp);
    }
    return retval;
}
#endif
