#include"../../../dplatform.h"
#include"../../../dplatform.h"
#include"../../../dplatform.h"
#include"../../../dplatform.h"

#include"../../sdld.h"
#include"../../sdld.h"
#include"../../sdld.h"
#include"../../sdld.h"
#define D_PLATFORM_IMPLEMENTATION
#include"../../sdld.h"
#include"../../sdld.h"
#include"../../sdld.h"

#define D_IMPLEMENTATION
#include"../../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../../devents.h"

#include"outsidefile.h"

#include<stdio.h>

int main(){

    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Include test for platform", 0);

    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 255, 170, 120, 255));
    func(out);
    D_FlipOutSurf(out);

    D_Delay(3000);

    D_FreeOutSurf(out);
    out = D_NULL;

    printf("Works.\n");
};
