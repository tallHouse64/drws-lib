#include<stdio.h>
#include"../devents.h"

int printEventQueue(){

    int i = 0;

    printf("back of queue: %d\n", D_EventQueueBack);
    printf("front of queue: %d\n", D_EventQueueFront);

    while(i < D_EVENT_QUEUE_LENGTH){
        printf("%02d ty:%01d|", i, D_EventQueue[i].type);
        i++;
    };

    printf("\n\n");

    return 0;
};

int main(){

    D_Event in = {D_MOUSEDOWN};
    D_Event out = {D_NULL};

    D_StartEvents();

    D_CauseEvent(&in);

    printEventQueue();

    D_GetEvent(&out);

    printEventQueue();

    printf("Got event, it's type is: %d\n\n", out.type);

    printf("Shouldn't be able to get event because queue is empty.\n");
    if(D_GetEvent(&out) == 0){
        printf("Got event (shouldn't happen).\n");
    }else{
        printf("Didn't get event (should happen)\n");
    };

    D_StopEvents();
    return 0;
};
