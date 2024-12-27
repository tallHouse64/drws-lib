#include"../d.h"
#include<stdio.h>

int main(){

    printf("D_GetMaskShift tests:\n\n");

    int m = 0x00FF0000;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    m = 0xF0;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    m = 0x2;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    m = 0x1;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    m = 0x80000000;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    m = 0x0;
    printf("m: %#x shift: %d\n", m, D_GetMaskShift(m));

    printf("\n\n");

    printf("D_GetMaskShift tests:\n\n");

    m = 0x00FF0000;
    printf("m: %#x len: %d\n", m, D_GetMaskLen(m));

    m = 0x00000001;
    printf("m: %#x len: %d\n", m, D_GetMaskLen(m));

    m = 0x001C0000;
    printf("m: %#x len: %d\n", m, D_GetMaskLen(m));

    m = 0x80000000;
    printf("m: %#x len: %d\n", m, D_GetMaskLen(m));

    m = 0x0;
    printf("m: %#x len: %d\n", m, D_GetMaskLen(m));

    return 0;
};
