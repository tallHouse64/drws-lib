#include<stdio.h>

#include"../../devents.h"
#include"../../devents.h"
#include"../../devents.h"
#include"../../devents.h"
#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"
#include"../../devents.h"
#include"../../devents.h"
#include"../../devents.h"
#include"../../devents.h"

#include"outsidefile.h"

int main(){

    D_Event e;

    D_StartEvents();

    func();

    D_GetEvent(&e);
    printf("Event type: %d\nShould be %d\n", e.type, D_MOUSEDOWN);


    D_StopEvents();

    printf("Works.\n");
};
