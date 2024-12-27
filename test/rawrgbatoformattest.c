#include<stdio.h>
#include"../d.h"

int main(){
    printf("D_RawrgbaToFormat() Test\n");

    //Test 1
    printf("Now testing with RGBA format");
    D_PixFormat f = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);

    D_uint32 col = D_RawrgbaToFormat(f, 100, 200, 100, 255);

    //It should say FF64C864
    //              AABBGGRR
    printf("Test 1 Colour: %#x\n", col);


    //Test 2
    col = D_RawrgbaToFormat(f, 0xF02, 0x10, 0x01, 0xFFFF); //Some of the numbers should overflow and the overflow should be ignored

    //It should say FF011002
    //              AABBGGRR
    printf("Test 2 Colour: %#x\n", col);


    //Test 3
    printf("Now testing with NDS format.\n");
    f = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);
    col = D_RawrgbaToFormat(f, 20, 31, 20, 1);

    //It should say D3F4    1101 0011 1111 0100
    //                      ABBB BBGG GGGR RRRR
    printf("Test 3 colour: %#x\n", col);


    //Test 4
    col = D_RawrgbaToFormat(f, 0, 0xFFFFFFFF, 0, 0xFFFFFFFF); //Overflow should be ignored

    //It should say 83E0    1000 0011 1110 0000
    //                      ABBB BBGG GGGR RRRR
    printf("Test 4 colour: %#x\n", col);


    //Test 5
    col = D_RawrgbaToFormat(f, 0xFFFFFFFF, 0, 0xFFFFFFFF, 0); //Overflow should be ignored

    //It should say 7C1F    0111 1100 0001 1111
    //                      ABBB BBGG GGGR RRRR
    printf("Test 5 colour: %#x\n", col);


    printf("Now testing with B&W format.\n");
    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);

    col = D_RawrgbaToFormat(f, 100, 200, 175, 255);
    //It should say 0x9E
    printf("Test 6 colour: %x\n", col);

    col = D_RawrgbaToFormat(f, 97, 12, 237, 255);
    //It should say 0x73
    printf("Test 7 colour: %x\n", col);

    return 0;
};
