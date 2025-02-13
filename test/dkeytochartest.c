#include<stdio.h>

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

/* This tests D_DKeyToChar(), it does not test
 *  every single key because it's just a switch.
 *  Testing all the keys would be remaking the
 *  functionality. If a few work, they should all
 *  work.
 */

int main(){
    printf("D_DKeyToChar() Test\n\n");

    printf("D_Ka: %c\n", D_DKeyToChar(D_Ka));
    printf("D_Kb: %c\n", D_DKeyToChar(D_Kb));
    printf("D_Kc: %c\n", D_DKeyToChar(D_Kc));


    printf("D_Kz: %c\n", D_DKeyToChar(D_Kz));

    printf("D_K0: %c\n", D_DKeyToChar(D_K0));
    printf("D_K1: %c\n", D_DKeyToChar(D_K1));
    printf("D_K2: %c\n", D_DKeyToChar(D_K2));
    printf("D_K9: %c\n", D_DKeyToChar(D_K9));

    printf("D_KAsterisk: %c\n", D_DKeyToChar(D_KAsterisk));
    printf("D_KSemicolon: %c\n", D_DKeyToChar(D_KSemicolon));

    printf("\nTests below should return null\n\n");

    printf("D_KLeftCtrl: %c\n", D_DKeyToChar(D_KLeftCtrl));
    printf("D_KRightShift: %c\n", D_DKeyToChar(D_KRightShift));
};
