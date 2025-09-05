#include<stdio.h>

#define D_IMPLEMENTATION
#include"../d.h"

int dontPrintf(char * format, ...){
    return 0;
};

/* This is is an automatic test.
 */


/* Levels of verbosity change to turn of a level
 *  define it as dontPrintf, to turn it on,
 *  define it as printf.
 *
 * V0 is for printing the details of each subtest
 *  and whether it was successful.
 * V1 is for printing weather each test (and it's
 *  subtests) succeeded.
 * V2 is for printing weather all tests were
 *  successful.
 */
#define TEST_PRINTF_V0 dontPrintf
#define TEST_PRINTF_V1 printf
#define TEST_PRINTF_V2 printf


/*Include the .c files directly. */
#include"chartomaptest.c"
#include"formattorgbatest.c"

int main(int argc, char ** argv){

    int failedTests = 0;

    failedTests += D_CharToMapTest();
    failedTests += D_FormatTorgbaTest();

    TEST_PRINTF_V2("All tests overall ");
    if(failedTests == 0){
        TEST_PRINTF_V2("Success\n\n");
        return 0;
    }else{
        TEST_PRINTF_V2("Failed (%d tests failed)\n\n", failedTests);
        return 1;
    };

    return 0;
};
