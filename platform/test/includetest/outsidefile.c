#include"../../dplatform.h"
#include"../../dplatform.h"
#include"../../dplatform.h"


int func(D_Surf * s){
    D_Rect r = {10, 10, 100, 50};

    D_FillRect(s, &r, D_rgbaToFormat(s->format, 155, 145, 145, 255));

    D_Surf * t = D_GetOutSurf(100, 100, 144, 120, "Test window from outsidefile");
    D_Delay(1000);

    D_FreeOutSurf(t);
    t = D_NULL;


    return 0;
};
