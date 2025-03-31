#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"

#include<stdio.h>

/* This file tests if the outSurfs[] array in
 *  sdld.h maps outsurfs to their outIds
 *  correctly. It also tests if an out surf that
 *  is freed and recreated has the same outId it
 *  did before.
 */

D_Surf * out1 = D_NULL;
D_Surf * out2 = D_NULL;
D_Surf * out3 = D_NULL;

void printIds(){

    if(out1 != D_NULL){
        printf("out1 outId: %d\n", out1->outId);
    }else{
        printf("out1 is null\n");
    };

    if(out2 != D_NULL){
        printf("out2 outId: %d\n", out2->outId);
    }else{
        printf("out2 is null\n");
    };

    if(out3 != D_NULL){
        printf("out3 outId: %d\n", out3->outId);
    }else{
        printf("out3 is null\n");
    };
};

int main(){

    printf("Testing outSurfs[] array.\n\n");

    printIds();

    printf("\nCreating out surfs\n\n");
    out1 = D_GetOutSurf(50, 50, 640, 480, "outSurfs[] array test win 1", 0);
    out2 = D_GetOutSurf(50, 50, 640, 480, "outSurfs[] array test win 2", 0);
    out3 = D_GetOutSurf(50, 50, 640, 480, "outSurfs[] array test win 3", 0);
    printIds();

    int outSurf2OldId = out2->outId;

    printf("\nFreeing outSurf 2\n\n");
    D_FreeOutSurf(out2);
    out2 = D_NULL;
    printIds();

    printf("\nCreating outSurf 2 again\n\n");
    out2 = D_GetOutSurf(50, 50, 640, 480, "outSurfs[] array test win 2 recreated", 0);
    printIds();

    printf("\nTest 1, does the recreated outSurf 2 have the same id it used to have?\n");
    if(out2->outId == outSurf2OldId){
        printf("Yes, (success)\n");
    }else{
        printf("No, (fail)\n");
    };

    printf("\nTest 2, does the outSurfs[] array correctly map surface outIds to D_Surf addresses?\n");
    if(outSurfs[out1->outId] == out1 && outSurfs[out2->outId] == out2 && outSurfs[out3->outId] == out3){
        printf("Yes, (success)\n");
    }else{
        printf("No, (fail)\n");
    };


    D_FreeOutSurf(out1);
    out1 = D_NULL;
    D_FreeOutSurf(out2);
    out2 = D_NULL;
    D_FreeOutSurf(out3);
    out3 = D_NULL;

};
