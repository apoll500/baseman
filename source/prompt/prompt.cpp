/*******************************************************************************
*                                                                              *
*  prompt.cpp                                                                  *
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
//prompt/code/v01/files/source/prompt/prompt.cpp
#include "prompt.h"
char *readFile(char **buffer,unsigned int *buffer_ln)
{
    int ch=0;
    unsigned int ln=0;
    while(true)
    {
        ch=getchar();
        if(ch==EOF)break;
        if(ln>=*buffer_ln)
        {
            (*buffer_ln)=(*buffer_ln)*2+1;
            *buffer=(char *)realloc(*buffer,(*buffer_ln+1)*sizeof(char));
        }
        (*buffer)[ln]=ch;
        ln++;
    }
    (*buffer)[ln]=0;
    return *buffer;
    
}
int prompt::main(int,char **)
{
    printf("@1> ");
    unsigned int aln=256;
    char *a=(char *)malloc((aln+1)*sizeof(char));
    readFile(&a,&aln);
    printf("\n");
    printf("@2> ");
    unsigned int i=0;
    while(a[i])
    {
        printf("%c",a[i++]);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
