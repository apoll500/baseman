#ifndef H_WWRAP_EXE_WWIN
#define H_WWRAP_EXE_WWIN

#include "macros/macros.h"

//------------------------------------------------------------------------------
/*
#ifdef COMPILE_PROKEE_MODULE
#define PROKEE_USE_WRAPPER
#include "strconv/v01/module.h"
#else
#include "strconv/strconv.h"
#endif
*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#ifdef COMPILE_PROKEE_MODULE
#ifndef COMPILE_PROKEE_MODULE_NO_STRCONV
#define PROKEE_USE_WRAPPER
#include "strconv/v01/module.h"
#else
#include "strconv/strconv.h"
#endif
#else
#include "strconv/strconv.h"
#endif
//------------------------------------------------------------------------------

#include <stdio.h>
#include <windows.h>

class osexe
{
public:
    static int myShellExecute(HWND hwnd,const char *action,const char *filename,const char *parameter,const char *workingDirectory,int show)
    {
        int retv=0;
        wchar_t *w_action=0;
        wchar_t *w_filename=0;
        wchar_t *w_parameter=0;
        wchar_t *w_workingDirectory=0;
        strconv::to_wcs(&w_action,0,action);
        strconv::to_wcs(&w_filename,0,filename);
        strconv::to_wcs(&w_parameter,0,parameter);
        strconv::to_wcs(&w_workingDirectory,0,workingDirectory);
        if(w_action && w_filename && w_parameter && w_workingDirectory)
        {
            retv=(long long)ShellExecuteW(hwnd,w_action,w_filename,w_parameter,w_workingDirectory,show);
        }
        if(w_action)free(w_action);
        if(w_filename)free(w_filename);
        if(w_parameter)free(w_parameter);
        if(w_workingDirectory)free(w_workingDirectory);
        return retv;
    }
    static int myShellExecute(HWND hwnd,const wchar_t *action,const wchar_t *filename,const wchar_t *parameter,const wchar_t *workingDirectory,int show)
    {
        return (long long)ShellExecuteW(hwnd,action,filename,parameter,workingDirectory,show);
    }
};

#endif
