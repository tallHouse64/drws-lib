#include<SDL2/SDL.h>
#include"../devents.h"
#include"../d.h"
#include"../dplatform.h"

#ifdef D_PLATFORM_IMPLEMENTATION
#ifndef D_PLATFORM_ALREADY_IMPLEMENTED
#define D_PLATFORM_ALREADY_IMPLEMENTED

SDL_Window * sdlw[D_MAX_OUT_SURFS] = {NULL};
SDL_Surface * sdls[D_MAX_OUT_SURFS] = {NULL};

/* This creates a window that can be drawn
 *  to, remember call D_FlipOutSurf() on
 *  it after drawing to show it onto the
 *  screen.
 *
 * Free this surface with D_FreeOutSurf().
 *  It destroys the window.
 *
 * This is called D_GetOutSurf() because it
 *  just gets a surface to output onto. On
 *  Windows, Mac, Linux this would just
 *  make a window but on NDS for example
 *  it doesn't make sence to make a window
 *  this is why it's not called
 *  D_CreateWindow(). Remember the purpose
 *  of this lib is to be as cross platfor
 *  as possible.
 *
 * x: X pos of where the top left of the window should go.
 * y: Y pos of where the top left of the window should go.
 * w: The width of the window.
 * h: The height of the window.
 * title: What the top of the window should say.
 */
D_Surf * D_GetOutSurf(int x, int y, int w, int h, char * title, D_OutSurfFlags flags){

    //Find next unused (NULL) element in sdlw
    int i = 0;
    while(i < D_MAX_OUT_SURFS && sdlw[i] != NULL){
        i++;
    };

    //printf("Found Id: %d\n", i);

    if(i == D_MAX_OUT_SURFS){
        return D_NULL;
    };


    //Translate the flags

    SDL_WindowFlags windowFlags = 0;

    if(flags & D_OUTSURFRESIZABLE){
        windowFlags = windowFlags | SDL_WINDOW_RESIZABLE;
    };

    if(flags & D_OUTSURFFULLSCREEN){
        windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN;
    };


    sdlw[i] = SDL_CreateWindow(title, x, y, w, h, windowFlags);

    sdls[i] = SDL_GetWindowSurface(sdlw[i]);

    D_Surf * s = D_CALLOC(1, sizeof(D_Surf));
    s->pix = sdls[i]->pixels;
    s->w = sdls[i]->w;
    s->h = sdls[i]->h;
    s->outId = i;
    s->blendMode = D_BLENDMODE_NORMAL;
    s->outSurfFlags = flags;

    //From looking at SDL_Pixels.h, because SDL_PixelFormat
    //has a BytesPerPixel it makes me think that all SDL
    //surfaces store pixels like d.h does,only storing
    //pixles in byte sizes.
    //todo: make sure that's true, fix if not.
    s->format = D_FindPixFormat(sdls[i]->format->Rmask, sdls[i]->format->Gmask, sdls[i]->format->Bmask, sdls[i]->format->Amask, sdls[i]->format->BitsPerPixel);
    return s;
};

/* Use this to free the surface created
 *  by D_GetOutSurf(), it destroys it's
 *  window.
 *
 * s: The outSurf to free.
 */
int D_FreeOutSurf(D_Surf * s){

    //Make it safe
    if(s->outId < 0){
        return -1;
    };

    SDL_DestroyWindow(sdlw[s->outId]);
    sdlw[s->outId] = NULL;
    sdls[s->outId] = NULL;
    D_FREE(s);
    s = D_NULL;

    return 0;
};

/* This takes the an outSurf created by
 *  D_GetOutSurf() and shows it onto the
 *  screen.
 *
 * s: The outSurf to free.
 */
int D_FlipOutSurf(D_Surf * s){

    //Make it safe (in case s is a regular surf made by D_CreateSurf())
    if(s->outId < 0){
        return -1;
    };

    SDL_UpdateWindowSurface(sdlw[s->outId]);
    return 0;
};

