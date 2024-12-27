#include<stdio.h>
#include"../devents.h"

#define POS_LEN 5
struct {
    int x, y;
} pos[POS_LEN] = {{23, 55}, {40, 70}, {50, 75}, {32, 11}, {23, 37}};

//This test should print the above list, many times. It should finish on 23, 11.

int main(){
    D_Event in = {0};
    in.type = D_MOUSEMOVE;

    D_Event out = {0};

    D_StartEvents();

    int i = 0;
    while(i < 254){

        in.mouse.x = pos[i % POS_LEN].x;
        in.mouse.y = pos[i % POS_LEN].y;
        D_CauseEvent(&in);

        D_GetEvent(&out);
        printf("'Mouse' x:%d, y:%d\n", in.mouse.x, in.mouse.y);
        i++;
    };

    D_StopEvents();
};
