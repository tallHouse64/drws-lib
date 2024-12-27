
/*
 * This is the devents library, it is
 *  made to be used with the d library
 *  for events so they can be used
 *  together to make games.
 *
 */

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

typedef struct D_MouseEvent {
    int x, y;
    D_MouseButton button;
} D_MouseEvent;

typedef struct D_Event {
    D_EventType type;
    union {
        struct D_MouseEvent mouse;
    };
} D_Event;

/*
 * You join the back of the queue, and leave the front.
 */
D_Event * D_EventQueue;
int D_EventQueueFront;
int D_EventQueueBack;
int D_EventQueueFull;

#define D_ISEVENTQUEUEEMPTY() (!(D_EventQueueFull) && (D_EventQueueBack == ((D_EventQueueFront - 1) + D_EVENT_QUEUE_LENGTH) % D_EVENT_QUEUE_LENGTH) )

int D_StartEvents(){
    D_EventQueue = D_CALLOC(sizeof(D_Event), D_EVENT_QUEUE_LENGTH);
    D_EventQueueFront = 0;
    D_EventQueueBack = D_EVENT_QUEUE_LENGTH - 1;
    D_EventQueueFull = 0;
};

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
