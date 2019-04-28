#ifndef H_WWRAP_EXE_WIN
#define H_WWRAP_EXE_WIN

#include <stdio.h>
#include <windows.h>

class osexe
{
public:
    static int myShellExecute(HWND hwnd,const char *action,const char *filename,const char *parameter,const char *workingDirectory,int show)
    {
        return (long long)ShellExecuteA(hwnd,action,filename,parameter,workingDirectory,show);
    }
    static int myShellExecute(HWND hwnd,const wchar_t *action,const wchar_t *filename,const wchar_t *parameter,const wchar_t *workingDirectory,int show)
    {
        return (long long)ShellExecuteW(hwnd,action,filename,parameter,workingDirectory,show);
    }
};

#endif
