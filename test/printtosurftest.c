#define D_IMPLEMENTATION
#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include"../d.h"
#undef D_IMPLEMENTATION
#undef D_ALLOW_STB_IMAGE
#undef STB_IMAGE_IMPLEMENTATION

#include"../platform/sdld.h"

D_Surf * out = D_NULL;
D_Surf * font = D_NULL;
D_Point p = {10, 40};

int main(){
    out = D_GetOutSurf(50, 50, 640, 480, "D_PrintToSurf() Test");
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 255, 255, 255, 255));

    font = D_LoadImage("img/font.png");

    D_PrintToSurf(out, font, &p, 20, "HELLO It Works");

    D_FlipOutSurf(out);

    D_Delay(5000);


    D_FreeOutSurf(out);
    out = D_NULL;
};