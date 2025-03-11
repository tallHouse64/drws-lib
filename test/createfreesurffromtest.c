#include<stdlib.h>
#include<stdio.h>

void * myCalloc(size_t nmemb, size_t size){
    printf("myCalloc() called\n");
    return calloc(nmemb, size);
};

void myFree(void * ptr){
    printf("myFree() called\n");
    free(ptr);
    return;
};

#define D_CALLOC myCalloc
#define D_FREE myFree

#define D_IMPLEMENTATION
#include"../d.h"

/* This file tests if the D_CreateSurfFrom()
 *  function works.
 *
 * When a preallocated surface (made by
 *  D_CreateSurfFrom()) is freed, it should only
 *  call D_FREE() once. This file also tests to
 *  make sure this happens.
 */

D_uint32 pixels[(256 * 196)] = {0};

int main(){
    printf("Testing D_CreateSurfFrom()\n\n");

    printf("Creating surface, should call myCalloc() once.\n");
    D_Surf * s = D_CreateSurfFrom(256, 196, D_FindPixFormat(0xFF, 0x00FF, 0x0000FF, 0x000000FF, 32), &(pixels[0]));

    printf("pix pointer: %p\n", s->pix);
    printf("w: %d\n", s->w);
    printf("h: %d\n", s->h);
    printf("outId: %d\n", s->outId);
    printf("alphaMod: %d\n", s->alphaMod);
    printf("blendMode: %d\n", s->blendMode);
    printf("flags: %d\n", s->flags);
    printf("outSurfFlags: %d\n", s->outSurfFlags);
    printf("bitDepth: %d\n", s->format.bitDepth);

    D_FillRect(s, D_NULL, D_rgbaToFormat(s->format, 255, 255, 255, 255));

    printf("Freeing surface, should call myFree() once.\n");
    D_FreeSurf(s);
    s = D_NULL;

};
