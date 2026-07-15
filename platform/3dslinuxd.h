#ifndef TDSLINUXD_H
#define TDSLINUXD_H

#include"../devents.h"
#include"../d.h"
#include"../dplatform.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define D_3DS_BPP 24 /* bits per pixel */
#define D_3DS_LINUX_PIXEL_FORMAT D_FindPixFormat(0xFF0000, 0xFF00, 0xFF, 0x0, D_3DS_BPP)
#define D_3DS_SCREEN_WIDTH 400
#define D_3DS_SCREEN_HEIGHT 240
#define D_3DS_NUM_SCREEN_BYTES ((D_3DS_SCREEN_WIDTH) * (D_3DS_SCREEN_HEIGHT) * ((D_3DS_BPP) / 8))

#endif

/* To compile programs that run on 3ds Linux, you
 *  need the arm-linux-gnueabi-gcc compiler. You
 *  also need to use the -static flag.
 */


#ifdef D_PLATFORM_IMPLEMENTATION
#ifndef D_PLATFORM_ALREADY_IMPLEMENTED
#define D_PLATFORM_ALREADY_IMPLEMENTED

D_Surf * D_D_TopScreen = D_NULL;

/* Made with open("/dev/fb0", O_RDWR) */
int D_D_TopScreenDev = -1;

/* Made with mmap() */
D_uint8 * D_D_ScreenMmap = D_NULL;

/* This function creates a surface for drawing to
 *  the top screen of a 3DS while running 3DS
 *  Linux and returns it.
 *
 * Free this surface with D_FreeOutSurf().
 *  It destroys the window.
 *
 * Note that this implementation of
 *  D_GetOutSurf() ignores the x, y, w and h
 *  parameters.
 *
 * This implementation of D_GetOutSurf() only
 *  works once, calling it again returns null.
 *
 * Other implementations don't necessarily ignore
 *  parameters (usually the implementations that
 *  work with a window manager that open a
 *  window).
 *
 * x: Ignored.
 * y: Ignored.
 * w: Ignored (400 is always used).
 * h: Ignored (240 is always used).
 * title: Ignored (for window titles).
 * flags: Ignored (always D_OUTSURFFULLSCREEN).
 * returns: A surface that gets copied to the
 *  screen when D_FlipOutSurf() is called, null
 *  is returned on error.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){

    D_Surf * out = D_NULL;

    if(D_D_TopScreen != D_NULL){
        return D_NULL;
    };

    /* Stop the terminal from drawing text to the
     *  top screen */
    system("stty -echo");


    /* Open the top screen device */
    D_D_TopScreenDev = open("/dev/fb0", O_RDWR);
    D_D_ScreenMmap = mmap(NULL, D_3DS_NUM_SCREEN_BYTES, PROT_READ | PROT_WRITE, MAP_SHARED, D_D_TopScreenDev, 0);

    /* Create a surface for the screen */
    D_D_TopScreen = D_CreateSurfFrom(D_3DS_SCREEN_WIDTH, D_3DS_SCREEN_HEIGHT, 0, D_NULL, D_3DS_LINUX_PIXEL_FORMAT, D_D_ScreenMmap);
    D_D_TopScreen->flags = D_OUTSURFFULLSCREEN;
    D_D_TopScreen->outId = 1;

    /* Create a back-buffer */
    out = D_CreateSurf(D_3DS_SCREEN_WIDTH, D_3DS_SCREEN_HEIGHT, D_3DS_LINUX_PIXEL_FORMAT);
    out->flags = D_OUTSURFFULLSCREEN;
    out->outId = 0;

    return out;
}

/* This function frees a surface created with
 *  D_GetOutSurf().
 *
 * If the surface was not created by
 *  D_GetOutSurf() the function does nothing and
 *  returns -2.
 *
 * If the surface is null, the function does
 *  nothing and returns -1.
 *
 * s: The surface to free.
 * Returns: 0 on success or a negative number on
 *  failure.
 */
int D_FreeOutSurf(D_Surf * s){

    if(s == D_NULL){
        return -1;
    };

    /* If the surface for the screen was passed
     *  in (outId == 1) or if the back-buffer was
     *  passed in (outId == 0), either way free
     *  the screen surface */
    if(s->outId == 0 || s->outId == 1){
        D_FreeSurf(D_D_TopScreen);

        munmap(D_D_ScreenMmap, D_3DS_NUM_SCREEN_BYTES);
        D_D_ScreenMmap = D_NULL;

        close(D_D_TopScreenDev);
        D_D_TopScreenDev = -1;

        /* Let the terminal draw text again */
        system("stty echo");

        if(s->outId == 1){
            /* If it was the screen surface we've
             *  done all we need to do */
            return 0;
        };
    };

    if(s->outId == 0){
        /* This is the back-buffer */
        D_FreeSurf(s);

        return 0;
    };

    return -2;
}

/* This function copies a back-buffer created by
 *  D_GetOutSurf() to the screen.
 *
 * If the surface was not created by
 *  D_GetOutSurf() the function does nothing and
 *  returns -2.
 *
 * If the surface is null, the function does
 *  nothing and returns -1.
 *
 * s: A surface created by D_GetOutSurf().
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_FlipOutSurf(D_Surf * s){

    if(s == D_NULL){
        return -1;
    };

    if(s->outId == 0){
        int i = 0;

        /* Copy the pixels from the back-buffer
         *  to the screen */
        while(i < D_3DS_NUM_SCREEN_BYTES){
            ((D_uint8 *)(D_D_TopScreen->pix))[i] = ((D_uint8 *)(s->pix))[i];
            i++;
        };

        return 0;
    };

    return -2;
}

/* This function blocks execution for "ms" number
 *  of milliseconds.
 *
 * ms: Milliseconds to wait.
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_Delay(int ms){
    return usleep(ms * 1000);
}

#endif /* D_PLATFORM_ALREADY_IMPLEMENTED */

#endif /* D_PLATFORM_IMPLEMENTATION */
