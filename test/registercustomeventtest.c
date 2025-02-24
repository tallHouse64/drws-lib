#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#include<stdio.h>

/* This file tests custom events and the
 *  D_RegisterCustomEvent() function.
 */

struct jumpEventData_t {
    int height; //These members are just examples
    int timeStamp;
};

struct moveEventData_t {
    int playerX;
    int playerY;
};

int main(){

    printf("Test 1, registering custom events using D_RegisterCustomEvent().\n\n");

    const int jumpEvent = D_RegisterCustomEvent();

    const int moveEvent = D_RegisterCustomEvent();

    printf("jumpEvent: %d\nshould be: %d\n\n", jumpEvent, D_FIRSTCUSTOMEVENT);
    printf("moveEvent: %d\nshould be: %d\n\n", moveEvent, D_FIRSTCUSTOMEVENT + 1);


    D_Event e;
    D_StartEvents();

    e.type = D_MOUSEMOVE;
    e.mouse.x = 10;
    e.mouse.y = 12;
    D_CauseEvent(&e);

    e.type = jumpEvent;
    struct jumpEventData_t jumpData = {24, 1012};
    e.custom = *((D_CustomEvent *)&jumpData); //This is type punning
    D_CauseEvent(&e);

    e.type = moveEvent;
    struct moveEventData_t moveData = {54, 39};
    e.custom = *((D_CustomEvent *)&moveData);
    D_CauseEvent(&e);

    printf("Test 2, receiving custom and normal events.\nShould be\n");
    printf("D_MOUSEMOVE x: %d y: %d, \n", 10, 12);
    printf("jumpEvent height: %d timeStamp: %d, \n", jumpData.height, jumpData.timeStamp);
    printf("moveEvent playerX: %d playerY: %d\nin that order.\n\n", moveData.playerX, moveData.playerY);

    //Tiny loop to drain the event queue
    while(D_GetEvent(&e) != -1){

        if(e.type == jumpEvent){
            printf("jumpEvent received height: %d timeStamp: %d\n",
                   (* ((struct jumpEventData_t *) &e.custom)).height,
                   (* ((struct jumpEventData_t *) &e.custom)).timeStamp);

        }else if(e.type == moveEvent){
            printf("moveEvent received playerX: %d playerY: %d\n", (* ((struct moveEventData_t *) &e.custom)).playerX, (* ((struct moveEventData_t *) &e.custom)).playerY);

        };

        switch(e.type){

            case D_MOUSEMOVE:
                printf("D_MOUSEMOVE received x: %d y: %d\n", e.mouse.x, e.mouse.y);
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
