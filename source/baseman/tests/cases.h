#ifndef TEST_CASES_baseman
#define TEST_CASES_baseman

#include <stdio.h>
#include <stdarg.h>

#include "baseman/baseman.h"
#include "generator/generator.h"

#define TEST_PASS 1
#define TEST_FAIL 0
#define TEST_PASS_ALL 2

void run_all_baseman(void);

#include "baseman/import/modules.h"

#endif
