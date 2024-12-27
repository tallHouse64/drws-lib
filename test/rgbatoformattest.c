#include<stdio.h>
#include"../d.h"

int main(){
    D_PixFormat f = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);

    //Should be 0xFFFFC8C8
    printf("Test 1 colour: %#x\n", D_rgbaToFormat(f, 200, 200, 255, 255));

    //Should be 0xFFFFFFFF
    printf("Test 2 colour: %#x\n", D_rgbaToFormat(f, 1000, 72624, 7718, 38489));

    //Should be 0x00000000
    printf("Test 3 colour: %#x\n", D_rgbaToFormat(f, -31, -6382, -1, -83783));


    // ( ((a) << 15) | (r)|((g)<<5)|((b)<<10))
    //ABBB BBGG GGGR RRRR
    f = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);

    printf("\nNDS format test.\n");

    //Should be 1111 1111 0001 1000  0xFF18
    //        0x   F    F    1    8
    printf("Test 4 %#x\n", D_rgbaToFormat(f, 200, 200, 255, 255));

    //CB9FF0
    //Should be 0 11101 10011 11000
    //          0111 0110 0111 1000
    //        0x   7    6    7    8
    printf("Test 4 %#x\n", D_rgbaToFormat(f, 203, 159, 240, 126));


    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);

    printf("\nB&W format test.\n");

    //Should be 0x64
    printf("Test 5 %#x\n", D_rgbaToFormat(f, 100, 100, 100, 255));

    //Should be 0x42 (average colour test (r+g+b)/3 )
    printf("Test 6 %#x\n", D_rgbaToFormat(f, 45, 81, 72, 255));


    return 0;
};
