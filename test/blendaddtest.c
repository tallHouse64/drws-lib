#include<stdio.h>
#define D_IMPLEMENTATION
#include"../d.h"

/*
 * The results of this test can be inaccurate by
 *  1.
 */

int sr = 245, sg = 20, sb = 201, sa = 255;
int dr = 40, dg = 243, db = 15, da = 255;
int rr = -1, rg = -1, rb = -1, ra = -1; //r for resullt

//e for expected
int test(int er, int eg, int eb, int ea){
    printf("src colour: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst colour: r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("should be : r: %d g: %d b: %d a: %d\n", er, eg, eb, ea);
    D_BlendAdd(sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);
    printf("res colour: r: %d g: %d b: %d a: %d\n\n", rr, rg, rb, ra);
    return 0;
};

int main(){
    printf("Testing D_BlendAdd()\n\n");


    test(255, 255, 216, 255);

    sa = 0;
    test(40, 243, 15, 255);

    sa = 127;
    test(162, 253, 115, 255);

    da = 0;
    test(162, 253, 115, 0);

    da = 50;
    sa = 70;
    test(107, 248, 70, 50);
};
