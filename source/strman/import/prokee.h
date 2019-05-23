#ifndef strman_import_prokee
#define strman_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/strman/inc/interface/import/all.fw"
#include "../../interface/prokee/strman/inc/wrapper/import/all.fw"

#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_strman

//Local classes


//Interface declarations of this module
#include "strman/strman.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "strman/strman.hh"

//Interface declarations of other required modules
#include "strconv/strconv.hh"


#endif
#endif
