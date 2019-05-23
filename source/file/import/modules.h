#ifndef file_import_modules
#define file_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "strconv/strconv.h"
#include "dir/dir.h"
#include "path/path.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "dir/dir.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "path/path.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_file

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif

#endif

#endif
