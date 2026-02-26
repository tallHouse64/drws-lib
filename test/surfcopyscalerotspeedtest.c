#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#include<SDL2/SDL.h>
#include<stdio.h>

/* This test finds the time that
 *  D_SurfCopyScaleRot() takes to run at
 *  different rotations.
 *
 * This test uses the standard library to print
 *  the results and SDL2 to time the function.
 */

int speedTest(D_Surf * img, D_Surf * out, D_Rect * rect, D_Point * centre, D_double deg){

    int static testNumber = 0;

    Uint64 startTime = 0;
    Uint64 endTime = 0;

    startTime = SDL_GetTicks64();
    D_SurfCopyScaleRot(img, D_NULL, out, rect, centre, deg, 0, 0);
    endTime = SDL_GetTicks64();

    printf("TestNo: %d deg: %f time: %dms\n", testNumber, deg, endTime - startTime);

    testNumber++;

    return 0;
};

int main(){

    SDL_Init(SDL_INIT_EVERYTHING);

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "D_SurfCopyScaleRot() speed test", 0);
    D_Surf * img = D_LoadImage("img/folder.png");
    D_Rect rect = {25, 50, 192, 108};
    D_Point centre = {96, 54};


    speedTest(img, out, &rect, &centre, 0);

    rect.x += rect.w + 20;
    speedTest(img, out, &rect, &centre, 30);

    rect.x += rect.w + 20;
    speedTest(img, out, &rect, &centre, 30.75);

    rect.y += rect.h + 20;
    rect.x = 25;
    speedTest(img, out, &rect, &centre, 90);

    rect.x += rect.w + 20;
    speedTest(img, out, &rect, &centre, 225);

    rect.x += rect.w + 20;
    speedTest(img, out, &rect, &centre, 359);


    D_FlipOutSurf(out);

    D_Delay(3000);

    D_FreeSurf(img);
    img = D_NULL;

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
