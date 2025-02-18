#define D_IMPLEMENTATION
#include"d.h"

#define DEVENTS_IMPLEMENTATION
#include"devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"platform/sdld.h"

/* This file is an example of how to use the
 *  drws-lib in a single file. It is very short
 *  to make it simple and easy to learn. Drws-lib
 *  has more features that are not used in this
 *  file.
 *
 * You can read d.h, which has it's own
 *  documentation inside it. You can also read
 *  the documentation in devents.h and
 *  platform/sdld.h.
 *
 * All this example does is create an "outSurf",
 *  which is a window. Then draws a green
 *  rectangle and shows the surface.
 */

D_Surf * out = D_NULL;

int main(){

    //Create the outSurf, (window).
    out = D_GetOutSurf(50, 50, 640, 480, "Example of drws-lib", 0);

    //Draw a green rectangle
    D_Rect r = {20, 20, 600, 440};
    D_FillRect(out, &r, D_rgbaToFormat(out->format, 100, 200, 100, 255));

    //Show the surface on screen
    D_FlipOutSurf(out);

    //Wait 3 seconds
    D_Delay(3000);

    //Free the outSurf, (the window is destroyed)
    D_FreeOutSurf(out);
    out = D_NULL;
};
