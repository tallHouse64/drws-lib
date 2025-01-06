#define D_IMPLEMENTATION
#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include"../d.h"
#undef D_IMPLEMENTATION
#undef D_ALLOW_STB_IMAGE
#undef STB_IMAGE_IMPLEMENTATION

#include"../platform/sdld.h"

D_Surf * out = D_NULL;
D_Surf * img = D_NULL;
D_Rect r = {0, 0, 630, 360};
D_Rect r2 = {400, 70, 200, 100};

int main(){
    img = D_LoadImage("img/scale.png");
    out = D_GetOutSurf(50, 50, 640, 480, "D_SurfCopyScale() test 2");

    //Scale up part of s1 test
    D_SurfCopyScale(img, &r, out, D_NULL);
    D_FlipOutSurf(out);
    D_Delay(3000);

    //Scale down part of s1 test
    r.x = 866;
    r.y = 400;
    r.w = 960;
    r.h = 540;
    D_SurfCopyScale(img, &r, out, &r2);
    D_FlipOutSurf(out);
    D_Delay(3000);

    //Massive scale up of part of s1 test
    r.x = 1239;
    r.y = 633;
    r.w = 38;
    r.h = 34;
    D_SurfCopyScale(img, &r, out, D_NULL);
    D_FlipOutSurf(out);
    D_Delay(3000);

    D_FreeSurf(img);
    img = D_NULL;

    D_FreeOutSurf(out);
    out = D_NULL;
};
