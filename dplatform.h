#include"d.h"

#ifndef DPLATFORM_H
#define DPLATFORM_H

D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags);
D_Surf * D_GetResizedOutSurf(D_Surf * s);
D_Surf * D_OutIdToOutSurf(int outId);
int D_FreeOutSurf(D_Surf * s);
int D_FlipOutSurf(D_Surf * s);
int D_PumpEvents();
int D_Delay(int ms);

#endif
