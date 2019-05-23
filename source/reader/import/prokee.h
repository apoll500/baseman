#ifndef reader_import_prokee
#define reader_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/reader/inc/interface/import/all.fw"
#include "../../interface/prokee/reader/inc/wrapper/import/all.fw"

#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_reader

//Local classes


//Interface declarations of this module
#include "reader/reader.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "reader/reader.hh"

//Interface declarations of other required modules
#include "strconv/strconv.hh"


#endif
#endif
