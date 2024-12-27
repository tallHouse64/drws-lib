#include<stdio.h>
#include"../d.h"

int main(){
    printf("D_ConvertPixel() Test\n");

    D_PixFormat from = {0};
    D_PixFormat to = {0};
    D_uint32 p = 0;




    printf("\n Tests from RGBA8888 format\n");
    from = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);



    p = 0xFF7BFF90;//#90ff7b r: 144, g: 255, b: 123, a: 255.
    to = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16); //NDS format

    // ABBB BBGG GGGR RRRR
    //  14    31    17
    // 1011 1011 1111 0001
    //Should be
    //0x  B    B    F    1
    printf("Test 1 to NDS Colour: %#x\n", D_ConvertPixel(from, to, p));


    p = 0xFF48C44D;//#90ff7b r: 144, g: 255, b: 123, a: 255.
    to = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8); //B&W format

    // r: 77, g: 196, b:72 average: 115
    //Should be 0x73
    printf("Test 2 to B&W Colour: %#x\n", D_ConvertPixel(from, to, p));




    //Tests from NDS
    printf("\n Tests from NDS format\n");
    from = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);



    p = 0xBBF1;//#90ff7b r: 144, g: 255, b: 123, a: 255.
    to = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);

    //0x  B    B    F    1
    // 1011 1011 1111 0001
    // ABBB BBGG GGGR RRRR
    // r: 139, g:255, b: 115
    //Should be: 0xFF73FF8B
    //
    //   approx 0xFF7BFF90
    printf("Test 3 to RGBA8888 Colour: %#x\n", D_ConvertPixel(from, to, p));


    p = 0x7678;//#90ff7b r: 144, g: 255, b: 123, a: 255.
    to =   D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);

    //0x  7    6    7    8
    // ABBB BBGG GGGR RRRR
    // 0111 0110 0111 1000
    //  B:29  G:19  R:24
    //R:238 G:156 B:197 average: 197
    //Should be 0xC5
    printf("Test 4 to B&W Colour: %#x\n", D_ConvertPixel(from, to, p));



    printf("\n Tests from B&W format\n");
    from = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0, 8);



    p = 0xA5;
    to = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);

    //Should be 0x00A5A5A5
    printf("Test 5 to RGBA8888 Colour: %#x\n", D_ConvertPixel(from, to, p));

    p = 0x45;
    to = D_FindPixFormat(0x1F, 0x3E0, 0x7C00, 0x8000, 16);

    //8
    //ABBB BBGG GGGR RRRR
    //0010 0001 0000 1000
    //0x 2    1    0    8
    printf("Test 6 to NDS Colour: %#x\n", D_ConvertPixel(from, to, p));

    return 0;
};
