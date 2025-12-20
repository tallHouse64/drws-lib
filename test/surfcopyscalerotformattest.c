#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define D_IMPLEMENTATION
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include "../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#define DELAY 1000/30

/* This file tests the D_SurfCopyScaleRot()
 *  function and weather it can copy between
 *  surfaces with different bit depths/pixel
 *  formats.
 *
 * Running the test, you should see 9 images that
 *  rotate with mouse movement.
 *
 * The left-most column are images copied to a
 *  target surface with a bit depth of 32.
 *
 * The middle column are images copied to a
 *  surface with a bit depth of 16.
 *
 * The right most column are images copied to a
 *  surface with a bit depth of 8.
 *
 *
 * The top row of images have a source bit depth
 *  of 32.
 *
 * The top middle of images have a source bit
 *  depth of 16.
 *
 * The top bottom of images have a source bit
 *  depth of 8.
 *
 *
 * This way each combination of bit depths are
 *  tested.
 *
 * You can also press any key to change the blend
 *  mode of all the images.
 */

int main(int argc, char ** argv){
    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "D_SurfCopyScaleRot() Format Test", 0);

    D_Rect targetResetRect = {0, 0, out->w / 3, out->h};
    D_Rect targetRect = targetResetRect;

    D_Surf * target32 = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));

    D_Surf * target16 = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));

    D_Surf * target8 = D_CreateSurf(out->w / 3, out->h, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0x00, 8));


    D_Surf * img = D_LoadImage("img/folder.png");

    D_Surf * img16 = D_CreateSurf(img->w, img->h, D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16));
    D_SurfCopyScale(img, D_NULL, img16, D_NULL);

    D_Surf * img8 = D_CreateSurf(img->w, img->h, D_FindPixFormat(0xFF, 0xFF, 0xFF, 0x00, 8));
    D_SurfCopyScale(img, D_NULL, img8, D_NULL);

    int running = 1;
    D_Event e = {0};
    D_Rect resetRect = {30, 70, 153, 86};
    D_Rect rect = resetRect;
    D_Point cen = {76, 43};
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

                    /* Hackey way to cycle
                     *  through blend modes,
                     *  (this is just a test).*/

                    img->blendMode += 1;
                    if(img->blendMode > D_BLENDMODE_DIVIDE){
                        img->blendMode = D_BLENDMODE_NONE;
                    };

                    img16->blendMode = img->blendMode;
                    img8->blendMode = img->blendMode;

                    break;
            };
        };

        /*angle += 0.01;*/


        rect = resetRect;
        targetRect = targetResetRect;

        /* Draw the left-most column. */
        D_FillRect(target32, D_NULL, D_rgbaToFormat(target32->format, 20, 50, 50, 255));
        D_FillRect(target32, &rect, D_rgbaToFormat(target32->format, 70, 70, 90, 255));

        D_SurfCopyScaleRot(img, D_NULL, target32, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img16, D_NULL, target32, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img8, D_NULL, target32, &rect, &cen, angle);

        D_SurfCopyScale(target32, D_NULL, out, &targetRect);



        /* Draw the middle column. */
        rect = resetRect;

        D_FillRect(target16, D_NULL, D_rgbaToFormat(target16->format, 50, 20, 50, 255));
        D_FillRect(target16, &rect, D_rgbaToFormat(target16->format, 70, 70, 90, 255));

        D_SurfCopyScaleRot(img, D_NULL, target16, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img16, D_NULL, target16, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img8, D_NULL, target16, &rect, &cen, angle);

        targetRect.x += out->w / 3;
        D_SurfCopyScale(target16, D_NULL, out, &targetRect);



        /* Draw the right-most column. */
        rect = resetRect;

        D_FillRect(target8, D_NULL, D_rgbaToFormat(target8->format, 50, 50, 20, 255));
        D_FillRect(target8, &rect, D_rgbaToFormat(target8->format, 70, 70, 90, 255));

        D_SurfCopyScaleRot(img, D_NULL, target8, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img16, D_NULL, target8, &rect, &cen, angle);

        rect.y += rect.h + 50;
        D_SurfCopyScaleRot(img8, D_NULL, target8, &rect, &cen, angle);

        targetRect.x += out->w / 3;
        D_SurfCopyScale(target8, D_NULL, out, &targetRect);


        D_FlipOutSurf(out);

        D_Delay(DELAY);
    };

    D_StopEvents();
    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
