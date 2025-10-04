#include<emscripten.h>
#include"../d.h"
#include"../devents.h"
#include"../dplatform.h"

/* Front and back buffers to draw to. Limit the
 *  global state as much as possible, this global
 *  state is necessary because a D_Surf doesn't
 *  have a pointer to front buffer pixel data, it
 *  only has a pointer to back buffer pixel data
 *  (which is surf->pix).
 *
 * Note that there is some global state in JS
 *  with D_Canvas, etc. Search "window." with ctrl
 *  + f to find it.
 */
D_uint32 * D_D_Buffer1;
D_uint32 * D_D_Buffer2;

/* This finds the element with the id
 *  "drws-lib-canvas" and returns an outsurf that
 *  can be used to draw to it.
 *
 * If this function returns null, check the
 *  browser console log and make sure there is a
 *  <canvas> element on the page with an id of
 *  "drws-lib-canvas".
 *
 * It is unlikely but this function may also
 *  return null if (from within
 *  D_CreateSurfFrom()) D_CALLOC() fails and
 *  returns null, causing D_CreateSurfFrom() to
 *  return null, causing this function to return
 *  null.
 *
 * This function draws to buffers inside wasm
 *  memory, this means a buffer needs to be
 *  copied when calling D_FlipSurf(). This may
 *  need optimising in the future.
 *
 * x: This number gets ignored.
 * y: This number gets ignored.
 * w: The width to set the html canvas element to.
 * h: The height to set the html canvas element to.
 * title: This gets ignored.
 * flags: This gets ignored.
 * returns: A pointer to a surface or null on failure.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){

    int foundUnusedCanvas = EM_ASM_INT({

        if(typeof D_Canvas !== 'undefined'){
            console.log("Drws-lib: Warning, D_GetOutSurf() called more than once without calling D_FreeOutSurf().");

            return 0;
        };

        window.D_Canvas = document.getElementById("drws-lib-canvas");

        if(!D_Canvas){
            console.log("Drws-lib: Warning, canvas element not found, make sure there is a <canvas> with an id of 'drws-lib-canvas'.");

            return 0;
        };

        if(D_Canvas.tagName != "CANVAS"){
            console.log("Drws-lib: Warning, element found with 'drws-lib-canvas' is not a <canvas> element.");

            return 0;
        };

        D_Canvas.width = $0;
        D_Canvas.height = $1;

        window.D_Context = D_Canvas.getContext('2d');
        window.D_ImageData = D_Context.getImageData(0, 0, D_Canvas.width, D_Canvas.height);
        //var data = imageData.data;

        return 1;
    }, w, h);

    if(!foundUnusedCanvas){
        return D_NULL;
    };

    if(buffer1 != D_NULL){
        D_D_Buffer1 = D_CALLOC(w * h, sizeof(D_uint32));
    };

    if(buffer2 != D_NULL){
        D_D_Buffer2 = D_CALLOC(w * h, sizeof(D_uint32));
    };

    D_Surf * surf = D_CreateSurfFrom(w, h, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32), D_D_Buffer1);

    surf->outId = 1;

    return surf;
};

/* This function frees a surf created by
 *  D_GetOutSurf().
 *
 * This function returns -1 if s is null and does
 *  nothing.
 *
 * If the surface passed in was not created by
 *  D_GetOutSurf(), the function returns -2 and
 *  does nothing.
 *
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_FreeOutSurf(D_Surf * s){

    if(s == D_NULL){
        return -1;
    };

    if(s->outId != 1){
        return -2;
    };

    s->outId = 0;

    D_FreeSurf(s);
    s = D_NULL;

    if(D_D_Buffer1 != D_NULL){
        D_FREE(D_D_Buffer1);
        D_D_Buffer1 = D_NULL;
    };

    if(D_D_Buffer2 != D_NULL){
        D_FREE(D_D_Buffer2);
        D_D_Buffer2 = D_NULL;
    };

    EM_ASM({
        D_ImageData = undefined;
        D_Context = undefined;
        D_Canvas = undefined;
    });

    return 0;
};

/* This function takes in a surface created by
 *  D_GetOutSurf() and shows it onscreen.
 *
 * To show the backbuffer onscreen, this function
 *  copies it onto a JS ImageData connected to
 *  the canvas. This may need optimising.
 *
 * If s is null, the function does nothing and
 *  returns -1.
 *
 * If s is has not been created by
 *  D_GetOutSurf(), the function does nothing and
 *  returns -2.
 *
 * s: The surface to show onscreen.
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_FlipOutSurf(D_Surf * s){
    if(s == D_NULL){
        return -1;
    };

    if(s->outId != 1){
        return -2;
    };

    EM_ASM({

        /* Apparently malloc in emscripen is
         *  always aligned to 8 bytes
         *  https://reviews.llvm.org/D104808 */

        var pixel = 0;

        for(var i = 0; i < (D_Canvas.width * D_Canvas.height); i++){
            pixel = getValue($0, "i32");

            D_ImageData.data[(i * 4)    ] = ((pixel >>> 24) & 0xFF); //Red
            D_ImageData.data[(i * 4) + 1] = ((pixel >>> 16) & 0xFF); //Green
            D_ImageData.data[(i * 4) + 2] = ((pixel >>>  8) & 0xFF); //Blue
            D_ImageData.data[(i * 4) + 3] = ((pixel       ) & 0xFF); //Alpha

        };

        D_Context.putImageData(D_ImageData, 0, 0);
    }, (int)(s->pix));

    /*Flip the front and back buffers.*/
    if(s->pix == D_D_Buffer1){
        s->pix = D_D_Buffer2;
    }else{
        s->pix = D_D_Buffer1;
    };

    return 0;
};
