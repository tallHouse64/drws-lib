
/*
 * This is the devents library, it is
 *  made to be used with the d library
 *  for events so they can be used
 *  together to make games.
 *
 */

#ifndef DEVENTS_H
#define DEVENTS_H

#ifndef D_DONT_USE_STDLIB
#include<stdlib.h>
#endif

#define D_EVENT_QUEUE_LENGTH 32

#ifndef D_NULL
#define D_NULL 0x0
#endif

#ifndef D_CALLOC
#define D_CALLOC calloc
#endif

#ifndef D_FREE
#define D_FREE free
#endif

typedef enum D_EventType {
    D_NOEVENT = 0,
    D_KEYDOWN,
    D_KEYUP,
    D_MOUSEDOWN,
    D_MOUSEUP,
    D_MOUSEMOVE,
    D_QUIT
} D_EventType;

//Bit masks that can be combin using bitwis or |
typedef enum D_MouseButton {
    D_NOBUTTON     = 0x00,
    D_LEFTBUTTON   = 0x01,
    D_MIDDLEBUTTON = 0x02,
    D_RIGHTBUTTON  = 0x04,
    D_BUTTON1      = 0x08,
    D_BUTTON2      = 0x10
} D_MouseButton;

/* In this keyboard enum, the meaning of the key
 *  is used. If a "u" key is pressed, a D_Ku
 *  keypress is the result.
 *
 * In the future there may be another enum for
 *  scancodes, where key positions are used
 *  instead of thair meanings.
 *
 * This is roughly based off a UK keyboard.
 */
typedef enum D_Key {
    D_KNone = 0,
    D_Ka,
    D_Kb,
    D_Kc,
    D_Kd,
    D_Ke,
    D_Kf,
    D_Kg,
    D_Kh,
    D_Ki,
    D_Kj,
    D_Kk,
    D_Kl,
    D_Km,
    D_Kn,
    D_Ko,
    D_Kp,
    D_Kq,
    D_Kr,
    D_Ks,
    D_Kt,
    D_Ku,
    D_Kv,
    D_Kw,
    D_Kx,
    D_Ky,
    D_Kz,

    D_K0,
    D_K1,
    D_K2,
    D_K3,
    D_K4,
    D_K5,
    D_K6,
    D_K7,
    D_K8,
    D_K9,

    D_KExclamation,
    D_KDoubleQuote,
    D_KPound,
    D_KDollar,
    D_KPercentage,
    D_KCaret,
    D_KAmpersand,
    D_KAsterisk,
    D_KLeftParentheses,
    D_KRightParentheses,

    D_KLeft,
    D_KRight,
    D_KUp,
    D_KDown,

    //This moves anticlockwise around the edge of
    // a uk keybaord.
    D_KEscape,
    D_KBacktick,
    D_KTab,
    D_KCapLock,
    D_KLeftShift,
    D_KBackSlash,
    D_KLeftCtrl,
    D_KLeftSuper,
    D_KAlt,
    D_KSpace,
    D_KAltGr,
    D_KRightSuper,
    D_KContextMenu,
    D_KRightCtrl,
    D_KRightShift,
    D_KEnter,
    D_KBackspace,

    D_KPipe, // This |

    D_KMinus,
    D_KEqual,
    D_KLeftBracket,
    D_KRightBracket,
    D_KSemicolon,
    D_KQuote,
    D_KHash,
    D_KComma,
    D_KPeriod,
    D_KForwardSlash,

    D_KUnderscore,
    D_KPlus,
    D_KLeftBrace,
    D_KRightBrace,
    D_KColon,
    D_KAt,
    D_KTilde,
    D_KLessThan,
    D_KGreaterThan,
    D_KQuestion,

    D_KF1,
    D_KF2,
    D_KF3,
    D_KF4,
    D_KF5,
    D_KF6,
    D_KF7,
    D_KF8,
    D_KF9,
    D_KF10,
    D_KF11,
    D_KF12,

    D_KPrintScreen,
    D_KScrollLock,
    D_KPause,

    D_KInsert,
    D_KHome,
    D_KPageUp,
    D_KDelete,
    D_KEnd,
    D_KPageDown
} D_Key;

