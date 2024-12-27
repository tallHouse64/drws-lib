#include"../tod.h"

int main(){
    D_Surf * out = D_GetOutSurf(10, 10, 640, 480, "Hello");

    D_FreeOutSurf(out);
};
