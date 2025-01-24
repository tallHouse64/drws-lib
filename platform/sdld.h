#include<SDL2/SDL.h>
#include"../devents.h"
#include"../d.h"

#ifdef D_PLATFORM_IMPLEMENTATION
#ifndef D_PLATFORM_ALREADY_IMPLEMENTED
#define D_PLATFORM_ALREADY_IMPLEMENTED

SDL_Window * sdlw[D_MAX_OUT_SURFS] = {NULL};
SDL_Surface * sdls[D_MAX_OUT_SURFS] = {NULL};

/* This creates a window that can be drawn
 *  to, remember call D_FlipOutSurf() on
 *  it after drawing to show it onto the
 *  screen.
 *
 * Free this surface with D_FreeOutSurf().
 *  It destroys the window.
 *
 * This is called D_GetOutSurf() because it
 *  just gets a surface to output onto. On
 *  Windows, Mac, Linux this would just
 *  make a window but on NDS for example
 *  it doesn't make sence to make a window
 *  this is why it's not called
 *  D_CreateWindow(). Remember the purpose
 *  of this lib is to be as cross platfor
 *  as possible.
 *
 * x: X pos of where the top left of the window should go.
 * y: Y pos of where the top left of the window should go.
 * w: The width of the window.
 * h: The height of the window.
 * title: What the top of the window should say.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){

    //Find next unused (NULL) element in sdlw
    int i = 0;
    while(i < D_MAX_OUT_SURFS && sdlw[i] != NULL){
        i++;
    };

    //printf("Found Id: %d\n", i);

    if(i == D_MAX_OUT_SURFS){
        return D_NULL;
    };


    //Translate the flags

    SDL_WindowFlags windowFlags = 0;

    if(flags & D_OUTSURFRESIZABLE){
        windowFlags = windowFlags | SDL_WINDOW_RESIZABLE;
    };


    sdlw[i] = SDL_CreateWindow(title, x, y, w, h, windowFlags);

    sdls[i] = SDL_GetWindowSurface(sdlw[i]);

    D_Surf * s = D_CALLOC(1, sizeof(D_Surf));
    s->pix = sdls[i]->pixels;
    s->w = sdls[i]->w;
    s->h = sdls[i]->h;
    s->outId = i;

    //From looking at SDL_Pixels.h, because SDL_PixelFormat
    //has a BytesPerPixel it makes me think that all SDL
    //surfaces store pixels like d.h does,only storing
    //pixles in byte sizes.
    //todo: make sure that's true, fix if not.
    s->format = D_FindPixFormat(sdls[i]->format->Rmask, sdls[i]->format->Gmask, sdls[i]->format->Bmask, sdls[i]->format->Amask, sdls[i]->format->BitsPerPixel);
    return s;
};

/* Use this to free the surface created
 *  by D_GetOutSurf(), it destroys it's
 *  window.
 *
 * s: The outSurf to free.
 */
int D_FreeOutSurf(D_Surf * s){

    //Make it safe
    if(s->outId < 0){
        return -1;
    };

    SDL_DestroyWindow(sdlw[s->outId]);
    sdlw[s->outId] = NULL;
    sdls[s->outId] = NULL;
    D_FREE(s);
    s = D_NULL;

    return 0;
};

/* This takes the an outSurf created by
 *  D_GetOutSurf() and shows it onto the
 *  screen.
 *
 * s: The outSurf to free.
 */
int D_FlipOutSurf(D_Surf * s){

    //Make it safe (in case s is a regular surf made by D_CreateSurf())
    if(s->outId < 0){
        return -1;
    };

    SDL_UpdateWindowSurface(sdlw[s->outId]);
    return 0;
};

int D_PumpEvents(){
    SDL_PumpEvents();
    SDL_Event se;
    D_Event e;

    //For every SDL event
    while(SDL_PeepEvents(&se, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0){

        //Translate it to a D event and add it to the queue
        switch(se.type){
            case SDL_MOUSEBUTTONDOWN:
                e.type = D_MOUSEDOWN;
                e.mouse.x = se.button.x;
                e.mouse.y = se.button.y;
                D_CauseEvent(&e);
                break;
            case SDL_MOUSEBUTTONUP:
                e.type = D_MOUSEUP;
                e.mouse.x = se.button.x;
                e.mouse.y = se.button.y;
                D_CauseEvent(&e);
                break;
            case SDL_MOUSEMOTION:
                e.type = D_MOUSEMOVE;
                e.mouse.x = se.motion.x;
                e.mouse.y = se.motion.y;
                D_CauseEvent(&e);
                break;
            case SDL_QUIT:
                e.type = D_QUIT;
                D_CauseEvent(&e);
                break;
        };

    };
    return 0;
};

/* This stops the thread from running
 *  for ms millisecon.
 *
 * ms: how many millisecon to stop.
 */
int D_Delay(int ms){
    SDL_Delay(ms);
    return 0;
};

#endif // D_PLATFORM_ALREADY_IMPLEMENTED

#endif // D_PLATFORM_IMPLEMENTATION