D_Key D_SDLKToDKey(SDL_KeyCode s){

    switch(s){
        case SDLK_a: return D_Ka;
        case SDLK_b: return D_Kb;
        case SDLK_c: return D_Kc;
        case SDLK_d: return D_Kd;
        case SDLK_e: return D_Ke;
        case SDLK_f: return D_Kf;
        case SDLK_g: return D_Kg;
        case SDLK_h: return D_Kh;
        case SDLK_i: return D_Ki;
        case SDLK_j: return D_Kj;
        case SDLK_k: return D_Kk;
        case SDLK_l: return D_Kl;
        case SDLK_m: return D_Km;
        case SDLK_n: return D_Kn;
        case SDLK_o: return D_Ko;
        case SDLK_p: return D_Kp;
        case SDLK_q: return D_Kq;
        case SDLK_r: return D_Kr;
        case SDLK_s: return D_Ks;
        case SDLK_t: return D_Kt;
        case SDLK_u: return D_Ku;
        case SDLK_v: return D_Kv;
        case SDLK_w: return D_Kw;
        case SDLK_x: return D_Kx;
        case SDLK_y: return D_Ky;
        case SDLK_z: return D_Kz;

        case SDLK_0: return D_K0;
        case SDLK_1: return D_K1;
        case SDLK_2: return D_K2;
        case SDLK_3: return D_K3;
        case SDLK_4: return D_K4;
        case SDLK_5: return D_K5;
        case SDLK_6: return D_K6;
        case SDLK_7: return D_K7;
        case SDLK_8: return D_K8;
        case SDLK_9: return D_K9;

        case SDLK_EXCLAIM: return D_KExclamation;
        case SDLK_QUOTEDBL: return D_KDoubleQuote;
        //case SDLK_POUND: return D_KPound;
        case SDLK_DOLLAR: return D_KDollar;
        case SDLK_PERCENT: return D_KPercentage;
        case SDLK_CARET: return D_KCaret;
        case SDLK_AMPERSAND: return D_KAmpersand;
        case SDLK_ASTERISK: return D_KAsterisk;
        case SDLK_LEFTPAREN: return D_KLeftParentheses;
        case SDLK_RIGHTPAREN: return D_KRightParentheses;

        case SDLK_LEFT: return D_KLeft;
        case SDLK_RIGHT: return D_KRight;
        case SDLK_UP: return D_KUp;
        case SDLK_DOWN: return D_KDown;

        case SDLK_ESCAPE: return D_KEscape;
        case SDLK_BACKQUOTE: return D_KBacktick;
        case SDLK_TAB: return D_KTab;
        case SDLK_CAPSLOCK: return D_KCapLock;
        case SDLK_LSHIFT: return D_KLeftShift;
        case SDLK_LCTRL: return D_KLeftCtrl;
        case SDLK_LGUI: return D_KLeftSuper;
        case SDLK_LALT: return D_KAlt;
        case SDLK_SPACE: return D_KSpace;
        case SDLK_ALTERASE: return D_KAltGr;
        case SDLK_RGUI: return D_KRightSuper;
        case SDLK_MENU: return D_KContextMenu;
        case SDLK_RCTRL: return D_KRightCtrl;
        case SDLK_RSHIFT: return D_KRightShift;
        case SDLK_RETURN: return D_KEnter;
        case SDLK_BACKSPACE: return D_KBackspace;

        //case SDLK_PIPE: return D_KPipe;

        case SDLK_MINUS: return D_KMinus;
        case SDLK_EQUALS: return D_KEqual;
        case SDLK_LEFTBRACKET: return D_KLeftBracket;
        case SDLK_RIGHTBRACKET: return D_KRightBracket;
        case SDLK_SEMICOLON: return D_KSemicolon;
        case SDLK_QUOTE: return D_KQuote;
        case SDLK_HASH: return D_KHash;
        case SDLK_COMMA: return D_KComma;
        case SDLK_PERIOD: return D_KPeriod;
        case SDLK_SLASH: return D_KForwardSlash;

        case SDLK_UNDERSCORE: return D_KUnderscore;
        case SDLK_PLUS: return D_KPlus;
        //case SDLK_LEFTBRACE: return D_KLeftBrace;
        //case SDLK_RIGHTBRACE: return D_KRightBrace;
        case SDLK_COLON: return D_KColon;
        case SDLK_AT: return D_KAt;
        //case SDLK_TIDLE: return D_KTilde;
        case SDLK_LESS: return D_KLessThan;
        case SDLK_GREATER: return D_KGreaterThan;
        case SDLK_QUESTION: return D_KQuestion;

        case SDLK_F1: return D_KF1;
        case SDLK_F2: return D_KF2;
        case SDLK_F3: return D_KF3;
        case SDLK_F4: return D_KF4;
        case SDLK_F5: return D_KF5;
        case SDLK_F6: return D_KF6;
        case SDLK_F7: return D_KF7;
        case SDLK_F8: return D_KF8;
        case SDLK_F9: return D_KF9;
        case SDLK_F10: return D_KF10;
        case SDLK_F11: return D_KF11;
        case SDLK_F12: return D_KF12;

        case SDLK_PRINTSCREEN: return D_KPrintScreen;
        case SDLK_SCROLLLOCK: return D_KScrollLock;
        case SDLK_PAUSE: return D_KPause;

        case SDLK_INSERT: return D_KInsert;
        case SDLK_HOME: return D_KHome;
        case SDLK_PAGEUP: return D_KPageUp;
        case SDLK_DELETE: return D_KDelete;
        case SDLK_END: return D_KEnd;
        case SDLK_PAGEDOWN: return D_KPageDown;
    };

    return D_KNone;
};

