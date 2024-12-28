#include"../sdld.h"

#define D_IMPLEMENTATION
#include"../../d.h"

int main(){
    D_Surf * s = D_GetOutSurf(10, 10, 640, 480, "Box Test");

    D_Rect r = {40, 40, 120, 80};
    D_FillRect(s, D_NULL, D_rgbaToFormat(s->format, 255, 200, 200, 255));
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 200, 255, 200, 255));


    D_Surf * s2 = D_GetOutSurf(20, 20, 800, 300, "Box Test Window 2");
    r.y += 40;
    D_FillRect(s2, D_NULL, D_rgbaToFormat(s2->format, 200, 200, 255, 255));
    D_FillRect(s2, &r, D_rgbaToFormat(s2->format, 255, 200, 200, 255));

    D_FlipOutSurf(s);
    D_FlipOutSurf(s2);
    D_Delay(2000);

    int i = 0;
    while(i < 100){

        D_FillRect(s2, D_NULL, D_rgbaToFormat(s2->format, 200, 200, 255, 255));
        D_FillRect(s2, &r, D_rgbaToFormat(s2->format, 255, 200, 200, 255));
        D_FlipOutSurf(s2);

        i++;
        r.x += 10;
        D_Delay(10);
    };

    D_FreeOutSurf(s);
    s = D_NULL;

    s = D_GetOutSurf(10, 10, 500, 400, "Box Test Again");
    r.x = 40;
    D_FillRect(s, D_NULL, D_rgbaToFormat(s->format, 255, 200, 200, 255));
    D_FillRect(s, &r, D_rgbaToFormat(s->format, 200, 255, 200, 255));

    D_FlipOutSurf(s);

    D_Delay(1000);

    D_FreeOutSurf(s);
    s = D_NULL;

    D_FreeOutSurf(s2);
    s2 = D_NULL;

    return 0;
};
