#ifndef PLIB_CLASS_path_all_hh
#define PLIB_CLASS_path_all_hh

#ifdef PROKEE_USE_INTERFACE

//Foreward declartions of classes
#ifdef COMPILE_PROKEE_MODULE
#include "path/v01/wrapper/import/all.fw"
#include "path/v01/interface/import/all.fw"
//#include "path/path.fw"
#else
#include "path/path.fw"
#endif

template<class T> class CondCopyControl;



#endif
#endif
