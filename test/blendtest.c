#define D_IMPLEMENTATION
#include"../d.h"

#include<stdio.h>

/* This file is to test the D_Blend() function.
 */

int sr = 255, sg = 255, sb = 255, sa = 128;
int dr = 0, dg = 0, db = 0, da = 0;
int r = 1, g = 1, b = 1, a = 1;

int main(){

    D_Blend(D_BLENDMODE_NORMAL, sr, sg, sb, sa, dr, dg, db, da, &r, &g, &b, &a);
    printf("D_BLENDMODE_NORMAL test\n");
    printf("source: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst:    r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("result: r: %d g: %d b: %d a: %d\n", r, g, b, a);

    D_Blend(D_BLENDMODE_NONE, sr, sg, sb, sa, dr, dg, db, da, &r, &g, &b, &a);
    printf("\nD_BLENDMODE_NONE test\n");
    printf("source: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst:    r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("result: r: %d g: %d b: %d a: %d\n", r, g, b, a);

    D_Blend(D_BLENDMODE_ADD, sr, sg, sb, sa, dr, dg, db, da, &r, &g, &b, &a);
    printf("\nD_BLENDMODE_Add test\n");
    printf("source: r: %d g: %d b: %d a: %d\n", sr, sg, sb, sa);
    printf("dst:    r: %d g: %d b: %d a: %d\n", dr, dg, db, da);
    printf("result: r: %d g: %d b: %d a: %d\n", r, g, b, a);

};
