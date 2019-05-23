//------------------------------------------------------------------------------
//AbsUniFileReader_INTERFACE
//------------------------------------------------------------------------------
#include <uchar.h>

class AbsUniFileReader3:virtual public FileReader,virtual public AbsUniFileReader2
{
public:
    //DESTRUCTOR--------------------------------------------------------
    virtual ~AbsUniFileReader3(){}
    //SUPERCLASS METHOD WRAPPER ----------------------------------------
    
    int getLine(){return FileReader::getLine();}
    
    
    int getColumn(){return FileReader::getColumn();}
    
    
    int get(){return FileReader::get();}
    
    
    int getChar(){return FileReader::getChar();}
    
    
    int getLastError(){return FileReader::getLastError();}
    
    
    int getLastErrorDetail(){return FileReader::getLastErrorDetail();}
    
    
    void resetLastError(){FileReader::resetLastError();}
    
    
    int getCurrLine(){return FileReader::getCurrLine();}
    
    
    int getCurrColumn(){return FileReader::getCurrColumn();}
    
    
    void setCurrLine(int n){FileReader::setCurrLine(n);}
    
    
    void setCurrColumn(int n){FileReader::setCurrColumn(n);}
    
};

