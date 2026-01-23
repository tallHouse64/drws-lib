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
 * The line drawn should be rgb: 121, 216, 194.
 *  The leftmost line should be that colour
 *  exactly, the middle only has to be
 *  approximately that colour and the line on the
 *  right should be a grayscale version of the
 *  colour.
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

/* This function just draws a line with a red and
 *  blue box at each end. */
int test(D_Surf * s, D_Point * a, D_Point * b, D_uint32 col){

    /* Draw point A as a red box */
    drawPoint(s, a, D_rgbaToFormat(s->format, 255, 0, 0, 255));

    /* Draw point B as a blue box */
    drawPoint(s, b, D_rgbaToFormat(s->format, 0, 0, 255, 255));

    /* Draw the line as white */
    D_DrawLine(s, a, b, 10, col);

    return 0;
};

int main(int argc, char ** argv){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Testing D_DrawLine()", 0);

    D_Surf * target32 = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    D_Rect target32Rect = {0, 0, out->w / 3, out->h};

    D_Surf * target16 = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));
    D_Rect target16Rect = {out->w / 3, 0, out->w / 3, out->h};

    D_Surf * target8  = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0x00, 8));
    D_Rect target8Rect = {(out->w / 3) * 2, 0, out->w / 3, out->h};

    D_Event e = {0};
    D_Point a = {40, 140};
    D_Point b = {200, 170};
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

        /* Clean the target surfaces to black */
        D_FillRect(target32, D_NULL, D_rgbaToFormat(target32->format, 255, 255, 255, 255));
        D_FillRect(target16, D_NULL, D_rgbaToFormat(target16->format, 255, 255, 255, 255));
        D_FillRect(target8,  D_NULL, D_rgbaToFormat(target8->format,  255, 255, 255, 255));

        /* Draw a line on a surface (with a bit
         *  depth of 32) */
        test(target32, &a, &b, D_rgbaToFormat(target32->format, 121, 216, 194, 255));
        D_SurfCopyScale(target32, D_NULL, out, &target32Rect);

        /* Draw a line on a surface (with a bit
         *  depth of 16) */
        test(target16, &a, &b, D_rgbaToFormat(target16->format, 121, 216, 194, 255));
        D_SurfCopyScale(target16, D_NULL, out, &target16Rect);

        /* Draw a line on a surface (with a bit
         *  depth of 8) */
        test(target8, &a, &b, D_rgbaToFormat(target8->format, 121, 216, 194, 255));
        D_SurfCopyScale(target8, D_NULL, out, &target8Rect);

        /* Show the frame onscreen */
        D_FlipOutSurf(out);


        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
