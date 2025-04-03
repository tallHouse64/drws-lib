#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"

#include<stdio.h>

/* This file tests the D_WindowToOutId() function
 *  in sdld.h.
 *
 * It tests multiple outSurfs/windows. It also
 *  destroys and recreates one to make sure it
 *  works even after recreating a window.
 */

D_Surf * out1 = D_NULL;
D_Surf * out2 = D_NULL;
D_Surf * out3 = D_NULL;

int overallSuccess = 1; //Set to 0 (fail) if at least one test fails

/* This function tests the D_WindowToOutId()
 *  function with any outSurf.
 *
 * s: The outSurf to test with.
 */
void test(D_Surf * s){

    int result = -1;
    int id = -1;

    printf("out%d\nResult: %d\nShould be: %d\n", s->outId, (result = D_WindowToOutId(sdlw[s->outId])), s->outId);
    if(result == s->outId){
        printf("Success\n\n");
    }else{
        printf("Fail\n\n");
        overallSuccess = 0;
    };

    return;
};

int main(){
    out1 = D_GetOutSurf(50, 50, 640, 480, "Test window 1", 0);
    out2 = D_GetOutSurf(50, 50, 640, 480, "Test window 2", 0);
    out3 = D_GetOutSurf(50, 50, 640, 480, "Test window 3", 0);

    printf("Testing D_WindowToOutId().\n\n");

    test(out1);
    test(out2);
    test(out3);

    printf("Freeing out2\n\n");
    D_FreeOutSurf(out2);
    out2 = D_NULL;

    printf("Checking the ids again\n\n");

    test(out1);
    //test(out2);
    test(out3);

    printf("Remaking out2\n\n");

    out2 = D_GetOutSurf(50, 50, 640, 480, "Test window 2 again", 0);

    printf("Checking the ids again\n\n");

    test(out1);
    test(out2);
    test(out3);

    printf("Final result\n");
    if(overallSuccess){
        printf("Success\n\n");
    }else{
        printf("Fail\n\n");
    };
};
