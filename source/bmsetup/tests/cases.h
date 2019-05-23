#ifndef TEST_CASES_bmsetup
#define TEST_CASES_bmsetup

#include <stdio.h>
#include <stdarg.h>

#include "bmsetup/bmsetup.h"
#include "generator/generator.h"

#define TEST_PASS 1
#define TEST_FAIL 0
#define TEST_PASS_ALL 2

void run_all_bmsetup(void);

#include "bmsetup/import/modules.h"

#endif
