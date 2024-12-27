#include<SDL2/SDL.h>
#define D_IMPLEMENTATION
#include"../d.h"

#define WAIT 10000

int showSurf(D_Surf * s){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * w = SDL_CreateWindow("test", 10, 10, 640, 480, 0);
    SDL_Surface * ws = SDL_GetWindowSurface(w);
    SDL_Surface * sdls = SDL_CreateRGBSurfaceFrom(s->pix, s->w, s->h, s->format.bitDepth, s->w * (D_BITDEPTHTOBYTES(s->format.bitDepth)), s->format.rMask, s->format.gMask, s->format.bMask, s->format.aMask);
    //printf("SDL Error: %s\n", SDL_GetError());

    SDL_FillRect(ws, NULL, 0);
    SDL_BlitScaled(sdls, NULL, ws, NULL);


    SDL_UpdateWindowSurface(w);

    SDL_Delay(WAIT);

    SDL_DestroyWindow(w);
    ws = NULL;
    w = NULL;
    SDL_FreeSurface(sdls);
    sdls = NULL;

    return 0;
};

int resetRect(D_Rect * r){
    r->x = 50;
    r->y = 50;
    r->w = 50;
    r->h = 50;

    return 0;
};

int main(){
    D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    D_uint32 p = D_rgbaToFormat(s->format, 200, 255, 200, 255);
    D_Rect r;

    //Draw rect
    resetRect(&r);
    D_FillRect(s, &r, p);

    //Draw the rect off the left
    resetRect(&r);
    r.x = -10;
    D_FillRect(s, &r, p);

    //Draw the rect off the right
    resetRect(&r);
    r.x = 600;
    r.y += 150;
    D_FillRect(s, &r, p);

    //Draw the rect off the top
    resetRect(&r);
    r.x += 100;
    r.y = -20;
    D_FillRect(s, &r, p);

    //Draw the rect off the bottom
    resetRect(&r);
    r.x += 170;
    r.y = 460;
    D_FillRect(s, &r, p);

    showSurf(s);

    D_FreeSurf(s);
};
