#include<SDL2/SDL.h>
#define D_ALLOW_STB_IMAGE
#define D_IMPLEMENTATION
#include"../d.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

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

int main(){
    D_Surf * s = D_LoadImage("../fi.bmp");

    showSurf(s);

    D_FreeSurf(s);
    s = D_NULL;

    return 0;
};
