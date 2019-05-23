#ifndef settings_import_prokee
#define settings_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



#include <string>

#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/settings/inc/interface/import/all.fw"
#include "../../interface/prokee/settings/inc/wrapper/import/all.fw"

#include "file/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_settings

//Local classes


//Interface declarations of this module
#include "settings/settings.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "settings/settings.hh"

//Interface declarations of other required modules
#include "file/file.hh"
#include "strconv/strconv.hh"


#endif
#endif
