#include"../d.h"

#ifndef DPLATFORM_H
#define DPLATFORM_H

D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title);
int D_FreeOutSurf(D_Surf * s);
int D_FlipOutSurf(D_Surf * s);
int D_PumpEvents();
int D_Delay(int ms);

#endif
