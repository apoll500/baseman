#ifndef bmsetup_import_modules
#define bmsetup_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "csv/csv.h"
#include "settings/settings.h"
#include "file/file.h"
#include "dir/dir.h"
#include "path/path.h"
#include "base64/base64.h"
#include "strman/strman.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "bmsetup/bmsetup.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "csv/csv.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "settings/settings.hh2"
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
#include "base64/base64.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strman/strman.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_bmsetup

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "bmsetup/bmsetup.hh2"
#endif

#endif

#endif
