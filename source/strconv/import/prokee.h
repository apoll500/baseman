#ifndef strconv_import_prokee
#define strconv_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER





#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/strconv/inc/interface/import/all.fw"
#include "../../interface/prokee/strconv/inc/wrapper/import/all.fw"



#ifdef COMPILE_MODULE_strconv

//Local classes


//Interface declarations of this module
#include "strconv/strconv.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "strconv/strconv.hh"

//Interface declarations of other required modules


#endif
#endif
