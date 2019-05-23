#ifndef baseman_import_modules
#define baseman_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "csv/csv.h"
#include "settings/settings.h"
#include "reader/reader.h"
#include "file/file.h"
#include "dir/dir.h"
#include "path/path.h"
#include "strman/strman.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "baseman/baseman.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "csv/csv.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "settings/settings.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "reader/reader.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "dir/dir.hh2"
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

#ifdef COMPILE_MODULE_baseman

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "baseman/baseman.hh2"
#endif

#endif

#endif
