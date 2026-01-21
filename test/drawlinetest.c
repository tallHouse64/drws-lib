#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#define DELAY 1000/30

/* This file tests the D_DrawLine() function.
 *
 * Hold left click and drag to move point A
 *  (red), hold right click and drag to move
 *  point B (blue).
 */

/* This function draws a point as a small
 *  rectangle. No safety because this is just
 *  test code.
 */
int drawPoint(D_Surf * s, D_Point * p, D_uint32 col){
    D_Rect r = {p->x - 4, p->y - 4, 8, 8};

    D_FillRect(s, &r, col);
    return 0;
};

int main(int argc, char ** argv){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Testing D_DrawLine()", 0);
    D_Event e = {0};
    D_Point a = {100, 100};
    D_Point b = {300, 170};
    int running = 1;

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) != -1){
            switch(e.type){

                case D_MOUSEMOVE:

                    if(e.mouse.button == D_LEFTBUTTON){
                        a.x = e.mouse.x;
                        a.y = e.mouse.y;
                    }else if(e.mouse.button == D_RIGHTBUTTON){
                        b.x = e.mouse.x;
                        b.y = e.mouse.y;
                    };

                    break;

                case D_QUIT:
                    running = 0;
                    break;

            };
        };


        /* Clear the window to black */
        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

        /* Draw point A as a red box */
        drawPoint(out, &a, D_rgbaToFormat(out->format, 255, 0, 0, 255));

        /* Draw point B as a blue box */
        drawPoint(out, &b, D_rgbaToFormat(out->format, 0, 0, 255, 255));

        /* Draw the line as white */
        D_DrawLine(out, &a, &b, 1, D_rgbaToFormat(out->format, 255, 255, 255, 255));

        /* Show the frame onscreen */
        D_FlipOutSurf(out);


        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
