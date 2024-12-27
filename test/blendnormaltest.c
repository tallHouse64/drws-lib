#include<stdio.h>
#define D_IMPLEMENTATION
#include"../d.h"

/*
 * Remember in this test if the colours are inaccurate by
 *  1 is is ok because some of the tests are done with a different
 *  metho.
 */

int sr = 245, sg = 20, sb = 251, sa = 255;
int dr = 40, dg = 243, db = 15, da = 255;
int rr = -1, rg = -1, rb = -1, ra = -1; //r for resullt

//e for expected
int test(int er, int eg, int eb, int ea){
    printf("src colour: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst colour: r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("should be : r: %d g: %d b: %d a: %d\n", er, eg, eb, ea);
    D_BlendNormal(sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);
    printf("res colour: r: %d g: %d b: %d a: %d\n\n", rr, rg, rb, ra);
    return 0;
};

int main(){
    printf("Testing D_BlendNormal()\n\n");

    //This testing is not thouroug, it is too tedious.
    //It might be better to test through using it in D_SurfCopyScale().
    test(245, 20, 251, 255);

    sa = 0;
    test(40, 243, 15, 255);

    sa = 127;
    test(142, 131, 133, 255); //Close enough

    sa = 201;
    //(((sr * sa) / 255)) + ((dr * (255 - sa)) / 255)
    //(((245 * 201) / 255)) + ((40 * (255 - 201)) / 255)
    //139 + 8
    test(201, 67, 201, 255);

    da = 50;
    //201 + ((50 * (255 - 201)) / 255)
    test(201, 67, 201, 211);
};
