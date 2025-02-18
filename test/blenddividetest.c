#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

/* This file tests the D_BlendDivide() function.
 *
 * The results of this test can be inaccurate by
 *  1.
 */

int sr = 245, sg = 20, sb = 201, sa = 255;
int dr = 100, dg = 243, db = 40, da = 255;
int rr = -1, rg = -1, rb = -1, ra = -1; //r for resullt

//e for expected
int test(int er, int eg, int eb, int ea){
    printf("src colour: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst colour: r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("should be : r: %d g: %d b: %d a: %d\n", er, eg, eb, ea);
    D_BlendDivide(sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);
    printf("res colour: r: %d g: %d b: %d a: %d\n\n", rr, rg, rb, ra);
    return 0;
};

int main(){
    printf("Testing D_BlendAdd()\n\n");

    //                      dstRGB * 256       srcA       dstRGB   255 - srcA
    // dstRGB = ( min( W, ( ------------ ) ) * ---- ) + (        * ---------- )
    //                       srcRGB + 1        255                    255

    test(104, 255, 50, 255);

    sa = 0;
    test(100, 243, 40, 255);

    sa = 127;
    test(102, 248, 45, 255);

    da = 0;
    test(102, 248, 45, 0);

    da = 50;
    sa = 70;
    test(101, 246, 42, 50);
};
