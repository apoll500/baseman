#ifndef H_WWRAP_EXE_LIN
#define H_WWRAP_EXE_LIN

#include <stdio.h>

//#include "../blib/strman.h"
//#include "../IniSettings/IniSettingsM.hpp"
//extern IniSettingsM *ini;

#include <string>
#include <string.h>

class osexe
{
public:
    static int myShellExecute(void *,const char *action,const char *filename,const char *,const char *,int)
    {
        std::string a;
        if(strman::isprefix("http://",filename) || strman::isprefix("https://",filename))
        {
            if(strcmp(action,"open")==0)
            {
                a=ini->get("main","browser");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
        }
        else
        {
            if(strcmp(action,"open")==0)
            {
                a=ini->get("main","fileman");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
            else if(strcmp(action,"edit")==0)
            {
                a=ini->get("main","editor");
                if(a=="")a="xdg-open";
                a=a+" "+filename+" &";
                printf("> %s\n",a.c_str());
                system(a.c_str());
            }
        }
        return 0;
    }
};

#endif
