#ifndef settings_import_modules
#define settings_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "file/file.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "settings/settings.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_settings

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "settings/settings.hh2"
#endif

#endif

#endif
