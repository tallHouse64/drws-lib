#include<stdio.h>
#include"../d.h"

//This is different to formattorgbatest.c

int main(){
    printf("D_RawFormatTorgba() Test.\n\n");
    D_PixFormat f = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);



    D_uint32 p = 0xFFE0C052; // This is just #52C0E0
    int r = 0, g = 0, b = 0, a = 0;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 82, 192, 224, 255
    printf("Test 1 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 0, 0, 0, 0
    printf("Test 2 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0xFF0085FF; //#ff8500
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 255, 133, 0, 255
    printf("Test 3 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0xFFFFFFFF; //#ffffff
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 255, 255, 255, 255
    printf("Test 4 Colour:  r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0xFFFFFFFF; //#ffffff
    r = 0;
    D_RawFormatTorgba(p, f, D_NULL, &g, &b, &a);
    //Should be 0, 255, 255, 255
    printf("Test 5 Colour:  r: %d, g: %d, b: %d, a: %d. (error test)\n", r, g, b, a);



    //NDS Colour tests
    printf("\nNDS Format tests.\n");
    f = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);

    p = 0xFF18;
    //    F    F    1    8
    // 1111 1111 0001 1000
    // ABBB BBGG GGGR RRRR
    // 1B:31  G: 24   R: 24
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 24, 24, 31, 1
    printf("Test 6 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0x7678;
    //    7    6    7    8
    // 0111 0110 0111 1000
    // ABBB BBGG GGGR RRRR
    // 0B:29  G: 19   R: 24
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 24, 19, 29, 0
    printf("Test 7 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0xFFFF;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 31, 31, 31, 1
    printf("Test 8 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 0;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 0, 0, 0, 0
    printf("Test 9 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);



    printf("\nB&W format tests.\n");
    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);
    p = 170;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 170, 170, 170, 0
    printf("Test 10 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    p = 255;
    D_RawFormatTorgba(p, f, &r, &g, &b, &a);
    //Should be 255, 255, 255, 0
    printf("Test 11 Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a);


    return 0;
};
