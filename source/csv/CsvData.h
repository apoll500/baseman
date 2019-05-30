/*******************************************************************************
*                                                                              *
*  CsvData.h                                                                   *
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
#ifndef CsvData_H
#define CsvData_H
#include <stdio.h>
#include <vector>
#include "csv/import/prokee.h"
#include "csv.hh"
//#include "CsvRecord.h"
#define CSV_INI_DAT_LENGTH 32

class CsvData:public AbsCsvData2
{
public:
    
    //CsvSettings *settings;//specification of csv input and output format
private:
    //std::vector<CsvRecord> data;
    AbsCsvRecord **data;
    int data_memln;
    int data_size;
    bool header;//set to true if first line contains header
public:
    //----------------------------------------------------
    // Constructors
    //----------------------------------------------------
    CsvData();
    ~CsvData();
    //----------------------------------------------------
    // Interface
    //----------------------------------------------------
    //load file
#ifdef OS_WIN
    int load(const wchar_t *filename,const char *docreate);
    //int load_wcs(const wchar_t *filename,const char *docreate);
    int load(const wchar_t *filename);
    //int load_wcs(const wchar_t *filename);
#endif
    int load(const char *filename,const char *docreate);
    //int load_wcs(const char *filename,const char *docreate);
    int load(const char *filename);
    //int load_wcs(const char *filename);
    int load(Reader *r);
    void addRecord(AbsCsvRecord *rec);
    //load next record
    AbsCsvRecord *load_rec(Reader *r);
    int get_record_count();
    //header
    void useHeader(bool h);
    int getHeaderId(const char *col);
    char *getHeader(int column_id);
    //set record
    bool setField(int row,int col,const char *val);
    bool setField(int row,const char *col,const char *val);
    int addRecord();
    int addRecord(int fldcount);
    bool addFieldToRecord(int row);
    //void delRecord(int row);
    //get record
    AbsCsvRecord *getRecord(int col,const char *val);
    AbsCsvRecord *getRecord(int *col,const char **val);
    AbsCsvRecord *getRecord(int row);
    AbsCsvRecord *getRecord(const char *col,const char *val);
    AbsCsvRecord *getRecord(const char **col,const char **val);
    AbsCsvRecord **getAllRecords(int col,const char *val);
    AbsCsvRecord **getAllRecords();
    AbsCsvRecord **getAllRecords(const char *col,const char *val);
    //print
    bool save(const char *filename);
    void print(FILE *f);
    void print(FILE *f,int *row,int *col);
    //copy
    //void copy(Reader *r,FILE *f,int *row,int *col);
};

#endif
