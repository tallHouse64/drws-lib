#include<nds.h>
#include"../d.h"
#include"devents.h"

#define NDS_SCREENS 2
#define NDS_FORMAT D_FindPixFormat(0x001F, 0x03E0, 0x7C00, 0x8000, 16)

int outSurfs[NDS_SCREENS] = {0, 0}; //Use as bool
D_uint32 lastKeysHeld = 0; //Keys held from last D_PumpEvents() call
touchPosition lastTouch = {0}; //Touch from last D_PumpEvents() call


int D_GetOutSurf(int x, int y, int w, int h, char * title){

    int i = 0;
    while(i < NDS_SCREENS && usedOutSurfs[i]){
        i++;
    };

    if(i == NDS_SCREENS){
        //No screens left
        return -1;
    };

    //Make the surface use the backbuffer of
    // the top screen (VRAM_A, frontbuffer is VRAM_B)
    if(numOutSurfs == 0){
        videoSetMode(MODE_FB1);
        vramSetBankA(VRAM_A_LCD);
        vramSetBankB(VRAM_B_LCD);

        D_Surf * s1 = D_CALLOC(1, sizeof(D_Surf));
        s1->pix = VRAM_A;
        s1->w = SCREEN_WIDTH;
        s1->h = SCREEN_HEIGHT;
        s1->outId = 0;
        s1->format = NDS_FORMAT;
    };

    numOutSurfs++;
};

int D_FreeOutSurf(D_Surf * s){
    if(s->outId == 0){
        D_FREE(s);
        s = D_NULL;
    }else if(s->outId == 1){
        D_FREE(s);
        s = D_NULL;
    }else {
        return -1;
    };

    return 0;
};

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

int D_PumpEvents(){
    D_Event e;

    scanKeys();
    D_uint32 held = keysHeld();
    touchPosition touch = {0};
    touchRead(&touch);


    //Handle touch events

    if((held & KEY_TOUCH) && !(lastKeysHeld & KEY_TOUCH)){

        //Touch just started (like mousedown)
        e.mouse.x = touch.x;
        e.mouse.y = touch.y;
        e.type = D_MOUSEDOWN;
        D_CauseEvent(&e);

    }else if((held & KEY_TOUCH) && (lastKeysHeld & KEY_TOUCH) && (touch.x != lastTouch.x && touch.y != lastTouch.y)){

        //Touch moved
        e.mouse.x = touch.x;
        e.mouse.y = touch.y;
        e.type = D_MOUSEMOVE;
        D_CauseEvent(&e);

    }else if(!(held & KEY_TOUCH) && (lastKeysHeld & KEY_TOUCH)){

        //Touch end (like mouseup)
        e.mouse.x = lastTouch.x;
        e.mouse.y = lastTouch.y;
        e.type = D_MOUSEUP;
        D_CauseEvent(&e);

    };


    lastTouch = touch;
    lastKeysHeld = held;
};

void D_D_DoNothing(void){
    return;
};

#define D_D_TIMERSPEED (BUS_CLOCK/1024)
#define D_D_TIMER 0

int D_Delay(int ms){
    irqEnable(IRQ_TIMER(TIMER));
    timerStart(TIMER, ClockDivider_1024, 65535 - ((TIMERSPEED * ms) / 1000), D_D_DoNothing);
    swiIntrWait(1, IRQ_TIMER(TIMER));
    timerStop(TIMER);
    return 0;
};
