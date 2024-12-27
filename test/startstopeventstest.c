#include<stdio.h>
#include"../devents.h"

int main(){
    D_StartEvents();

    //It should say
    //D_EventQueue: 0x????? (not 0x000000)
    //D_EventQueueFront: 0
    //D_EventQueueBack: 31 (D_EVENT_QUEUE_LENGTH - 1)
    //D_EventQueueFull: 0
    printf("D_EventQueue: %p\nD_EventQueueFront: %d\nD_EventQueueBack: %d\nD_EventQueueFull: %d\n", D_EventQueue, D_EventQueueFront, D_EventQueueBack, D_EventQueueFull);

    D_StopEvents();
    return 0;
};
