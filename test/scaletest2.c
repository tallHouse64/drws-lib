#define D_IMPLEMENTATION
#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

/* This test is to make sure D_SurfCopyScale()
 *  can copy part of a source surface (not using
 *  null for r1) and that it can scale up and
 *  down.
 */

D_Surf * out = D_NULL;
D_Surf * img = D_NULL;
D_Rect r = {0, 0, 630, 360};
D_Rect r2 = {400, 70, 200, 100};

int main(){
    img = D_LoadImage("img/scale.png");
    out = D_GetOutSurf(50, 50, 640, 480, "D_SurfCopyScale() test 2", 0);

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
