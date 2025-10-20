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

/* This function prints special keys that
 *  D_DKeyToChar() returns null for, like
 *  CapsLock or Ctrl.*/
int printSpecialKey(D_Key k){
    switch(k){

        case D_KLeft:  EM_ASM({console.log("Left");});  break;
        case D_KRight: EM_ASM({console.log("Right");}); break;
        case D_KUp:    EM_ASM({console.log("Up");});    break;
        case D_KDown:  EM_ASM({console.log("Down");});  break;

        case D_KEscape:   EM_ASM({console.log("Escape");});   break;
        case D_KTab:      EM_ASM({console.log("Tab");});      break;
        case D_KCapLock:  EM_ASM({console.log("CapLock");});  break;
        case D_KLeftShift:EM_ASM({console.log("LeftShift");});break;
        case D_KLeftCtrl: EM_ASM({console.log("LeftCtrl");}); break;
        case D_KLeftSuper:EM_ASM({console.log("LeftSuper");});break;
        case D_KAlt:      EM_ASM({console.log("Alt");});      break;
        case D_KAltGr:    EM_ASM({console.log("AltGr");});    break;
        case D_KRightSuper:EM_ASM({console.log("RightSuper");});break;
        case D_KContextMenu:EM_ASM({console.log("ContextMenu");});break;
        case D_KRightCtrl:EM_ASM({console.log("RightCtrl");});break;
        case D_KRightShift:EM_ASM({console.log("RightShift");});break;
        case D_KEnter:    EM_ASM({console.log("Enter");});    break;
        case D_KBackspace:EM_ASM({console.log("Backspace");});break;

        case D_KF1:  EM_ASM({console.log("F1")});  break;
        case D_KF2:  EM_ASM({console.log("F2")});  break;
        case D_KF3:  EM_ASM({console.log("F3")});  break;
        case D_KF4:  EM_ASM({console.log("F4")});  break;
        case D_KF5:  EM_ASM({console.log("F5")});  break;
        case D_KF6:  EM_ASM({console.log("F6")});  break;
        case D_KF7:  EM_ASM({console.log("F7")});  break;
        case D_KF8:  EM_ASM({console.log("F8")});  break;
        case D_KF9:  EM_ASM({console.log("F9")});  break;
        case D_KF10: EM_ASM({console.log("F10")}); break;
        case D_KF11: EM_ASM({console.log("F11")}); break;
        case D_KF12: EM_ASM({console.log("F12")}); break;

        case D_KPrintScreen:EM_ASM({console.log("PrintScreen")});break;
        case D_KScrollLock: EM_ASM({console.log("ScrollLock")}); break;
        case D_KPause:      EM_ASM({console.log("Pause")});      break;

        case D_KInsert:    EM_ASM({console.log("Insert")}); break;
        case D_KHome:      EM_ASM({console.log("Home")});   break;
        case D_KPageUp:    EM_ASM({console.log("PageUp")}); break;
        case D_KDelete:    EM_ASM({console.log("Delete")}); break;
        case D_KEnd:       EM_ASM({console.log("End")});    break;
        case D_KPageDown:  EM_ASM({console.log("PageDown")});break;


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
