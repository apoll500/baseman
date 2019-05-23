#ifndef file_import_prokee
#define file_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/file/inc/interface/import/all.fw"
#include "../../interface/prokee/file/inc/wrapper/import/all.fw"

#include "strconv/v01/module.h"
#include "dir/v01/module.h"
#include "path/v01/module.h"


#ifdef COMPILE_MODULE_file

//Local classes


//Interface declarations of this module
#include "file/file.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "file/file.hh"

//Interface declarations of other required modules
#include "strconv/strconv.hh"
#include "dir/dir.hh"
#include "path/path.hh"


#endif
#endif
