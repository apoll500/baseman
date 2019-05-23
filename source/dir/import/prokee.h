#ifndef dir_import_prokee
#define dir_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/dir/inc/interface/import/all.fw"
#include "../../interface/prokee/dir/inc/wrapper/import/all.fw"

#include "file/v01/module.h"
#include "label/v01/module.h"
#include "path/v01/module.h"
#include "strman/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_dir

//Local classes


//Interface declarations of this module
#include "dir/dir.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "dir/dir.hh"

//Interface declarations of other required modules
#include "file/file.hh"
#include "label/label.hh"
#include "path/path.hh"
#include "strman/strman.hh"
#include "strconv/strconv.hh"


#endif
#endif
