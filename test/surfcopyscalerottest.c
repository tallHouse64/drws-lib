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

    D_Rect subR = {10, 10, 620, 460};
    D_Surf * sub = D_CreateSubsurf(out, &subR);

    D_Surf * img = D_LoadImage("img/folder.png");
    D_Rect imgR = {0, 0, img->w, img->h};

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

                case D_KEYDOWN:

                    if(e.keyboard.key == D_Kw){
                        rect.y = rect.y - 10;
                    }else if(e.keyboard.key == D_Ks){
                        rect.y = rect.y + 10;
                    }else if(e.keyboard.key == D_Ka){
                        rect.x = rect.x - 10;
                    }else if(e.keyboard.key == D_Kd){
                        rect.x = rect.x + 10;

                    }else if(e.keyboard.key == D_Ki){
                        imgR.h = imgR.h + 10;
                    }else if(e.keyboard.key == D_Ko){
                        imgR.h = imgR.h - 10;
                    }else if(e.keyboard.key == D_Kk){
                        imgR.y = imgR.y + 10;
                    }else if(e.keyboard.key == D_Kl){
                        imgR.y = imgR.y - 10;

                    }else if(e.keyboard.key == D_Kp){
                        imgR.w = imgR.w + 10;
                    }else if(e.keyboard.key == D_KLeftBracket){
                        imgR.w = imgR.w - 10;
                    }else if(e.keyboard.key == D_KSemicolon){
                        imgR.x = imgR.x + 10;
                    }else if(e.keyboard.key == D_KQuote){
                        imgR.x = imgR.x - 10;
                    };

                    break;
            };
        };

        /*angle += 0.01;*/


        D_FillRect(sub, D_NULL, D_rgbaToFormat(out->format, 50, 50, 50, 255));
        D_FillRect(sub, &rect, D_rgbaToFormat(out->format, 70, 70, 90, 255));
        D_SurfCopyScaleRot(img, &imgR, sub, &rect, &cen, angle);

        D_FlipOutSurf(out);

        D_Delay(DELAY);
    };

    D_StopEvents();
    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
