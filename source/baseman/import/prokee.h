#ifndef baseman_import_prokee
#define baseman_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



class Reader;

#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/baseman/inc/interface/import/all.fw"
#include "../../interface/prokee/baseman/inc/wrapper/import/all.fw"

#include "csv/v01/module.h"
#include "settings/v01/module.h"
#include "reader/v01/module.h"
#include "file/v01/module.h"
#include "dir/v01/module.h"
#include "path/v01/module.h"
#include "strman/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_baseman

//Local classes


//Interface declarations of this module
#include "baseman/baseman.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "baseman/baseman.hh"

//Interface declarations of other required modules
#include "csv/csv.hh"
#include "settings/settings.hh"
#include "reader/reader.hh"
#include "file/file.hh"
#include "dir/dir.hh"
#include "path/path.hh"
#include "strman/strman.hh"
#include "strconv/strconv.hh"


#endif
#endif
