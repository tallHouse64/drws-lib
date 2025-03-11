#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

int main(){
    D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));

    printf("alphaMod: %d\nShould be: 255\n\n", s->alphaMod);

    D_SetSurfAlphaMod(s, 50);
    printf("alphaMod: %d\nShould be: 50\n\n", s->alphaMod);

    D_SetSurfAlphaMod(s, 245);
    printf("alphaMod: %d\nShould be: 245\n\n", s->alphaMod);

    D_SetSurfAlphaMod(s, 0);
    printf("alphaMod: %d\nShould be: 0\n\n", s->alphaMod);

    D_SetSurfAlphaMod(s, 255);
    printf("alphaMod: %d\nShould be: 255\n\n", s->alphaMod);

};
