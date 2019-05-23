#ifndef strman_import_modules
#define strman_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "strman/strman.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_strman

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "strman/strman.hh2"
#endif

#endif

#endif
