#ifndef path_import_prokee
#define path_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER

#define PATH_ABS 1
#define PATH_DIR 2
#define PATH_LAB 4
#define PATH_SYSTEM_LINUX 1
#define PATH_SYSTEM_WINDOWS 2




#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/path/inc/interface/import/all.fw"
#include "../../interface/prokee/path/inc/wrapper/import/all.fw"

#include "file/v01/module.h"
#include "dir/v01/module.h"
#include "strman/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_path

//Local classes


//Interface declarations of this module
#include "path/path.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "path/path.hh"

//Interface declarations of other required modules
#include "file/file.hh"
#include "dir/dir.hh"
#include "strman/strman.hh"
#include "strconv/strconv.hh"


#endif
#endif