typedef struct D_KeyboardEvent {
    D_Key key; //keycode (meaning of the key)
} D_KeyboardEvent;

typedef struct D_MouseEvent {
    int x, y;
    D_MouseButton button;
} D_MouseEvent;

typedef struct D_Event {
    D_EventType type;
    union {
        struct D_KeyboardEvent keyboard;
        struct D_MouseEvent mouse;
    };
} D_Event;

int D_GetNumberOfEventsInEventQueue();
char D_DKeyToChar(D_Key k);
int D_StartEvents();
int D_StopEvents();
int D_CauseEvent(D_Event * e);
int D_GetEvent(D_Event * e);

#endif // DEVENTS_H

#ifdef DEVENTS_IMPLEMENTATION
#ifndef DEVENTS_ALREADY_IMPLEMENTED
#define DEVENTS_ALREADY_IMPLEMENTED

/*
 * You join the back of the queue, and leave the front.
 */
D_Event * D_EventQueue;
int D_EventQueueFront; //Starts as 0
int D_EventQueueBack; //Starts as D_EVENT_QUEUE_LENGTH - 1
int D_EventQueueFull;

#define D_ISEVENTQUEUEEMPTY() (!(D_EventQueueFull) && (D_EventQueueBack == ((D_EventQueueFront - 1) + D_EVENT_QUEUE_LENGTH) % D_EVENT_QUEUE_LENGTH) )

/* This fuction is used to find how many events
 *  are in the event queue.
 *
 * returns: The number of events in the queue.
 */
int D_GetNumberOfEventsInEventQueue(){

    //Check if the queue is in the special full or empty state

    if((D_EventQueueBack >= (D_EventQueueFront - 1) ? ((D_EventQueueBack - D_EventQueueFront) + 1) : (D_EVENT_QUEUE_LENGTH + ((D_EventQueueBack - D_EventQueueFront) + 1)) ) == D_EVENT_QUEUE_LENGTH){

        return (D_EventQueueFull ? 32 : 0);
    };

    //Otherwise use the same number as the if statement above
    return (D_EventQueueBack >= (D_EventQueueFront - 1) ? ((D_EventQueueBack - D_EventQueueFront) + 1) : (D_EVENT_QUEUE_LENGTH + ((D_EventQueueBack - D_EventQueueFront) + 1)) );
};

/* This function converts a D_Key to a char. If
 *  the key has no char value (like the shift
 *  key) it returns null.
 *
 * k: The D_Key to convert.
 * returns: A char value from the D_Key.
 */
