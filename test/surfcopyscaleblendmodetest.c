#define D_ALLOW_STB_IMAGE
#define D_IMPLEMENTATION
#include"../d.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../stb_image.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

/* This tests the blendmodes using
 *  D_SurfCopyScale().
 *
 * This test has a screenshot on the drws-lib
 *  front page to show the blendmodes drws-lib
 *  supports.
 */

D_Surf * out = D_NULL;
D_Surf * img1 = D_NULL;
D_Surf * img2 = D_NULL;
D_Surf * font = D_NULL;
D_Rect r = {10, 10, 192, 108};
D_Point p = {0, 0};

int test(D_BLENDMODE blend, char * s){

    D_SurfCopyScale(img2, D_NULL, out, &r);

    img1->blendMode = blend;
    D_SurfCopyScale(img1, D_NULL, out, &r);

    if(blend == D_BLENDMODE_MULTIPLY){
        D_PrintToSurf(out, font, &p, 30, -12, s);
    }else{
        D_PrintToSurf(out, font, &p, 30, -10, s);
    };

    r.y = r.y + r.h + 5; //Move rect down

    //Move point so it's next to the rect
    p.x = r.x + r.w + 15;
    p.y = (r.y + (r.h / 2)) - 15;

};

int resetTest(){
    D_FlipOutSurf(out);
    D_Delay(10000);

    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

    r.y = 10;

    //Move point so it's next to the rect
    p.x = r.x + r.w + 15;
    p.y = (r.y + (r.h / 2)) - 15;
};

int main(int argc, char ** argv){
    out = D_GetOutSurf(50, 50, 640, 480, "Testing blendmodes in D_SurfCopyScale()", 0);
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

    img1 = D_LoadImage("img/blendTestFront.png");
    img2 = D_LoadImage(argc >= 2 ? argv[1] : "img/blendTestBack.png");
    font = D_LoadImage("img/fontWhite.png");

    //Move point so it is next to the rect
    p.x = r.x + r.w + 15;
    p.y = (r.y + (r.h / 2)) - 15;


    test(D_BLENDMODE_NONE, "No blending");
    test(D_BLENDMODE_NORMAL, "Normal blending");
    test(D_BLENDMODE_ADD, "Additive blending");
    test(D_BLENDMODE_MULTIPLY, "Multiplication blending");
    resetTest();


    test(D_BLENDMODE_SUBTRACT, "Subtration blending");
    test(D_BLENDMODE_DIVIDE, "Division blending");
    resetTest();


    D_FreeOutSurf(out);
    out = D_NULL;
};
