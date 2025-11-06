#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#define DELAY 1000/30

/* This test is to make sure that
 *  D_SurfCopyScale() doesn't read or write
 *  outside of the safe area on any subsurface.
 *
 * If you run the test, you should see a green
 *  rectangle (which is a subsurface) cover the
 *  entire window except for a 1 pixel, black
 *  boarder. In the green rectangle you should
 *  see a part of an image, the image gets loaded
 *  and a subsurface is created on part of it
 *  (covering the yellow windows) then part of
 *  that is copied onto the green subsurface. You
 *  can use the arrow keys to move what part of
 *  the image subsurface gets copied. If you see
 *  red, that shows that D_SurfCopyScale() is not
 *  copying data it shouldn't (data which is
 *  outside imageInner->safeArea).
 *
 * You can also move the mouse which moves the
 *  image. It should only draw on the green
 *  subsurface (the black 1 pixel boarder should
 *  never get drawn over).
 */

int main(int argc, char ** argv){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Subsurface scale copy test", 0);

    D_Rect where = {1, 1, 638, 478};
    D_Surf * inner = D_CreateSubsurf(out, &where);

    D_Surf * image = D_LoadImage("img/door.jpeg");

    D_Rect imageRect = {0, 0, 256, 144};

    D_Rect imageWhere = {371, 203, 519, 344};
    D_Surf * imageInner = D_CreateSubsurf(image, &imageWhere);

    D_Rect imageRect2 = {0, 0, 200, 150};


    int running = 1;
    D_Event e = {0};

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) >= 0){
            switch(e.type){
                case D_QUIT:
                    running = 0;
                    break;

                case D_MOUSEMOVE:
                    imageRect.x = e.mouse.x - (imageRect.w / 2);
                    imageRect.y = e.mouse.y - (imageRect.h / 2);
                    break;

                case D_KEYDOWN:
                    switch(e.keyboard.key){
                        case D_KLeft:
                            imageRect2.x = imageRect2.x - 10;
                            break;
                        case D_KRight:
                            imageRect2.x = imageRect2.x + 10;
                            break;
                        case D_KUp:
                            imageRect2.y = imageRect2.y - 10;
                            break;
                        case D_KDown:
                            imageRect2.y = imageRect2.y + 10;
                            break;
                    };
                    break;
            };
        };

        D_FillRect(inner, D_NULL, D_rgbaToFormat(inner->format, 0, 255, 0, 255));


        D_FillRect(inner, &imageRect, D_rgbaToFormat(inner->format, 255, 0, 0, 255));
        D_SurfCopyScale(imageInner, &imageRect2, inner, &imageRect);

        D_FlipOutSurf(out);

        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeSurf(inner);
    inner = D_NULL;

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