char D_DKeyToChar(D_Key k){
    switch(k){
        case D_Ka: return 'a';
        case D_Kb: return 'b';
        case D_Kc: return 'c';
        case D_Kd: return 'd';
        case D_Ke: return 'e';
        case D_Kf: return 'f';
        case D_Kg: return 'g';
        case D_Kh: return 'h';
        case D_Ki: return 'i';
        case D_Kj: return 'j';
        case D_Kk: return 'k';
        case D_Kl: return 'l';
        case D_Km: return 'm';
        case D_Kn: return 'n';
        case D_Ko: return 'o';
        case D_Kp: return 'p';
        case D_Kq: return 'q';
        case D_Kr: return 'r';
        case D_Ks: return 's';
        case D_Kt: return 't';
        case D_Ku: return 'u';
        case D_Kv: return 'v';
        case D_Kw: return 'w';
        case D_Kx: return 'x';
        case D_Ky: return 'y';
        case D_Kz: return 'z';

        case D_K0: return '0';
        case D_K1: return '1';
        case D_K2: return '2';
        case D_K3: return '3';
        case D_K4: return '4';
        case D_K5: return '5';
        case D_K6: return '6';
        case D_K7: return '7';
        case D_K8: return '8';
        case D_K9: return '9';

        case D_KExclamation: return '!';
        case D_KDoubleQuote: return '"';
        //case D_KPound: return 0;
        case D_KDollar: return '$';
        case D_KPercentage: return '%';
        case D_KCaret: return '^';
        case D_KAmpersand: return '&';
        case D_KAsterisk: return '*';
        case D_KLeftParentheses: return '(';
        case D_KRightParentheses: return ')';

        case D_KBacktick: return '`';
        case D_KTab: return '\t';
        case D_KBackSlash: return '\\';
        case D_KSpace: return ' ';
        case D_KEnter: return '\n';
        case D_KBackspace: return '\b';

        case D_KPipe: return '|';

        case D_KMinus: return '-';
        case D_KEqual: return '=';
        case D_KLeftBracket: return '[';
        case D_KRightBracket: return ']';
        case D_KSemicolon: return ';';
        case D_KQuote: return '\'';
        case D_KHash: return '#';
        case D_KComma: return ',';
        case D_KPeriod: return '.';
        case D_KForwardSlash: return '/';

        case D_KUnderscore: return '_';
        case D_KPlus: return '+';
        case D_KLeftBrace: return '{';
        case D_KRightBrace: return '}';
        case D_KColon: return ':';
        case D_KAt: return '@';
        case D_KTilde: return '~';
        case D_KLessThan: return '<';
        case D_KGreaterThan: return '>';
        case D_KQuestion: return '?';
    };

    return '\0';
};

/* This function allocates memory for the event
 *  queue.
 */
int D_StartEvents(){
    D_EventQueue = D_CALLOC(sizeof(D_Event), D_EVENT_QUEUE_LENGTH);
    D_EventQueueFront = 0;
    D_EventQueueBack = D_EVENT_QUEUE_LENGTH - 1;
    D_EventQueueFull = 0;
};

/* This function frees the memory allocated for
 *  the event queue. After calling it, don't call
 *  D_GetEvent() or D_CauseEvent() unless you
 *  call D_StartEvents() again. (You would get a
 *  segfault).
 */
int D_StopEvents(){
    D_FREE(D_EventQueue);
    D_EventQueue = D_NULL;
};

/* Adds an event to the back of the event queue.
 *  It copies what e is pointing to. It returns
 *  0 on success. If the queue is full it returns
 *  -1. The queue is FIFO (First In First Out).
 *
 * e: The event to add to the back of the queue.
 * returns: 0 on success, -1 otherwise.
 */
int D_CauseEvent(D_Event * e){
    if(D_EventQueueFull){
        return -1;
    };
    D_EventQueueBack++;
    D_EventQueueBack %= D_EVENT_QUEUE_LENGTH;
    D_EventQueue[D_EventQueueBack] = *e;

    //If the back of the queue is to the left of the front (-1) after adding an event, the queue must be full.
    if( (D_EventQueueBack == ((D_EventQueueFront - 1) + D_EVENT_QUEUE_LENGTH) % D_EVENT_QUEUE_LENGTH) ){
        D_EventQueueFull = 1;
    };
    return 0;
};

/* This removes an event off the queue and fills
 *  in the e pointer with it. If the queue is
 *  empty it returns -1, if e is null it also
 *  returns -1;
 *
 * e: Pointer to write next event to.
 * returns: 0 on success, -1 otherwise.
 */
int D_GetEvent(D_Event * e){
    if(!D_ISEVENTQUEUEEMPTY() && e != D_NULL){
        D_EventQueueFront++;
        D_EventQueueFront %= D_EVENT_QUEUE_LENGTH;

        //After removing an event, the queue cannot be full
        D_EventQueueFull = 0;

        *e = (D_EventQueue[D_EventQueueFront - 1]);
        return 0;
    };
    return -1;
};

#endif // DEVENTS_ALREADY_IMPLEMENTED

#endif // DEVENTS_IMPLEMENTATION
