/*******************************************************************************
*                                                                              *
*  FileReader.cpp                                                              *
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
#include "FileReader.hpp"

FileReader::FileReader(FILE *file):ReaderImpl()
{
    f=file;
    file_opened_here=false;
}

FileReader::FileReader(const char *a):ReaderImpl()
{
    //printf("--> reader: open file '%s'\n",a);
    f=fopen(a,"rb");
    if(!f)
    {
        //printf("--> failed to open file '%s'\n",a);
        lastError=READER_ERROR_OPEN_FILE;
        lastErrorDetail=errno;
        file_opened_here=false;
    }
    else
    {
        file_opened_here=true;
    }
}

#ifdef OS_WIN
FileReader::FileReader(const wchar_t *a):ReaderImpl()
{
    f=_wfopen(a,L"rb");
    if(!f)
    {
        lastError=READER_ERROR_OPEN_FILE;
        lastErrorDetail=errno;
        file_opened_here=false;
    }
    else
    {
        file_opened_here=true;
    }
}
#else
FileReader::FileReader(const wchar_t *):ReaderImpl()
{
    //wchar_t version for linux not implemented.
    lastError=READER_ERROR_OPEN_FILE;
    lastErrorDetail=0;
    file_opened_here=false;
    fprintf(stderr,"\n[ERROR] reader: Error while opening file.\nFilename given as (wchar_t *) string. This function is not avalable for OS_LIN!\n");
}
#endif

FileReader::~FileReader()
{
    //printf("--> closing file reader\n");
    if(file_opened_here)fclose(f);
}

int FileReader::getNextChar()
{
    if(!f || feof(f))
    {
        return 0;
    }
    currentChar=fgetc(f);
    return 1;
}