/* This function fills the event queue with the
 *  events that happened since the last call to
 *  D_PumpEvents(). Use D_GetEvent() to read take
 *  them off the queue.
 *
 * If this function causes a segfault, it's
 *  probably because D_StartEvents() has not been
 *  called. Remember to to also use
 *  D_StopEvents().
 *
 * returns: 0.
 */
int D_PumpEvents(){
    SDL_PumpEvents();
    SDL_Event se;
    D_Event e;

    //For every SDL event
    while(SDL_PeepEvents(&se, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0){

        //Translate it to a D event and add it to the queue
        switch(se.type){
            case SDL_MOUSEBUTTONDOWN:
                e.type = D_MOUSEDOWN;
                e.mouse.x = se.button.x;
                e.mouse.y = se.button.y;
                D_CauseEvent(&e);
                break;

            case SDL_MOUSEBUTTONUP:
                e.type = D_MOUSEUP;
                e.mouse.x = se.button.x;
                e.mouse.y = se.button.y;
                D_CauseEvent(&e);
                break;

            case SDL_MOUSEMOTION:
                e.type = D_MOUSEMOVE;
                e.mouse.x = se.motion.x;
                e.mouse.y = se.motion.y;
                D_CauseEvent(&e);
                break;

            case SDL_KEYDOWN:
                e.type = D_KEYDOWN;
                e.keyboard.key = D_SDLKToDKey(se.key.keysym.sym);
                D_CauseEvent(&e);
                break;

            case SDL_KEYUP:
                e.type = D_KEYUP;
                e.keyboard.key = D_SDLKToDKey(se.key.keysym.sym);
                D_CauseEvent(&e);
                break;

            case SDL_QUIT:
                e.type = D_QUIT;
                D_CauseEvent(&e);
                break;
        };

    };
    return 0;
};

/* This stops the thread from running
 *  for ms millisecon.
 *
 * ms: how many millisecon to stop.
 */
int D_Delay(int ms){
    SDL_Delay(ms);
    return 0;
};

#endif // D_PLATFORM_ALREADY_IMPLEMENTED

#endif // D_PLATFORM_IMPLEMENTATION
