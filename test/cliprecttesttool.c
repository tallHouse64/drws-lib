#define D_ALLOW_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#define D_IMPLEMENTATION
#include"../d.h"
#undef D_ALLOW_STB_IMAGE
#undef STB_IMAGE_IMPLEMENTATION
#undef D_IMPLEMENTATION

#include"../platform/sdld.h"


#define DELAY 1000/15

D_Surf * out = D_NULL;
D_Event e = {0};
D_Point mouse = {0};
D_Rect outer = {150, 150, 100, 100};
D_Rect inner = {0};
int running = 1;

int drawRectCorners(D_Surf * s, D_Rect * r, D_uint32 col){
    D_Rect cor = {0, 0, 10, 10};

    //Draw top left
    cor.x = r->x - 5;
    cor.y = r->y - 5;
    D_FillRect(s, &cor, col);

    //Draw top right
    cor.x = (r->x + r->w) - 5;
    cor.y = r->y - 5;
    D_FillRect(s, &cor, col);

    //Draw bottom left
    cor.x = r->x - 5;
    cor.y = (r->y + r->h) - 5;
    D_FillRect(s, &cor, col);

    //Draw bottom right
    cor.x = (r->x + r->w) - 5;
    cor.y = (r->y + r->h) - 5;
    D_FillRect(s, &cor, col);

    return 0;
};

int draw(){

    //Fill out with black
    D_FillRect(out, D_NULL, D_rgbaToFormat(out->format, 0, 0, 0, 255));

    //Draw outer
    drawRectCorners(out, &outer, D_rgbaToFormat(out->format, 255, 200, 200, 255));
    D_FillRect(out, &outer, D_rgbaToFormat(out->format, 30, 30, 30, 255));

    //Draw inner
    D_FillRect(out, &inner, D_rgbaToFormat(out->format, 200, 255, 200, 255));


    D_FlipOutSurf(out);
};

int main(){
    out = D_GetOutSurf(50, 50, 640, 480, "D_ClipRect() test tool");

    D_StartEvents();

    while(running){
        D_PumpEvents();

        while(D_GetEvent(&e) != -1){
            switch(e.type){
                case D_MOUSEMOVE:
                    mouse.x = e.mouse.x;
                    mouse.y = e.mouse.y;
                    break;
                case D_QUIT:
                    running = 0;
                    break;
            };

        };

        inner.x = mouse.x;
        inner.y = mouse.y;
        inner.w = 130;
        inner.h = 130;

        D_ClipRect(outer.x, outer.y, outer.w, outer.h, &inner);

        printf("inner rect\nx: %d\ny: %d\nw: %d\nh: %d\n\n", inner.x, inner.y, inner.w, inner.h);

        draw();

        D_Delay(DELAY);
    };

    D_StopEvents();

    D_FreeOutSurf(out);
    out = D_NULL;
};
