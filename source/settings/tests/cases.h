#ifndef TEST_CASES_settings
#define TEST_CASES_settings

#include <stdio.h>
#include <stdarg.h>

#include "settings/settings.h"
#include "generator/generator.h"

#define TEST_PASS 1
#define TEST_FAIL 0
#define TEST_PASS_ALL 2

void run_all_settings(void);

#include "settings/import/modules.h"

#endif
