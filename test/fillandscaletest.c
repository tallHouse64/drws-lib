#include<stdio.h>
#include<SDL2/SDL.h>
#include"d.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

int showSurf(D_Surf * s){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * w = SDL_CreateWindow("test", 10, 10, 640, 480, 0);
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

    D_Surf * s = D_CreateSurf(640, 480);

    D_Rect r = {5, 5, 630, 470};//{5, 5, 22, 22};//{-10, -10, 255, 255};
    D_FillRect(s, NULL, D_rgbaToABGR8888(255, 255, 255, 255));
    D_FillRect(s, &r, D_rgbaToABGR8888(100, 255, 100, 255));

    printf("num %#04X\n", ((D_uint32 *) s->pix)[(10 * s->w) + 10]);



    int x, y, n;

    void * dat = stbi_load("fi2.bmp", &x, &y, &n, 4);

    D_Surf * img = 0x0;

    if(dat != NULL){

        printf("Got image.\n");
        img = D_CreateSurf(x, y);
        memcpy(img->pix, dat, x * y * 4);
        printf("Done copy.\n");

    }else{
        printf("Failed to get image.\n");
    };

    stbi_image_free(dat);

    //D_SurfCopyScale(img, D_NULL, s, D_NULL);

    D_Rect r2 = {20, 20, 200, 200};
    D_Rect r1 = {314, 299, 360, 482};//{x/4, y/4, x/2, y/2};
    D_SurfCopyScale(img, &r1, s, &r2);


    showSurf(img);
    showSurf(s);
    D_FreeSurf(img);
    D_FreeSurf(s);
};
