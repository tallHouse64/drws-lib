#define D_IMPLEMENTATION
#include"../../d.h"
#include"../../dplatform.h"
#include"../webd.h"

#define DELAY 1000/60

D_Surf * out = D_NULL;

/* **WARNING**: Flashing lights warning if you
 *  run this test.
 *
 * This file tests the D_GetOutSurf() and
 *  D_FlipOutSurf() functions.
 */

int main(){
    out = D_GetOutSurf(0, 0, 640, 480, "Test", 0);
    D_Surf * testImage = D_CreateSurf(out->w, out->h, out->format);
    D_Rect flashingRect = {10, 10, 30, 30};
    int state = 0;

    /*Draw test image*/
    D_Rect colorBox = {0, 0, testImage->w / 3, testImage->h};
    D_FillRect(testImage, &colorBox, D_rgbaToFormat(out->format, 255, 0, 0, 255));
    colorBox.x += colorBox.w;
    D_FillRect(testImage, &colorBox, D_rgbaToFormat(out->format, 0, 255, 0, 255));
    colorBox.x += colorBox.w;
    D_FillRect(testImage, &colorBox, D_rgbaToFormat(out->format, 0, 0, 255, 255));

    EM_ASM({
        console.log("Running");
        console.log("out " + $0 + " pix " + $1);
    }, out, out->pix);

    while(1){
        EM_ASM({console.log("While loop!")});

        /*D_SurfCopyScale(testImage, D_NULL, out, D_NULL);*/

        colorBox.x = 0;
        D_FillRect(out, &colorBox, D_rgbaToFormat(out->format, 255, 0, 0, 255));
        colorBox.x += colorBox.w;
        D_FillRect(out, &colorBox, D_rgbaToFormat(out->format, 0, 255, 0, 255));
        colorBox.x += colorBox.w;
        D_FillRect(out, &colorBox, D_rgbaToFormat(out->format, 0, 0, 255, 255));

        if(state){
            D_FillRect(out, &flashingRect, D_rgbaToFormat(out->format, 0, 0, 255, 255));
        }else{
            D_FillRect(out, &flashingRect, D_rgbaToFormat(out->format, 255, 0, 0, 255));
        };

        EM_ASM({
            window.timeBeforeFlipOutSurf = Date.now();
        });

        D_FlipOutSurf(out);

        EM_ASM({
            console.log("D_FlipSurf() took " + (Date.now() - timeBeforeFlipOutSurf) + "ms");
        });

        state = !state;

        emscripten_sleep(DELAY);
    };



    D_FreeOutSurf(out);
    out = D_NULL;
    return 0;
};
