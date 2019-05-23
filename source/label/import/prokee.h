#ifndef label_import_prokee
#define label_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/label/inc/interface/import/all.fw"
#include "../../interface/prokee/label/inc/wrapper/import/all.fw"

#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_label

//Local classes


//Interface declarations of this module
#include "label/label.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "label/label.hh"

//Interface declarations of other required modules
#include "strconv/strconv.hh"


#endif
#endif
