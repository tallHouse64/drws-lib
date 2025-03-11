#define D_ALLOW_STB_IMAGE
#define D_IMPLEMENTATION
#include"../d.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../stb_image.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

/* This file tests using the alpha modulation on
 *  a surface. It runs D_SetSurfAlphaMod() on a
 *  surface and D_SurfCopyScale() to make sure it
 *  is partly/fully/not transparent depending on
 *  the alpha modulation.
 *
 * If the test is working, you should see
 *  blendTestFront.png fade away in front of
 *  blendTestBack.png.
 *
 * On my laptop, this test took 1min and 33 sec.
 */

#define DELAY 5

int main(){

    D_Surf * back = D_LoadImage("img/blendTestBack.png");
    D_Surf * front = D_LoadImage("img/blendTestFront.png");

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Testing surface alpha modulation", 0);
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

    D_Rect r = {128, 132, 384, 216};
    D_SurfCopyScale(back, D_NULL, out, &r);
    D_SurfCopyScale(front, D_NULL, out, &r);

    D_FlipOutSurf(out);

    D_Delay(1000);

    printf("Testing normal blending.\n");
    int i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    printf("Testing addition blending.\n");
    front->blendMode = D_BLENDMODE_ADD;
    i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    printf("Testing multiplication blending.\n");
    front->blendMode = D_BLENDMODE_MULTIPLY;
    i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    printf("Testing subtraction blending.\n");
    front->blendMode = D_BLENDMODE_SUBTRACT;
    i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    printf("Testing division blending.\n");
    front->blendMode = D_BLENDMODE_DIVIDE;
    i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    printf("Testing no blending (it should not fade this time).\n");
    front->blendMode = D_BLENDMODE_NONE;
    i = 255;
    while(i >= 0){
        D_SetSurfAlphaMod(front, i);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_SurfCopyScale(back, D_NULL, out, &r);
        D_SurfCopyScale(front, D_NULL, out, &r);

        D_FlipOutSurf(out);

        D_Delay(DELAY);

        i--;
    };

    D_Delay(1000);
};
