#ifndef H_WWRAP_EXE
#define H_WWRAP_EXE

#include "../macros/macros.h"

#ifdef OS_WIN
#ifdef OS_WIN_WCS
#include "osexe_wwin.h"
#else
#include "osexe_win.h"
#endif
#elif defined OS_LIN
#include "osexe_lin.h"
#endif

#endif
