#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"

#include<stdio.h>

int main(){
    printf("Should be  %d\nreturns %d\n\n", D_Ka, D_SDLKToDKey(SDLK_a));
    printf("Should be  %d\nreturns %d\n\n", D_Kb, D_SDLKToDKey(SDLK_b));
    printf("Should be  %d\nreturns %d\n\n", D_Kz, D_SDLKToDKey(SDLK_z));

    printf("Should be  %d\nreturns %d\n\n", D_KHome, D_SDLKToDKey(SDLK_HOME));
};
