#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

/* This file tests the D_CreateSubsurf()
 *  function.
 *
 * If it is working, you should see a window
 *  appear filled with green except for a 1 pixel
 *  thick black boarder. This is the "inner"
 *  surface getting filled with green, that
 *  surface covering the entire outer surface
 *  except for 1 pixel on each side.
 *
 * This test also draws rectangles at each edge
 *  of the window to make sure they only draw
 *  within the surface.
 *
 * Another thing this test does is draw grey
 *  rectangles on "inner" (the green subsurface),
 *  at each side. This is to test that
 *  D_FillRect() doesn't draw outside that
 *  surface.
 */

int main(int argc, char ** argv){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Testing D_CreateSubsurface()", 0);


    /* Make a surface and draw the green rect */
    D_Rect where = {1, 1, 638, 478};
    D_Surf * inner = D_CreateSubsurf(out, &where);

    /* Fill the safe area */
    D_FillRect(inner, &inner->safeArea, D_rgbaToFormat(inner->format, 0, 255, 0, 255));


    /* Draw 4 rectangles at each edge of "out" */

    /* Make a surface and draw the red rect (on
     *  the left). */
    D_Rect where2 = {-20, 50, 40, 40};
    D_Surf * inner2 = D_CreateSubsurf(out, &where2);

    /* Fill the safe area */
    D_FillRect(inner2, D_NULL, D_rgbaToFormat(inner2->format, 255, 0, 0, 255));


    /* Make a surface and draw the blue rect (on
     *  the right). */
    D_Rect where3 = {620, 120, 40, 40};
    D_Surf * inner3 = D_CreateSubsurf(out, &where3);

    /* Fill the safe area */
    D_FillRect(inner3, D_NULL, D_rgbaToFormat(inner3->format, 0, 0, 255, 255));


    /* Make a surface and draw the purple rect
     *  (on the top). */
    D_Rect where4 = {70, -20, 40, 40};
    D_Surf * inner4 = D_CreateSubsurf(out, &where4);

    /* Fill the safe area */
    D_FillRect(inner4, D_NULL, D_rgbaToFormat(inner4->format, 255, 0, 255, 255));


    /* Make a surface and draw the purple rect
     *  (on the bottom). */
    D_Rect where5 = {200, 460, 40, 40};
    D_Surf * inner5 = D_CreateSubsurf(out, &where5);

    /* Fill the safe area */
    D_FillRect(inner5, D_NULL, D_rgbaToFormat(inner5->format, 255, 255, 0, 255));



    /* Draw 4 rectangles at each edge of "inner"
     */

    /* Make a surface and draw a grey rect (on
     *  the left). */
    D_Rect where6 = {-20, 170, 40, 40};
    D_Surf * inner6 = D_CreateSubsurf(inner, &where6);

    /* Fill the safe area */
    D_FillRect(inner6, D_NULL, D_rgbaToFormat(inner6->format, 128, 128, 128, 255));


    /* Make a surface and draw a grey rect (on
     *  the right). */
    D_Rect where7 = {620, 220, 40, 40};
    D_Surf * inner7 = D_CreateSubsurf(inner, &where7);

    /* Fill the safe area */
    D_FillRect(inner7, D_NULL, D_rgbaToFormat(inner7->format, 128, 128, 128, 255));


    /* Make a surface and draw a grey rect (on
     *  the top). */
    D_Rect where8 = {250, -20, 40, 40};
    D_Surf * inner8 = D_CreateSubsurf(inner, &where8);

    /* Fill the safe area */
    D_FillRect(inner8, D_NULL, D_rgbaToFormat(inner8->format, 128, 128, 128, 255));


    /* Make a surface and draw a grey rect (on
     *  the bottom). */
    D_Rect where9 = {350, 460, 40, 40};
    D_Surf * inner9 = D_CreateSubsurf(inner, &where9);

    /* Fill the safe area */
    D_FillRect(inner9, D_NULL, D_rgbaToFormat(inner9->format, 128, 128, 128, 255));



    D_FlipOutSurf(out);
    D_Delay(3000);


    D_FreeSurf(inner);
    inner = D_NULL;

    D_FreeOutSurf(out);
    out = D_NULL;
    return 0;
};
