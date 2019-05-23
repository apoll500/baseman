#ifndef dir_import_modules
#define dir_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "file/file.h"
#include "label/label.h"
#include "path/path.h"
#include "strman/strman.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "dir/dir.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "label/label.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "path/path.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strman/strman.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_dir

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "dir/dir.hh2"
#endif

#endif

#endif
