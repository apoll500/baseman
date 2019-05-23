#ifndef base64_import_prokee
#define base64_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/base64/inc/interface/import/all.fw"
#include "../../interface/prokee/base64/inc/wrapper/import/all.fw"

#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_base64

//Local classes


//Interface declarations of this module
#include "base64/base64.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "base64/base64.hh"

//Interface declarations of other required modules
#include "strconv/strconv.hh"


#endif
#endif
