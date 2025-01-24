#include"../d.h"

#ifndef DPLATFORM_H
#define DPLATFORM_H

typedef enum D_OutSurfFlags {
    D_OUTSURFRESIZABLE = 0x01
} D_OutSurfFlags;

D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title);
int D_FreeOutSurf(D_Surf * s);
int D_FlipOutSurf(D_Surf * s);
int D_PumpEvents();
int D_Delay(int ms);

#endif
