#define D_IMPLEMENTATION
#include"../../d.h"
#include"../../dplatform.h"
#include"../webd.h"

#define DELAY 1000/30

D_Surf * out = D_NULL;

int main(){
    out = D_GetOutSurf(0, 0, 640, 480, "Test", 0);

    EM_ASM({
        console.log("Running");
        console.log("out " + $0 + " pix " + $1);
    }, out, out->pix);

    while(1){
        EM_ASM({console.log("While loop!")});

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 255, 0, 0, 255));
        D_FlipOutSurf(out);
        emscripten_sleep(DELAY);

        D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 255, 255));
        D_FlipOutSurf(out);
        emscripten_sleep(DELAY);
    };



    D_FreeOutSurf(out);
    out = D_NULL;
    return 0;
};
