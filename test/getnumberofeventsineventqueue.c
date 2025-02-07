#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#include<stdio.h>

/* This file tests the
 *  D_GetNumberOfEventsInEventQueue() function.
 *
 */

D_Event e;

int main(){
    e.type = D_MOUSEDOWN;

    D_StartEvents();

    printf("Count up\n\n");

    int i = 0;
    while(i < D_EVENT_QUEUE_LENGTH){

        printf("Should have %d events\nHave %d events\n\n", i, D_GetNumberOfEventsInEventQueue());

        D_CauseEvent(&e);
        i++;
    };

    //printf("Should have 32 events\nHave %d events\n\n", D_GetNumberOfEventsInEventQueue());

    printf("Count down\n\n");

    while(i > 0){

        printf("Should have %d events\nHave %d events\n\n", i, D_GetNumberOfEventsInEventQueue());

        D_GetEvent(&e);
        i--;
    };

    printf("Should have %d events\nHave %d events\n\n", i, D_GetNumberOfEventsInEventQueue());
    D_CauseEvent(&e);
    i++;

    printf("Special pattern\n\n");

    while(i < D_EVENT_QUEUE_LENGTH){

        printf("Should have %d events\nHave %d events\nFront: %d back: %d\n\n", i, D_GetNumberOfEventsInEventQueue(), D_EventQueueFront, D_EventQueueBack);
        D_GetEvent(&e);
        i--;

        printf("Should have %d events\nHave %d events\nFront: %d back: %d\n\n", i, D_GetNumberOfEventsInEventQueue(), D_EventQueueFront, D_EventQueueBack);
        D_CauseEvent(&e);
        i++;

        printf("Should have %d events\nHave %d events\nFront: %d back: %d\n\n", i, D_GetNumberOfEventsInEventQueue(), D_EventQueueFront, D_EventQueueBack);
        D_CauseEvent(&e);

        i++;
    };

    D_StopEvents();
}
