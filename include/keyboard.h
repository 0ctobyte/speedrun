/**
  *@file keyboard.h
  *Handles keyboard input
  *@note Does not trigger keyboard events; events are handled by the keyhandler function in the handler.c
  *routines. The keyhandler function is called by this modules keycheck function via a function pointer.
  */
//    /**
//      *@defgroup keyboardh keyboard.h
//      *Handles keyboard input
//      *@note Does not trigger keyboard events; events are handled by the keyhandler function in the handler.c
//      *routines. The keyhandler function is called by this modules keycheck function via a function pointer.
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

#define KEYPRESSED	0x1
#define KEYNEW		0x2
#define KEYREPEAT	0x4

/*----------------------------------------------------------------------------------------------------------*/

typedef void* (*KEY_CALLBACK)(char*, void*);

/*----------------------------------------------------------------------------------------------------------*/

void keydown(ALLEGRO_KEYBOARD_EVENT *kb);

/*----------------------------------------------------------------------------------------------------------*/

void keyup(ALLEGRO_KEYBOARD_EVENT *kb);

/*----------------------------------------------------------------------------------------------------------*/

void keyrepeat(ALLEGRO_KEYBOARD_EVENT *kb);

/*----------------------------------------------------------------------------------------------------------*/

void keyupdate(void);

/*----------------------------------------------------------------------------------------------------------*/

void keyclear(void);

/*----------------------------------------------------------------------------------------------------------*/

void* keycheck(KEY_CALLBACK func, void *data);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
