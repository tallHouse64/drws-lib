#include<SDL2/SDL.h>

#define ALLOW_STB_IMAGE
#include"d.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

int showSurf(D_Surf * s){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * w = SDL_CreateWindow("test", 10, 10, s->w/8, s->h/8, 0);
    SDL_Surface * ws = SDL_GetWindowSurface(w);
    SDL_Surface * sdls = SDL_CreateRGBSurfaceFrom(s->pix, s->w, s->h, 32, s->w * 4, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);

    SDL_FillRect(ws, NULL, 0);
    SDL_BlitScaled(sdls, NULL, ws, NULL);


    SDL_UpdateWindowSurface(w);

    SDL_Delay(3000);

    SDL_DestroyWindow(w);
    ws = NULL;
    w = NULL;
    SDL_FreeSurface(sdls);
    sdls = NULL;

    return 0;
};

int main(){
    D_Surf * s = D_LoadImage("folder.png");

    showSurf(s);

    D_FreeSurf(s);

    return 0;
};
