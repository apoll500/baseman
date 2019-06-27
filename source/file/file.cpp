/*******************************************************************************
*                                                                              *
*  file.cpp                                                                    *
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
#include "file.h"
bool file::copyfile(FILE *targetfile,FILE *sourcefile)
{
    char a[BUFSIZ];
    size_t ln=1;
    while(ln)
    {
        ln=fread(a,1,BUFSIZ,sourcefile);
        fwrite(a,1,ln,targetfile);
    }
    return true;
}
bool file::copyfile(int targetfile,int sourcefile)
{
    char a[BUFSIZ];
    size_t ln=1;
    while(ln>0)
    {
        ln=read(sourcefile,a,BUFSIZ);
        write(targetfile,a,ln);
    }
    return true;
}
void *file::readfile(FILE *f,void *data,unsigned int *ln)
{
    size_t bln=1;
    size_t bytecount=0;
    while(bln)
    {
        bln=fread(&((char *)data)[bytecount],1,BUFSIZ,f);
        bytecount+=bln;
    }
    if(ln)*ln=bytecount;
    return data;
}

int file::writefilef(FILE *file,void *data,unsigned int length)
{
    return fwrite(data,1,length,file);
}
int file::writefilef(int file,void *data,unsigned int length)
{
    return write(file,data,length);
}
