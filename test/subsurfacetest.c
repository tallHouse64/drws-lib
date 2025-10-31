#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

/* This file tests wather it is possible to
 *  create a subsurface from a surface using the
 *  D_CreateSurfaceFrom() function.
 *
 * If it is working, you should see a window
 *  appear filled with green except for a 1 pixel
 *  thick black boarder.
 *
 * The subsurface "inner" covers the entire
 *  window surface except for the one pixel
 *  boarder, "inner" gets filled completely with
 *  green.
 */

int main(int argc, char ** argv){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "subsurface test", 0);


    /* Where the inner rect should go */
    /*D_Rect where = {430, 50, 200, 100};*/
    D_Rect where = {1, 1, 638, 478};

    D_Surf * inner = D_CreateSurfFrom(where.w,
                                      where.h,
                                      (out->w - where.w) * (D_BITDEPTHTOBYTES(out->format.bitDepth)),
                                      out->format,
                                      (((D_uint8 *)out->pix) + (((where.y * out->w) + where.x) * (D_BITDEPTHTOBYTES(out->format.bitDepth))) + out->pitch));

    D_FillRect(inner, D_NULL, D_rgbaToFormat(inner->format, 0, 255, 0, 255));
    D_FlipOutSurf(out);

    D_Delay(3000);

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
