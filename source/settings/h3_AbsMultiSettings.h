/*******************************************************************************
*                                                                              *
*  h3_AbsMultiSettings.h                                                       *
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
//------------------------------------------------------------------------------
//AbsMultiSettings_INTERFACE
//------------------------------------------------------------------------------
class Reader;

class AbsMultiSettings3:virtual public Settings,virtual public AbsMultiSettings2
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsMultiSettings3(){}
    //SUPERCLASS METHOD WRAPPER ----------------------------------------
    
    bool loadfile(const char *filename){return Settings::loadfile(filename);}
    
    
    bool loadfile(const char *filename,bool docreate){return Settings::loadfile(filename,docreate);}
    
    
    int getDefBlockCount(){return Settings::getDefBlockCount();}
    
    
    std::string getNextDefBlockName(){return Settings::getNextDefBlockName();}
    
    
    void updateDefBlockNames(){Settings::updateDefBlockNames();}
    
    
    void insert(std::string defName,std::string name,std::string value){Settings::insert(defName,name,value);}
    
    
    void set(std::string defName,std::string name,std::string value){Settings::set(defName,name,value);}
    
    
    void set(std::string defName,std::string name,int i,std::string value){Settings::set(defName,name,i,value);}
    
    
    std::string get(std::string defName,std::string name){return Settings::get(defName,name);}
    
    
    std::string get(std::string defName,std::string name,int i){return Settings::get(defName,name,i);}
    
    
    bool exists(std::string defName,std::string name){return Settings::exists(defName,name);}
    
    
    bool exists(std::string defName,std::string name,int i){return Settings::exists(defName,name,i);}
    
    
    int getNameCount(std::string defName){return Settings::getNameCount(defName);}
    
    
    int getNameCount(std::string defName,std::string name){return Settings::getNameCount(defName,name);}
    
    
    std::string getNextName(std::string defName){return Settings::getNextName(defName);}
    
    
    std::string getNextName(std::string defName,std::string name){return Settings::getNextName(defName,name);}
    
    
    std::string getNextValue(std::string defName,std::string name){return Settings::getNextValue(defName,name);}
    
    
    void save(const char *filename){Settings::save(filename);}
    
    
    bool save2(const char *filename){return Settings::save2(filename);}
    
};

