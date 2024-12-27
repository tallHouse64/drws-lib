#include<stdio.h>
#define D_IMPLEMENTATION
#include"../d.h"

//Worked first time!
//I wrote D_PointInRect() in college break and tested it there in another breaak same day.

D_Point p = {0};
D_Rect r = {10, 10, 10, 100};

int test(int e){ //e for expect
    printf("Point x: %d y: %d\nRect x: %d y: %d w: %d h: %d\nShould be %d\nResult %d\n\n", p.x, p.y, r.x, r.y, r.w, r.h, e, D_PointInRect(&p, &r));
};

int main(){

    //Outside top left test
    p.x = 9; p.y = 9;
    test(0);

    //Outside top test
    p.x = 10; p.y = 9;
    test(0);

    //Outside left test
    p.x = 9; p.y = 10;
    test(0);

    //Inside top left test
    p.x = 10; p.y = 10;
    test(1);

    //Outside bottom right test
    p.x = 20; p.y = 110;
    test(0);

    //Outside bottom test
    p.x = 19; p.y = 110;
    test(0);

    //Outside right test
    p.x = 20; p.y = 109;
    test(0);

    //Inside bottom right test
    p.x = 19; p.y = 109;
    test(1);

};
