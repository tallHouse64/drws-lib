#define D_CUSTOMEVENT_SIZE 128

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

/* This file tests custom events with structures
 *  bigger than 32 bytes, meaning that
 *  D_CUSTOMEVENT_SIZE is redefined.
 */

struct bigEventData_t {
    D_uint32 a, b, c, d, e, f, g, h, i;
};

int main(){

    D_StartEvents();
    D_Event e;

    const int bigEvent = D_RegisterCustomEvent();

    e.type = D_MOUSEDOWN;
    e.mouse.x = 42;
    e.mouse.y = 78;
    D_CauseEvent(&e);

    e.type = bigEvent;
    struct bigEventData_t bigEventData = {472, 8118, 123, 987, 222, 5555, 547375, 3323, 1073741823};
    e.custom = (* ((D_CustomEvent *) &bigEventData));
    D_CauseEvent(&e);

    printf("Big custom event test (bigger than 32 bytes).\n");
    printf("Should receive\n");
    printf("D_MOUSEDOWN x: %d y: %d\n", 42, 78);
    printf("bigEvent a: 472 b: 8118 c: 123 d: 987 e: 222 f: 5555 g: 547375 h: 3323 i: 1073741823\n\n");

    printf("Receiving events\n");

    while(D_GetEvent(&e) != -1){

        if(e.type == bigEvent){

            struct bigEventData_t * data = (struct bigEventData_t *) &e.custom;
            printf("bigEvent received a: %d b: %d c: %d d: %d e: %d f: %d g: %d h: %d i: %d\n", data->a, data->b, data->c, data->d, data->e, data->f, data->g, data->h, data->i);

        }else if(e.type == D_MOUSEDOWN){
            printf("D_MOUSEDOWN recived x: %d y: %d\n", e.mouse.x, e.mouse.y);
        };

    };

    D_StopEvents();

};
