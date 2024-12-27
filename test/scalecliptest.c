#include<SDL2/SDL.h>

#define D_IMPLEMENTATION
#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include"../d.h"

#define WAIT 3000

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
    r->x = 70;
    r->y = 10;
    r->w = 50;
    r->h = 50;

    return 0;
};

int main(){
    D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    D_Surf * img = D_LoadImage("../fi.bmp");

    D_Rect r;
    resetRect(&r);
    D_SurfCopyScale(img, D_NULL, s, &r);

    resetRect(&r);
    r.x = -10;
    D_SurfCopyScale(img, D_NULL, s, &r);

    resetRect(&r);
    r.x = 620;
    r.y += 70;
    D_SurfCopyScale(img, D_NULL, s, &r);

    resetRect(&r);
    r.y = -20;
    r.x += 100;
    D_SurfCopyScale(img, D_NULL, s, &r);

    resetRect(&r);
    r.y = 470;
    r.x += 200;
    D_SurfCopyScale(img, D_NULL, s, &r);

    showSurf(s);

    D_FreeSurf(img);
    img = D_NULL;
    D_FreeSurf(s);
    s = D_NULL;
};
