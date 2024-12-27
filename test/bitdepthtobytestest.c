#include<stdio.h>
#include"../d.h"

int main(){
    int i = -4;
    while(i < 35){
        printf("bitDepth: %d, bytes: %d\n", i, D_BITDEPTHTOBYTES(i));
        i++;
    };

    //It should print -2 (error) for all negativ numbers and 0
    //It should print 1 byte for 1 to 8
    //It should print 2 bytes for 9 to 16
    //It should print 4 bytes for 17 to 32
    //It should print -1 (meaning error) for 33 and bigger
};
