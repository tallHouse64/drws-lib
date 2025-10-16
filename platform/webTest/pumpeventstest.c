#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#include"../../dplatform.h"
#include"../webd.h"

#define DELAY 1000/60


/* WARNING: This test has flashing lights.
 *
 * This file tests the D_PumpEvents() function.
 */

/* This function prints keys */
int printSpecialKey(D_Key k){
    switch(k){

        case D_KLeft:  EM_ASM({console.log("Left");});  break;
        case D_KRight: EM_ASM({console.log("Right");}); break;
        case D_KUp:    EM_ASM({console.log("Up");});    break;
        case D_KDown:  EM_ASM({console.log("Down");});  break;

        default:
            EM_ASM({console.log("Unknown");});
            break;
    };

    return 0;
};

int main(int argc, char ** argv){
    D_Surf * out = D_GetOutSurf(0, 0, 640, 480, "D_PumpEvents() test", 0);
    int running = 1;
    int state = 0; /*1: draw white, 0: draw black*/
    D_Event e = {0};

    D_StartEvents();

    EM_ASM({console.log("Running");});

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) >= 0){
            switch(e.type){

                case D_MOUSEMOVE:
                    EM_ASM({console.log("Mouse move!");});
                    break;
                case D_MOUSEDOWN:
                    EM_ASM({console.log("Mouse down!");});
                    break;
                case D_MOUSEUP:
                    EM_ASM({console.log("Mouse up!");});
                    break;

                case D_KEYDOWN:
                    if(D_DKeyToChar(e.keyboard.key) != '\0'){
                        EM_ASM({console.log("Key down! " + String.fromCharCode($0));}, D_DKeyToChar(e.keyboard.key));
                    }else{
                        EM_ASM({console.log("Key down:");});
                        printSpecialKey(e.keyboard.key);
                    };
                    break;


                case D_KEYUP:
                    if(D_DKeyToChar(e.keyboard.key) != '\0'){
                        EM_ASM({console.log("Key up! " + String.fromCharCode($0));}, D_DKeyToChar(e.keyboard.key));
                    }else{
                        EM_ASM({console.log("Key up:");});
                        printSpecialKey(e.keyboard.key);
                    };
                    break;

                default:
                    break;
            };
        };

        if(state){
            D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 255, 255, 255, 255));
        }else{
            D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));
        };

        D_FlipOutSurf(out);

        state = !state;
        emscripten_sleep(DELAY);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;
    return 0;
};
