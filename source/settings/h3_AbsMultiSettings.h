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

