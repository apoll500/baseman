#ifndef reader_import_modules
#define reader_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "reader/reader.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_reader

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "reader/reader.hh2"
#endif

#endif

#endif
