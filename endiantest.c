#include<stdio.h>

//Thank you for the answer: https://stackoverflow.com/questions/4181951/how-to-check-whether-a-system-is-big-endian-or-little-endian

//This was there too: perl -e 'use Config; print $Config{byteorder}'
//It should print 1 on the firt digi for little endian


int main(){
    int n = 1;

    //little endian if true
    if(*(char *)&n == 1){
        printf("This computer is little endian.\n");
    }else{
        printf("This computer is big endian.\n");
    };

    // return 0;
};
