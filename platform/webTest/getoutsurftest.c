#define D_IMPLEMENTATION
#include"../../d.h"
#include"../../dplatform.h"
#include"../webd.h"

int main(){
    D_Surf * out = D_GetOutSurf(0, 0, 640, 480, "Test", 0);

    D_FreeOutSurf(out);
    out = D_NULL;
    return 0;
};
