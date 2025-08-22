#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"

#define DELAY 1000/15

/* This file tests general keyboard and mouse
 *  input events fired by D_PumpEvents().
 */

int main(int argc, char ** argv){
    D_StartEvents();

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Keyboard Event Test", 0);
    D_Rect r = {0, 0, 40, 40};
    D_Event e;
    int running = 1;

    while(running){

        printf("\nNew frame\n");
        D_PumpEvents();

        while(D_GetEvent(&e) != -1){

            printf("Event type: %d\n", e.type);
            switch(e.type){
                case D_MOUSEMOVE:
                    printf("mouse move button %d\n", e.mouse.button);
                    r.x = e.mouse.x;
                    r.y = e.mouse.y;
                    break;
                case D_MOUSEDOWN:
                    printf("mouse down button: %d\n", e.mouse.button);
                    break;
                case D_MOUSEUP:
                    printf("mouse up button: %d\n", e.mouse.button);
                    break;
                case D_KEYDOWN:
                    printf("keydown: %c\n", D_DKeyToChar(e.keyboard.key));
                    break;
                case D_KEYUP:
                    printf("keyup: %c\n", D_DKeyToChar(e.keyboard.key));
                    break;
                case D_QUIT:
                    running = 0;
                    break;
            };
        };

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 150, 255, 250, 255));

        D_FillRect(out, &r, D_rgbaToFormat(out->format, 255, 255, 255, 255));

        D_FlipOutSurf(out);
        D_Delay(DELAY);
    };


    D_FreeOutSurf(out);

    D_StopEvents();
};
