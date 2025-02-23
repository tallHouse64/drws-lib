#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#include<stdio.h>

/* This file tests custom events and the
 *  D_RegisterCustomEvent() function.
 */

int main(){

    printf("Test 1, registering custom events using D_RegisterCustomEvent().\n\n");

    const int jumpEvent = D_RegisterCustomEvent();

    const int moveEvent = D_RegisterCustomEvent();

    printf("jumpEvent: %d\nshould be: %d\n\n", jumpEvent, D_FIRSTCUSTOMEVENT);
    printf("moveEvent: %d\nshould be: %d\n\n", moveEvent, D_FIRSTCUSTOMEVENT + 1);


    D_Event e;
    D_StartEvents();

    e.type = D_MOUSEMOVE;
    D_CauseEvent(&e);

    e.type = jumpEvent;
    D_CauseEvent(&e);

    e.type = moveEvent;
    D_CauseEvent(&e);

    printf("Test 2, receiving custom and normal events.\nShould be D_MOUSEMOVE, jumpEvent, moveEvent in that order.\n\n");

    //Tiny loop to drain the event queue
    while(D_GetEvent(&e) != -1){

        if(e.type == jumpEvent){
            printf("jumpEvent received\n");

        }else if(e.type == moveEvent){
            printf("moveEvent received\n");

        };

        switch(e.type){

            case D_MOUSEMOVE:
                printf("D_MOUSEMOVE received\n");
                break;

        };

    };

    printf("\n\nTest 3, register max number of events.\n\n");

    int i = 2; //Already registered 2 custom events
    int lastReg = -1;
    int reg = -1;
    while(reg != 0){
        lastReg = reg;
        reg = D_RegisterCustomEvent();

        if(reg != D_NOEVENT){
            i++;
        };
    };

    printf("Last event number before running out of events: %d\nShould be:                                      %d\n\n", lastReg, D_LASTEVENT);

    printf("Registered %d events.\nShould be  %d which is (D_LASTEVENT - D_FIRSTCUSTOMEVENT) + 1.\n", i, ((D_LASTEVENT - D_FIRSTCUSTOMEVENT) + 1));

    D_StopEvents();
};
