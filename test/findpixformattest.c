#include"../d.h"
#include<stdio.h>

int printPixFormat(D_PixFormat f){

    printf("rMaskShift: %d\n", f.rMaskShift);
    printf("rMaskLen: %d\n\n", f.rMaskLen);

    printf("gMaskShift: %d\n", f.gMaskShift);
    printf("gMaskLen: %d\n\n", f.gMaskLen);

    printf("bMaskShift: %d\n", f.bMaskShift);
    printf("bMaskLen: %d\n\n", f.bMaskLen);

    printf("aMaskShift: %d\n", f.aMaskShift);
    printf("aMaskLen: %d\n\n", f.aMaskLen);

    printf("rMask: %#x\n", f.rMask);
    printf("gMask: %#x\n", f.gMask);
    printf("bMask: %#x\n", f.bMask);
    printf("aMask: %#x\n", f.aMask);

    printf("bitDepth: %d\n\n\n", f.bitDepth);

    return 0;
};

int main(){

    D_PixFormat f = D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32);

    printPixFormat(f);


    //For NDS
    //( ((a) << 15) | (r)|((g)<<5)|((b)<<10))
    //ABBB BBGG GGGR RRRR
    f = D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16);

    printPixFormat(f);


    f = D_FindPixFormat(0xFF, 0xFF, 0xFF, 0x00, 8);

    printPixFormat(f);

    return 0;
};
