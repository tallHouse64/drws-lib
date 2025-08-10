#include<nds.h>
#include"../d.h"
#include"../devents.h"

#define D_NDS_SCREENS 2
#define D_NDS_FORMAT D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16)

int D_D_UsedOutSurfs[D_NDS_SCREENS] = {0, 0}; //Use as bool
D_uint32 D_D_LastKeysHeld = 0; //Keys held from last D_PumpEvents() call
touchPosition D_D_LastTouch = {0}; //Touch from last D_PumpEvents() call

/* This function gets a surface that is used to
 *  read/write directly to the NDS vram, it can
 *  be used to draw to the bottom screen. Call
 *  D_FlipOutSurf() after drawing to show it on
 *  screen.
 *
 * This implementation of D_GetOutSurf() ignores
 *  all it's parameters, it will only return a
 *  surface with a width of 256 and height of
 *  192.
 *
 * This function uses double buffering.
 *
 * x: The x coordinate of where the surface would
 *  appear on screen (ignored).
 * y: The y coordinate of where the surface would
 *  appear on screen (ignored).
 * w: The width of the surface (ignored, 256 used
 *  instead).
 * h: The height of the surface (ignored, 192
 *  used instead).
 * title: A title that would be used for the
 *  window if there was one (ignored).
 * flags: Unused, may be used in the future
 *  (ignored). D_OUTSURFFULLSCREEN used instead.
 * returns: An output surface.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){


    //Make the surface use the backbuffer of
    // the top screen (VRAM_A, frontbuffer is VRAM_B)
    if(!D_D_UsedOutSurfs[0]){
        videoSetMode(MODE_FB1);
        vramSetBankA(VRAM_A_LCD);
        vramSetBankB(VRAM_B_LCD);

        lcdMainOnBottom();

        D_Surf * s1 = D_CreateSurfFrom(SCREEN_WIDTH, SCREEN_HEIGHT, D_NDS_FORMAT, VRAM_A);

        if(s1 == D_NULL){
            return D_NULL;
        };

        s1->outId = 0;
        s1->flags = D_OUTSURFFULLSCREEN;

        D_D_UsedOutSurfs[0] = 1;
        return s1;
    };

    return D_NULL;
};

/* This function frees an out surf created by
 *  (returned by) D_GetOutSurf().
 *
 * s: The surface to free.
 * returns: 0 on success.
 */
int D_FreeOutSurf(D_Surf * s){
    if(s->outId == 0){

        D_D_UsedOutSurfs[0] = 0;
        D_FreeSurf(s);
        s = D_NULL;

    }else if(s->outId == 1){

        D_D_UsedOutSurfs[1] = 0;
        D_FreeSurf(s);
        s = D_NULL;

    }else {
        return -1;
    };

    return 0;
};


/* This function shows onscreen what has been
 *  drawn to a backbuffer surface, it also
 *  changes the surface to so that it's pixel
 *  data pointer points to another backbuffer
 *  (which was onscreen).
 *
 * Only pass in a surface that was returned by
 *  D_GetOutSurf().
 *
 * s: The surface to show on screen.
 */
int D_FlipOutSurf(D_Surf * s){
    if(s->outId == 0){
        if(s->pix == VRAM_A){
            //Change which bufer is on display (the new front buffer)
            videoSetMode(MODE_FB0); //We were just drawing to VRAM_A, now show it.

            //Change the surface to the new back buffer.
            s->pix = VRAM_B; //Start drawing to VRAM_B.
        }else if(s->pix == VRAM_B){
            videoSetMode(MODE_FB1); //We drew to VRAM_B, now show it.

            s->pix = VRAM_A; //Now draw to VRAM_A.
        };
    };
};

/* This function fills the event queue with
 *  events that happened since the last call to
 *  D_PumpEvents().
 *
 * This function uses the D_CauseEvent() function
 *  to add events to the queue according to the
 *  input on the ds.
 */
int D_PumpEvents(){
    D_Event e;

    scanKeys();
    D_uint32 held = keysHeld();
    touchPosition touch = {0};
    touchRead(&touch);


    //Handle touch events

    if((held & KEY_TOUCH) && !(D_D_LastKeysHeld & KEY_TOUCH)){

        //Touch just started (like mousedown)
        e.mouse.x = touch.px;
        e.mouse.y = touch.py;
        e.type = D_MOUSEDOWN;
        D_CauseEvent(&e);

    }else if((held & KEY_TOUCH) && (D_D_LastKeysHeld & KEY_TOUCH) && (touch.px != D_D_LastTouch.px && touch.py != D_D_LastTouch.py)){

        //Touch moved
        e.mouse.x = touch.px;
        e.mouse.y = touch.py;
        e.type = D_MOUSEMOVE;
        D_CauseEvent(&e);

    }else if(!(held & KEY_TOUCH) && (D_D_LastKeysHeld & KEY_TOUCH)){

        //Touch end (like mouseup)
        e.mouse.x = D_D_LastTouch.px;
        e.mouse.y = D_D_LastTouch.py;
        e.type = D_MOUSEUP;
        D_CauseEvent(&e);

    };


    D_D_LastTouch = touch;
    D_D_LastKeysHeld = held;
};

void D_D_DoNothing(void){
    return;
};

#define D_D_TIMERSPEED (BUS_CLOCK/1024)
#define D_D_TIMER 0

/* This function waits "ms" milliseconds. It
 *  stops code running for that amount of time
 *  (it's a blocking function).
 *
 * 1000 milliseconds is 1 second.
 *
 * ms: The number of milliseconds to wait.
 * returns: 0 on success.
 */
int D_Delay(int ms){
    irqEnable(IRQ_TIMER(D_D_TIMER));
    timerStart(D_D_TIMER, ClockDivider_1024, 65535 - ((D_D_TIMERSPEED * ms) / 1000), D_D_DoNothing);
    swiIntrWait(1, IRQ_TIMER(D_D_TIMER));
    timerStop(D_D_TIMER);
    return 0;
};
