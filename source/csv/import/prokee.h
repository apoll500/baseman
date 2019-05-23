#ifndef csv_import_prokee
#define csv_import_prokee

#define PROKEE_USE_INTERFACE
#define PROKEE_USE_WRAPPER



class Reader;

class CsvData;
class CsvRecord;
class CsvField;
class CsvSettings;

#ifdef COMPILE_PROKEE_MODULE

#include "../../interface/prokee/csv/inc/interface/import/all.fw"
#include "../../interface/prokee/csv/inc/wrapper/import/all.fw"

#include "file/v01/module.h"
#include "reader/v01/module.h"
#include "strconv/v01/module.h"


#ifdef COMPILE_MODULE_csv

//Local classes


//Interface declarations of this module
#include "csv/csv.hh"

#endif

#else

//Local classes


//Interface declarations of this module
#include "csv/csv.hh"

//Interface declarations of other required modules
#include "file/file.hh"
#include "reader/reader.hh"
#include "strconv/strconv.hh"


#endif
#endif
