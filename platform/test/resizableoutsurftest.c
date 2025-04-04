#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"

#include<stdio.h>

/* This file tests window resizing. Including the
 *  D_OUTSURFRESIZE event and the
 *  D_GetResizedOutSurf() function.
 *
 * The test runs on two windows.
 */

int main(){
    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Resizable outSurf test", D_OUTSURFRESIZABLE);
    D_Surf * out2 = D_GetOutSurf(70, 70, 640, 480, "Resizable outSurf test", D_OUTSURFRESIZABLE);
    D_Event e;
    int running = 1;
    D_Rect rect = {20, 20, 600, 440};

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) == 0){
            switch(e.type){

                case D_QUIT:
                    running = 0;
                    break;

                case D_MOUSEDOWN:
                    printf("Mousedown event\n");
                    break;

                case D_OUTSURFRESIZE:
                    printf("Resize event\nw: %d\nh: %d\noutId: %d\n\n",
                           e.outSurf.data1,
                           e.outSurf.data2,
                           e.outSurf.outId);

                    if(e.outSurf.outId == out->outId){
                        out = D_GetResizedOutSurf(out);

                    }else if(e.outSurf.outId == out2->outId){
                        out2 = D_GetResizedOutSurf(out2);

                    };

                    break;

            };
        };

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 200, 200, 255, 255));
        D_FillRect(out, &rect, D_rgbaToFormat(out->format, 255, 150, 200, 255));
        D_FlipOutSurf(out);

        D_FillRect(out2, D_NULL, D_rgbaToFormat(out2->format, 200, 255, 200, 255));
        D_FillRect(out2, &rect, D_rgbaToFormat(out2->format, 255, 200, 255, 255));
        D_FlipOutSurf(out2);

        D_Delay(100);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;
    D_FreeOutSurf(out2);
    out2 = D_NULL;
};
