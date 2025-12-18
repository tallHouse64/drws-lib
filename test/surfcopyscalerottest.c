#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#define DELAY 1000/30


int main(int argc, char ** argv){
    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "D_SurfCopyScaleRot() Test", 0);
    D_Surf * img = D_LoadImage("img/folder.png");
    int running = 1;
    D_Event e = {0};
    D_Rect rect = {140, 70, 153, 86};
    D_Point cen = {30, 43};
    D_double angle = -10;
    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) != -1){
            switch(e.type){
                case D_QUIT:
                    running = 0;
                    break;
                case D_MOUSEMOVE:
                    angle = e.mouse.x - 180;
                    break;
            };
        };

        /*angle += 0.01;*/


        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        D_FillRect(out, &rect, D_rgbaToFormat(out->format, 70, 70, 90, 255));
        D_SurfCopyScaleRot(img, D_NULL, out, &rect, &cen, angle);
        D_FlipOutSurf(out);

        D_Delay(DELAY);
    };

    D_StopEvents();
    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
