#include<SDL2/SDL.h>
#include"../d.h"

int showSurf(D_Surf * s){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * w = SDL_CreateWindow("test", 10, 10, 640, 480, 0);
    SDL_Surface * ws = SDL_GetWindowSurface(w);
    SDL_Surface * sdls = SDL_CreateRGBSurfaceFrom(s->pix, s->w, s->h, s->format.bitDepth, s->w * (D_BITDEPTHTOBYTES(s->format.bitDepth)), s->format.rMask, s->format.gMask, s->format.bMask, s->format.aMask);
    //printf("SDL Error: %s\n", SDL_GetError());

    SDL_FillRect(ws, NULL, 0);
    SDL_BlitScaled(sdls, NULL, ws, NULL);


    SDL_UpdateWindowSurface(w);

    SDL_Delay(1000);

    SDL_DestroyWindow(w);
    ws = NULL;
    w = NULL;
    SDL_FreeSurface(sdls);
    sdls = NULL;

    return 0;
};

int show8BitSurf(D_Surf * s){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * w = SDL_CreateWindow("8bit test", 10, 10, 640, 480, 0);
    SDL_Surface * ws = SDL_GetWindowSurface(w);
    SDL_Surface * sdls = SDL_CreateRGBSurface(0, 640, 480, 32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);

    SDL_FillRect(sdls, NULL, SDL_MapRGBA(sdls->format, 0, 0, 0, 255));
    SDL_FillRect(ws, NULL, SDL_MapRGBA(ws->format, 0, 0, 0, 255));

    int x = 0;
    int y = 0;
    while(y < sdls->h){
        x = 0;
        while(x < sdls->w){
            (((D_uint32 *)(sdls->pixels))[(y * sdls->w) + x] = ((D_uint8 *)(s->pix))[(y * s->w) + x] | (((D_uint8 *)(s->pix))[(y * s->w) + x] << 8) | (((D_uint8 *)(s->pix))[(y * s->w) + x] << 16) | (255 << 24));
            x++;
        };
        y++;
    };

    SDL_BlitScaled(sdls, NULL, ws, NULL);

    SDL_UpdateWindowSurface(w);

    SDL_Delay(3000);

    SDL_FreeSurface(sdls);
    sdls = NULL;
    SDL_DestroyWindow(w);
    w = NULL;
};

int main(){

    //ABGR8888 fill test
    D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));

    D_Rect r = {5, 5, 630, 470};
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 200, 255, 200, 255));

    //printf("Colour: %#x\n", D_rgbaToFormat(s->format, 200, 255, 200, 255));

    showSurf(s); //You should see a window open with a light green box in the middle and black around the sides

    D_FreeSurf(s);
    s = D_NULL;


    //ABBB BBGG GGGR RRRR fill test
    s = D_CreateSurf(640, 480, D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16));

    D_FillRect(s, &r, D_rgbaToFormat(s->format, 200, 255, 200, 255));

    showSurf(s);

    D_FreeSurf(s);
    s = D_NULL;


    //B&W fill test
    s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8));

    D_FillRect(s, &r, D_rgbaToFormat(s->format, 128, 128, 128, 255));

    //printf("8Bit Colour: %#x\n", ((D_uint8 *)(s->pix))[(5 * s->w) + 5]);

    show8BitSurf(s);

    D_FreeSurf(s);
    s = D_NULL;

    return 0;
};
