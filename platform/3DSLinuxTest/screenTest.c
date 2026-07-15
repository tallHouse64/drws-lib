#define D_PLATFORM_IMPLEMENTATION
#include"../3dslinuxd.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_IMPLEMENTATION
#include"../../d.h"

#include"../../dplatform.h"

/* This test fades the screen from blue to
 * purple, then it waits 3 seconds and quits.
 */

int main(){
    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Hello", 0);

    int i = 0;

    while(i < 255){
        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, i, 0, 255, 255));
        D_FlipOutSurf(out);
        D_Delay(10);

        i++;
    };

    D_Delay(3000);

    D_FreeOutSurf(out);
    out = D_NULL;

    return 0;
};
