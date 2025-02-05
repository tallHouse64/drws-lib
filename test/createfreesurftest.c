#include<stdio.h>
#define D_IMPLEMENTATION
#include"../d.h"

int main(){
    D_Surf * s = D_CreateSurf(256, 196, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 17));

    //not much to test right now
    printf("pix pointer: %p\n", s->pix);
    printf("w: %d\n", s->w);
    printf("h: %d\n", s->h);
    printf("outId: %d\n", s->outId);
    printf("blendMode: %d\n", s->blendMode);
    printf("bitDepth: %d\n", s->format.bitDepth);

    D_FreeSurf(s);
    s = D_NULL;
    printf("Surface freed\n");
};
