/*******************************************************************************
*                                                                              *
*  CsvData.cpp                                                                 *
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
#include "CsvData.h"
#include "csv.h"

CsvData::CsvData()
{
    settings=new CsvSettings(',','\n','\"');
    header=false;
    data_memln=CSV_INI_DAT_LENGTH;
    data=(CsvRecord **)malloc((data_memln+1)*sizeof(CsvRecord *));
    data_size=0;
}
CsvData::~CsvData()
{
    for(int i=0; i<data_size; i++)
    {
        delete data[i];
    }
    delete settings;
}
int CsvData::load(const char *filename,const char *docreate)
{
    if(load(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=fopen(filename,"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load(filename);
        }
    }
    return -1;
}
int CsvData::load(const char *filename)
{
    //Reader *r=ReaderInterface::createFileReader(filename);
    FileReader *r=new FileReader(filename);
    if(r->getLastError())return -1;
    load(r);
    delete r;
    return 0;
}
#ifdef OS_WIN
int CsvData::load(const wchar_t *filename,const char *docreate)
{
    if(load(filename)==0)return 0;
    else if(docreate)
    {
        FILE *f=_wfopen(filename,L"wb");
        if(f)
        {
            fprintf(f,"%s",docreate);
            fclose(f);
            return load(filename);
        }
    }
    return -1;
}
#endif
#ifdef OS_WIN
int CsvData::load(const wchar_t *filename)
{
    //Reader *r=ReaderInterface::createFileReader(filename);
    FileReader *r=new FileReader(filename);
    if(r->getLastError())return -1;
    load(r);
    return 0;
}
#endif
int CsvData::load(FileReader *r)
{
    int h=1;
    while(h==1)
    {
        //AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
        CsvRecord *rec=new CsvRecord(this);
        h=rec->load(r);
        addRecord(rec);
    }
    return 0;
}
void CsvData::addRecord(CsvRecord *rec)
{
    if(data_size>=data_memln)
    {
        data_memln*=2;
        data=(CsvRecord **)realloc(data,(data_memln+1)*sizeof(CsvRecord *));
    }
    data[data_size++]=rec;
}
CsvRecord *CsvData::load_rec(FileReader *r)
{
    CsvRecord *rec=new CsvRecord(this);
    rec->load(r);
    return rec;
}
void CsvData::useHeader(bool h)
{
    header=h;
}
int CsvData::getHeaderId(const char *col)
{
    if(!header)return -1;
    return data[0]->match(col);
}
char *CsvData::getHeader(int column_id)
{
    if(!header)return 0;
    if(column_id<0 || column_id>=data[0]->get_record_size())return 0;
    return data[0]->getField(column_id);
}
bool CsvData::setField(int row,int col,const char *val)
{
    CsvRecord *rec=getRecord(row);
    if(!rec)return false;
    return rec->setField(col,val);
}
bool CsvData::setField(int row,const char *col,const char *val)
{
    int c=getHeaderId(col);
    if(c==-1)return false;
    return setField(row,c,val);
}
int CsvData::addRecord()
{
    if(header)return addRecord(data[0]->get_record_size());
    //AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
    CsvRecord *rec=new CsvRecord(this);
    addRecord(rec);
    return data_size-1;
}
int CsvData::addRecord(int fldcount)
{
    //AbsCsvRecord *rec=AbsCsvRecordInterface::createCsvRecord(this);
    CsvRecord *rec=new CsvRecord(this);
    addRecord(rec);
    int i,row=data_size-1;

    for(i=0; i<fldcount; i++)addFieldToRecord(row);
    return row;
}
bool CsvData::addFieldToRecord(int row)
{
    CsvRecord *rec=getRecord(row);
    if(!rec)return false;
    rec->addField();
    return true;
}
CsvRecord *CsvData::getRecord(int col,const char *val)
{
    for(int i=0; i<data_size; i++)
    {
        if(data[i]->match(col,val))
        {
            return data[i];
        }
    }

    return 0;
}
CsvRecord *CsvData::getRecord(int *col,const char **val)
{
    int ln=iln(col);
    int j;

    for(int i=0; i<data_size; i++)
    {
        for(j=0; j<ln; j++)
        {
            if(!data[i]->match(col[j],val[j]))break;
        }
        if(j==ln)
        {
            return data[i];
        }
    }

    return 0;
}
CsvRecord *CsvData::getRecord(int row)
{
    int rrow;
    if(row>=0)rrow=row;
    else rrow=data_size+row;
    if(rrow<0 || rrow>=data_size)return 0;
    return data[rrow];
}
CsvRecord *CsvData::getRecord(const char *col,const char *val)
{
    if(!header)return 0;
    int c=getHeaderId(col);
    if(c<0)return 0;
    return getRecord(c,val);
}
CsvRecord *CsvData::getRecord(const char **col,const char **val)
{
    if(!header)return 0;

    int ln=aln(col);
    int *c=(int *)malloc((ln+1)*sizeof(int));
    int i;

    for(i=0; i<ln; i++)
    {
        c[i]=getHeaderId(col[i]);
        if(c[i]<0)
        {
            free(c);
            return 0;
        }
    }
    c[ln]=INT_MAX;

    CsvRecord *r=getRecord(c,val);
    free(c);
    return r;
}
CsvRecord **CsvData::getAllRecords(int col,const char *val)
{
    int rpos=0,rmax=16;
    CsvRecord **r;
    r=(CsvRecord **)malloc((rmax+1)*sizeof(CsvRecord *));
    for(int i=0; i<data_size; i++)
    {
        if(data[i]->match(col,val))
        {
            if(rpos>=rmax)
            {
                rmax*=2;
                r=(CsvRecord **)realloc(r,(rmax+1)*sizeof(CsvRecord *));
            }
            r[rpos++]=data[i];
        }
    }
    r[rpos]=0;

    return r;
}
CsvRecord **CsvData::getAllRecords()
{
    CsvRecord **r;
    int rpos=0,rmax=data_size;
    r=(CsvRecord **)malloc((rmax+1)*sizeof(CsvRecord *));
    for(int i=header; i<data_size; i++)
    {
        if(rpos>=rmax)
        {
            rmax*=2;
            r=(CsvRecord **)realloc(r,(rmax+1)*sizeof(CsvRecord *));
        }
        r[rpos++]=data[i];
    }
    r[rpos]=0;

    return r;
}
CsvRecord **CsvData::getAllRecords(const char *col,const char *val)
{
    if(!header)return 0;
    int c=getHeaderId(col);
    if(c<0)return 0;
    return getAllRecords(c,val);
}
bool CsvData::save(const char *filename)
{
    FILE *f=fopen(filename,"wb");
    if(!f)return false;
    print(f);
    fclose(f);
    return true;
}
void CsvData::print(FILE *f)
{
    for(int i=0; i<data_size; i++)
    {
        data[i]->print(f);
        if(i+1<data_size)fprintf(f,"%c",settings->record_seperator_out);
    }
}
void CsvData::print(FILE *f,int *row,int *col)
{
    int ln=data_size;
    int i,p=0;
    if(row)qsort(row,iln(row),sizeof(int),cmpi);
    for(i=0; i<ln; i++)
    {
        if(row)
        {
            if(i==row[p])
            {
                if(col==0)data[i]->print(f);
                else data[i]->print(f,col);
                if(i<ln)fprintf(f,"%c",settings->record_seperator_out);
                while(row[p]==row[p+1])
                {
                    p++;
                }
                p++;
                if(row[p]==INT_MAX)break;
            }
        }
        else
        {
            if(col==0)data[i]->print(f);
            else data[i]->print(f,col);
            if(i<ln)fprintf(f,"%c",settings->record_seperator_out);
        }
    }
}
