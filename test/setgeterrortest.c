#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

const char specialError[] = "D Error: Special error";
const char specialError2[] = "D Error: Second special error";

int main(){

    printf("The current error: %s\n", D_GetError());

    D_SetError(specialError);
    printf("The current error: %s\n", D_GetError());

    D_SetError(specialError2);
    printf("The current error: %s\n", D_GetError());
};
