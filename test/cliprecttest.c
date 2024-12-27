#include<stdio.h>
#define D_IMPLEMENTATION
#include"../d.h"

/* Because of cliprecttesttool.c this test
 *  is not needed and is unfinished.
 */
int printRect(char * testInfo, D_Rect * r){
    printf("%s\nx: %d y: %d w: %d h: %d\n\n", testInfo, r->x, r->y, r->w, r->h);
};

int main(){
    D_Rect r = {40, 50, 100, 120};

    //cut noting test
    D_ClipRect(30, 40, 120, 140, &r);
    printRect("Should be 40, 50, 100, 120", &r);

    //cut off left by 10 test
    D_ClipRect(50, 40, 120, 140, &r);
    printRect("Should be 50, 50, 90, 120", &r);

    //cut off top by 10 test
    D_ClipRect(50, 60, 120, 140, &r);
    printRect("Should be 50, 60, 90, 110", &r);

    //cut off right by 10 test
    D_ClipRect(50, 60, 80, 140, &r);
    printRect("Should be 50, 60, 80, 110", &r);

    //cut off right by 10 test
    D_ClipRect(50, 60, 80, 100, &r);
    printRect("Should be 50, 60, 80, 100", &r);

    //cut off all sides by 10 test
    D_ClipRect(60, 70, 60, 80, &r);
    printRect("Should be 60, 70, 60, 80", &r);

    printf("\nTests for when inner rect is completely outside\n\n");

    //Test for when rect is completely outside
    //
    //   0         10        20
    //   ^         ^         ^
    //0  _________..________.._________
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |________||________||________|
    //10 _________..________.._________
    //   |        ||________||        |
    //   |        |||outer |||        |
    //   |        |||rect  |||        |
    //   |        |||      |||        |
    //   |        |||      |||        |
    //   |        |||      |||        |
    //   |        |||      |||        |
    //   |        |||______|||        |
    //   |________||________||________|
    //20 _________..________.._________
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |        ||        ||        |
    //   |________||________||________|
    //

    //Off the top left
    r.x = 0;
    r.y = 0;
    r.w = 10;
    r.h = 10;
    D_ClipRect(11, 11, 8, 8, &r);
    printRect("Should be 11, 11, 0, 0", &r);

    //Off the top
    r.x = 10;
    r.y = 0;
    r.w = 10;
    r.h = 10;
    D_ClipRect(11, 11, 8, 8, &r);
    printRect("Should be 11, 11, 8, 0", &r);

    //Off the top right
    r.x = 20;
    r.y = 0;
    r.w = 10;
    r.h = 10;
    D_ClipRect(11, 11, 8, 8, &r);
    printRect("Should be 18, 11, 0, 0", &r);

    return 0;
};
