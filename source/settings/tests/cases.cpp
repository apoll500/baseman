//../../../../source/settings/tests/cases.cpp

#include "cases.h"


//----------------------------------------------------------------------
// Run all tests
//----------------------------------------------------------------------
void run_all_settings(void)
{
    int test_counter=0;
    int test_status=0;
    
    FILE *f=fopen("test_results.def","wb");
    if(!f)
    {
        printf("Cannot open output file.\n");
        return;
    }
    
    
    
    
    fclose(f);
}
