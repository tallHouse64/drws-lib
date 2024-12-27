#include<stdio.h>
#include"../devents.h"

int main(){
    D_Event in = {D_MOUSEDOWN};
    D_Event out = {D_NULL};
    D_StartEvents();

    //Should return 0 everytime except for the last time when it returns -1
    int i = 0;
    while(i < D_EVENT_QUEUE_LENGTH+1){
        printf("D_CauseEvent return: %d\n", D_CauseEvent(&in));
        i++;
    };

    printf("\nGet event: %d\n", D_GetEvent(&out));
    printf("Cause event (should work and be 0): %d\n", D_CauseEvent(&in));
    printf("Cause event (should not work and be -1): %d\n", D_CauseEvent(&in));

    D_StopEvents();
};
