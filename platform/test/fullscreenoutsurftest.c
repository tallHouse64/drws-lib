#define D_IMPLEMENTATION
#include"../../d.h"

#define DEVENTS_IMPLEMENTATION
#include"../../devents.h"

#define D_PLATFORM_IMPLEMENTATION
#include"../sdld.h"


/*This tests if an outsurf can be fullscreen.
 * Click to close when running the test.
 */

int main(){
    D_Surf * out = D_GetOutSurf(50, 50, 640, 480, "Fullscreen outSurf test", D_OUTSURFFULLSCREEN);
    D_Event e;
    int running = 1;

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) == 0){
            if(e.type == D_QUIT || e.type == D_MOUSEDOWN){
                running = 0;
            };
        };

        D_Delay(100);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;
};
