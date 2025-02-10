#include<SDL2/SDL.h>

#define D_IMPLEMENTATION
#define D_ALLOW_STB_IMAGE
#include"../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../platform/sdld.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../stb_image.h"

D_Surf * out = D_NULL;
D_Surf * img = D_NULL;

int main(){
    img = D_LoadImage("img/folder.png");
    printf("Loaded\n");

    out = D_GetOutSurf(50, 50, 640, 480, "Testing D_LoadImage()", 0);

    D_SurfCopyScale(img, D_NULL, out, D_NULL);

    D_FlipOutSurf(out);

    D_Delay(3000);

    D_FreeSurf(img);
    img = D_NULL;

    return 0;
};
