#include<stdlib.h>
#include<stdio.h>

void myFree(void * ptr){
    static int numCalls = 0;
    numCalls++;

    printf("myFree() called, %dth time\n", numCalls);
    free(ptr);
    return;
};

void * (*myCalloc)(size_t nmemb, size_t size) = calloc;

#define D_CALLOC myCalloc

#define D_FREE myFree

#define D_IMPLEMENTATION
#include"../d.h"

//This calloc always returns null.
void * brokenCalloc(size_t nmemb, size_t size){
    printf("brokenCalloc() not allocating\n");
    return D_NULL;
};

/*This calloc only works once. This is so that
 *  D_CreateSurf allocates a D_Surf without
 *  allocating pixel data.
 */
void * partlyBrokenCalloc(size_t nmemb, size_t size){
    static int state = 0;

    if(state == 0){
        state = 1;

        printf("partlyBrokenCalloc() allocating\n");
        return calloc(nmemb, size);
    };

    printf("partlyBrokenCalloc() not allocating\n");
    return D_NULL;
};

int main(){
    D_Surf * s = D_CreateSurf(256, 196, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 17));

    printf("Testing normally, should call myFree() twice at the end.\n\n");

    //not much to test right now
    printf("pix pointer: %p\n", s->pix);
    printf("w: %d\n", s->w);
    printf("h: %d\n", s->h);
    printf("outId: %d\n", s->outId);
    printf("alphaMod: %d\n", s->alphaMod);
    printf("blendMode: %d\n", s->blendMode);
    printf("flags: %d\n", s->flags);
    printf("outSurfFlags: %d\n", s->outSurfFlags);
    printf("bitDepth: %d\n", s->format.bitDepth);

    D_FreeSurf(s);
    s = D_NULL;
    printf("Surface freed\n");



    printf("\n\nTesting with a broken D_CALLOC, shouldn't call myFree().\n\n");

    myCalloc = brokenCalloc;

    s = D_CreateSurf(256, 196, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 17));

    printf("surf pointer: %p\n", s);



    printf("\n\nTesting with partly broken D_CALLOC, should call myFree() once.\n\n");

    myCalloc = partlyBrokenCalloc;

    s = D_CreateSurf(256, 196, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 17));

    printf("surf pointer: %p\n", s);
};
