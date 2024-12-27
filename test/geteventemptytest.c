#include<stdio.h>
#include"../devents.h"

int main(){
    D_Event out = {D_NULL};
    D_StartEvents();

    printf("D_GetEvent return (should be -1): %d\n", D_GetEvent(&out));

    D_StopEvents();
};
