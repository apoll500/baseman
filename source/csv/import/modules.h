#ifndef csv_import_modules
#define csv_import_modules

#ifndef COMPILE_PROKEE_MODULE

//Include required modules
#include "file/file.h"
#include "reader/reader.h"
#include "strconv/strconv.h"


//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "csv/csv.hh2"
#endif

#ifdef PROKEE_USE_INTERFACE
#include "file/file.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "reader/reader.hh2"
#endif
#ifdef PROKEE_USE_INTERFACE
#include "strconv/strconv.hh2"
#endif


#endif

#ifdef COMPILE_MODULE_csv

//Local module headers


#ifdef PROKEE_USE_INTERFACE
#include "csv/csv.hh2"
#endif

#endif

#endif
