/**
  *@file mouse.h
  *Handles mouse input
  *@note Does not trigger mouse events; events are handled by the mousehandler function in the handler.c
  *routines. The mousehandler function is called by this modules mousecheck function via a function pointer.
  */
//    /**
//      *@defgroup mouseh mouse.h
//      *Handles mouse input
//      *@note Does not trigger mouse events; events are handled by the mousehandler function in the handler.c
//      *routines. The mousehandler function is called by this modules mousecheck function via a function pointer.
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

typedef enum mouse_events {
    MOUSE_L = 0x1,
    MOUSE_L_NEW = 0x2,
    MOUSE_R = 0x4,
    MOUSE_R_NEW = 0x8,
    MOUSE_M = 0x10,
    MOUSE_M_NEW = 0x20
} MOUSEEVENTS;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct mouse {
    MOUSEEVENTS button;
    int x;
    int y;
    int z;
    int dx;
    int dy;
    int dz;
} MOUSE;

/*----------------------------------------------------------------------------------------------------------*/

typedef void* (*MOUSE_CALLBACK)(MOUSE*, void*);

/*----------------------------------------------------------------------------------------------------------*/

void mousedown(ALLEGRO_MOUSE_EVENT *mouse_data);

/*----------------------------------------------------------------------------------------------------------*/

void mouseup(ALLEGRO_MOUSE_EVENT *mouse_data);

/*----------------------------------------------------------------------------------------------------------*/

void mouseaxes(ALLEGRO_MOUSE_EVENT *mouse_data);

/*----------------------------------------------------------------------------------------------------------*/

void mouseupdate(void);

/*----------------------------------------------------------------------------------------------------------*/

void* mousecheck(MOUSE_CALLBACK func, void* data);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
