#ifndef TEST_CASES_csv
#define TEST_CASES_csv

#include <stdio.h>
#include <stdarg.h>

#include "csv/csv.h"
#include "generator/generator.h"

#define TEST_PASS 1
#define TEST_FAIL 0
#define TEST_PASS_ALL 2

void run_all_csv(void);

#include "csv/import/modules.h"

#endif
