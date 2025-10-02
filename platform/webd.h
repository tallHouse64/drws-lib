#include<emscripten.h>
#include"../d.h"
#include"../devents.h"
#include"../dplatform.h"

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
 * x: This number gets ignored.
 * y: This number gets ignored.
 * w: The width to set the html canvas element to.
 * h: The height to set the html canvas element to.
 * title: This gets ignored.
 * flags: This gets ignored.
 * returns: A pointer to a surface or null on failure.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){

    void * data = EM_ASM_PTR({

        if(typeof D_Canvas !== 'undefined'){
            console.log("Drws-lib: Warning, D_GetOutSurf() called more than once without calling D_FreeOutSurf().");
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

        return D_ImageData.data;
    }, w, h);

    if(data == D_NULL){
        return D_NULL;
    };

    D_Surf * surf = D_CreateSurfFrom(w, h, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32), data);

    surf->outId = 1;

    return surf;
};

/* This function frees a surf created by
 *  D_GetOutSurf().
 *
 * This function returns -1 if s is null.
 *
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_FreeOutSurf(D_Surf * s){

    if(s == D_NULL){
        return -1;
    };

    s->outId = 0;

    D_FreeSurf(s);
    s = D_NULL;

    EM_ASM({
        D_Canvas = undefined;
        D_Context = undefined;
        D_ImageData = undefined;
    });

    return 0;
};

/* This function takes in a surface created by
 *  D_GetOutSurf() and shows it onscreen.
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
        D_Context.putImageData(D_ImageData, 0, 0);
    });
    return 0;
};
