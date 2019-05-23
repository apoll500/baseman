#ifndef bmsetup_import_prokee
#define bmsetup_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/bmsetup/inc/interface/import/all.fw"
#include "../../interface/prokee/bmsetup/inc/wrapper/import/all.fw"

#include "csv/v01/module.h"
#include "settings/v01/module.h"
#include "file/v01/module.h"
#include "dir/v01/module.h"
#include "path/v01/module.h"
#include "base64/v01/module.h"
#include "strman/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_bmsetup

//Local classes


//Interface declarations of this module
#include "bmsetup/bmsetup.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "bmsetup/bmsetup.hh"

//Interface declarations of other required modules
#include "csv/csv.hh"
#include "settings/settings.hh"
#include "file/file.hh"
#include "dir/dir.hh"
#include "path/path.hh"
#include "base64/base64.hh"
#include "strman/strman.hh"
#include "strconv/strconv.hh"


#endif
#endif
