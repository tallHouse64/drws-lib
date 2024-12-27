#include<SDL2/SDL.h>

#define D_IMPLEMENTATION
#include"../d.h"

#define WAIT 1000

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

    SDL_Delay(WAIT);

    SDL_FreeSurface(sdls);
    sdls = NULL;
    SDL_DestroyWindow(w);
    w = NULL;
};

/* This just fills 3 rectangles with colours on s,
 *  just for testing. Saves having to read a bmp.
 */
int drawToSurf(D_Surf * s){
    D_FillRect(s, D_NULL, D_rgbaToFormat(s->format, 255, 255, 255, 255));

    D_Rect r = {10, 20, 100, 160};
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 255, 200, 200, 255));

    r.x += 120;
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 190, 240, 190, 255));

    r.x -= 60;
    r.y += 70;
    r.h = 50;
    r.w = 300;
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 170, 170, 220, 255));

    return 0;
};

int main(){
    D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32)); //src

    printf("Remember!!! To avoid confusion, s is the small surface getting copied to the outer d surface.\n");

    //Draw to s
    drawToSurf(s);
    printf("Showing src surf.\n");
    showSurf(s);

    //Below are scale tests,
    //First are from AGBA8888 to RGBA8888, to NDS and to B&W

    printf("\nScale from RGBA8888 tests.\n");


    printf("Scale RGBA8888 to RGBA8888 test.\n");
    D_Surf * d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32)); //dst
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 200, 100, 100, 255));
    D_Rect rd = {40, 40, 200, 100};
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("Scale RGBA8888 to NDS format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 200, 100, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("Scale RGBA8888 to B&W format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 100, 200, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    show8BitSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("\nScale from NDS tests.\n");

    D_FreeSurf(s);
    s = D_NULL;
    s = D_CreateSurf(640, 480, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16)); //src


    //Draw to s
    drawToSurf(s);
    printf("Showing src surf now in NDS format.\n");
    showSurf(s);


    printf("Scale NDS to RGBA8888 format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 200, 100, 100, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;



    printf("Scale NDS to NDS format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 200, 100, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;



    printf("Scale NDS to B&W format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 100, 200, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    show8BitSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("\nScale from B&W tests.\n");



    D_FreeSurf(s);
    s = D_NULL;
    s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8)); //src
    drawToSurf(s);
    printf("Showing src surf now in B&W format.\n");
    show8BitSurf(s);


    printf("Scale B&W to RGBA8888 format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 200, 100, 100, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("Scale B&W to NDS format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 200, 100, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    showSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    printf("Scale B&W to B&W format test.\n");
    d = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8));
    D_FillRect(d, D_NULL, D_rgbaToFormat(d->format, 100, 100, 200, 255));
    D_SurfCopyScale(s, D_NULL, d, &rd);
    show8BitSurf(d);

    D_FreeSurf(d);
    d = D_NULL;


    D_FreeSurf(s);
    s = D_NULL;
};
