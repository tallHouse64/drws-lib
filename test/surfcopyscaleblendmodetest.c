#define D_ALLOW_STB_IMAGE
#define D_IMPLEMENTATION
#include"../d.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../stb_image.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

D_Surf * out = D_NULL;
D_Surf * img1 = D_NULL;
//D_Surf * img2 = D_NULL;
D_Surf * font = D_NULL;
D_Rect r = {10, 10, 192, 108};
D_Point p = {0, 0};

int main(){
    out = D_GetOutSurf(50, 50, 640, 480, "Testing blendmodes in D_SurfCopyScale()", 0);
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

    img1 = D_LoadImage("img/ye2.png");
    //img2 = D_LoadImage("img/sta.png");
    font = D_LoadImage("img/fontwhite.png");

    //Move point
    p.x = r.x + r.w + 15;
    p.y = (r.y + (r.h / 2)) - 15;

    img1->blendMode = D_BLENDMODE_NONE;
    D_SurfCopyScale(img1, D_NULL, out, &r);
    D_PrintToSurf(out, font, &p, 30, -10, "No blending");



    r.y = r.y + r.h + 5; //Move rect down

    //Move point
    p.x = r.x + r.w + 15;
    p.y = (r.y + (r.h / 2)) - 15;

    img1->blendMode = D_BLENDMODE_NORMAL;
    D_SurfCopyScale(img1, D_NULL, out, &r);
    D_PrintToSurf(out, font, &p, 30, -10, "Normal blending");


    D_FlipOutSurf(out);
    D_Delay(30000);


    D_FreeOutSurf(out);
    out = D_NULL;
};
