/* This tests alpha blending in the D_CopySurfScaled()
 *  function. When you run it, you can press anywhere
 *  on the sliders to set all the pixels of an image
 *  to a certain alpha number (This does mean the alpha
 *  information that was there gets lost so you lose
 *  the semi transparent blobs, the original file is
 *  unchanged).
 *
 */

#define D_ALLOW_STB_IMAGE
#define D_IMPLEMENTATION
#include"../d.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../stb_image.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"


#define DELAY 1000/15

D_Surf * out = D_NULL;
D_Surf * pic1 = D_NULL;
D_Rect pic1Slider = {570, 10, 10, 256};
D_Surf * pic2 = D_NULL;
D_Rect pic2Slider = {585, 10, 10, 256};
D_Surf * pic3 = D_NULL;
D_Rect pic3Slider = {600, 10, 10, 256};
D_Surf * fin = D_NULL;
D_Rect finSlider = {615, 10, 10, 256};
D_Rect finR = {20, 20, 540, 380};
D_Event e = {D_NULL};
D_Point mouse = {0, 0}; //updated every mousedown
int running = 1;
int finAlpha = 255;

//Only works for surfaces that have a 32 bitdepth (can be easily changed)
//This sets every pixel's alpha to alpha (meaning what was there gets lost)
int setSurfAlpha(D_Surf * s, int alpha){
    if(alpha < 0 || alpha > 255){
        return -1;
    };

    int y = 0;
    int x = 0;
    int r = 0, g = 0, b = 0, a = 0;
    while(y < s->h){
        x = 0;
        while(x < s->w){
            D_FormatTorgba((((D_uint32 *)s->pix)[(y * s->w) + x]), s->format, &r, &g, &b, &a);
            (((D_uint32 *)s->pix)[(y * s->w) + x]) = D_rgbaToFormat(s->format, r, g, b, alpha);
            //printf("New rgba r: %d g: %d b: %d alpha: %d\n", r, g, b, alpha);
            x++;
        };
        y++;
    };
};

int draw(){
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
    D_FillRect(fin, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, finAlpha));
    D_SurfCopyScale(pic1, D_NULL, fin, D_NULL);
    D_SurfCopyScale(pic2, D_NULL, fin, D_NULL);
    D_SurfCopyScale(pic3, D_NULL, fin, D_NULL);
    D_SurfCopyScale(fin, D_NULL, out, &finR);

    D_FillRect(out, &pic1Slider, D_rgbaToFormat(out->format, 200, 190, 190, 255));
    D_FillRect(out, &pic2Slider, D_rgbaToFormat(out->format, 200, 190, 190, 255));
    D_FillRect(out, &pic3Slider, D_rgbaToFormat(out->format, 200, 190, 190, 255));
    D_FillRect(out, &finSlider, D_rgbaToFormat(out->format, 200, 190, 190, 255));

    D_FlipOutSurf(out);
};

//This relies on the sliders having a height of 256
int mouseDown(){
    if(D_PointInRect(&mouse, &pic1Slider)){
        setSurfAlpha(pic1, mouse.y - pic1Slider.y);
        printf("pic1Slicder pressed\n");
    };
    if(D_PointInRect(&mouse, &pic2Slider)){
        setSurfAlpha(pic2, mouse.y - pic2Slider.y);
        printf("pic2Slicder pressed\n");
    };
    if(D_PointInRect(&mouse, &pic3Slider)){
        setSurfAlpha(pic3, mouse.y - pic3Slider.y);
        printf("pic3Slicder pressed\n");
    };
    if(D_PointInRect(&mouse, &finSlider)){
        //setSurfAlpha(fin, mouse.y - finSlider.y);
        finAlpha = mouse.y - finSlider.y;
        printf("finSlicder pressed\n");
    };
    return 0;
};

int main(){
    out = D_GetOutSurf(50, 50, 640, 480, "Scale Test With Normal Blending", 0);
    fin = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
    pic1 = D_LoadImage("img/sta.png");
    pic2 = D_LoadImage("img/door.jpeg");
    pic3 = D_LoadImage("img/ye.png");

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) != -1){
            switch(e.type){
                case D_MOUSEDOWN:
                    mouse.x = e.mouse.x;
                    mouse.y = e.mouse.y;
                    mouseDown();
                    break;
                case D_QUIT:
                    running = 0;
                    break;
            };

        };

        draw();

        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeSurf(pic1);
    pic1 = D_NULL;
    D_FreeSurf(pic2);
    pic2 = D_NULL;
    D_FreeSurf(pic3);
    pic2 = D_NULL;
    D_FreeSurf(fin);
    fin = D_NULL;

    D_FreeOutSurf(out);
    out = D_NULL;
};
