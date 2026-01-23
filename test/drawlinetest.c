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
 *
 * You can also press "q" to quit the program
 *  now.
 *
 * This test also uses a subsurf to make it
 *  visible when the function draws outside a
 *  surface (which would mean the function is
 *  unsafe and may write to memory it shouldn't).
 *  While running the test, the line should never
 *  cover the red boarder around the window.
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

    D_Surf * realOut = D_GetOutSurf(50, 50, 640, 480, "Testing D_DrawLine()", 0);
    D_Rect rect = {1, 1, 638, 478};
    D_Surf * out = D_CreateSubsurf(realOut, &rect);

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

                case D_KEYDOWN:
                    if(e.keyboard.key == D_Kq){
                        running = 0;
                    };
                    break;

                case D_QUIT:
                    running = 0;
                    break;

            };
        };

        /* Clear the real window to red */
        D_FillRect(realOut, D_NULL, D_rgbaToFormat(out->format, 255, 0, 0, 255));

        /* Clear the window to black */
        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

        /* Draw point A as a red box */
        drawPoint(out, &a, D_rgbaToFormat(out->format, 255, 0, 0, 255));

        /* Draw point B as a blue box */
        drawPoint(out, &b, D_rgbaToFormat(out->format, 0, 0, 255, 255));

        /* Draw the line as white */
        D_DrawLine(out, &a, &b, 10, D_rgbaToFormat(out->format, 255, 255, 255, 255));

        /* Show the frame onscreen */
        D_FlipOutSurf(realOut);


        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeSurf(out);
    out = D_NULL;

    D_FreeOutSurf(realOut);
    realOut = D_NULL;

    return 0;
};
