#include"platform/ndsd.h"

#define DEVENTS_IMPLEMENTATION
#include"devents.h"

#define D_IMPLEMENTATION
#include"d.h"

#include"dplatform.h"

/* This file tests the D_Delay() function in
 *  ndsd.h.
 *
 * This test flashes white and black on the
 *  screen in a loop, it changes once every
 *  second.
 */

int main(){
    D_Surf * out = D_GetOutSurf(0, 0, 640, 480, "D_Delay() test, flash once per second", 0);

    while(1){
        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 255, 255, 255, 255));
        D_FlipOutSurf(out);
        D_Delay(1000);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_FlipOutSurf(out);
        D_Delay(1000);
    };

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
