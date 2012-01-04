/**
  *@file eventhandler.h
  *Handles all keyboard, mouse and button events
  */
//    /**
//      *@defgroup eventhandlerh eventhandler.h
//      *Handles all keyboard, mouse and button events
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

/**
  *@brief
  *Checks for keyboard input.
  *
  *This function is called once every frame via a function pointer through keyboard.c
  *keycheck function. All keyboard input is handled here. The void pointer points
  *to a struct of type GDATA to set the the structure member 'quit' and 'gamestarted'
  *to false or true depending on the situation
  *@param [in] key
  *The pointer to an array of chars which contain the details for which key has been pressed.
  *The array of chars is processed and updated by the keyboard.c routines.
  *@param [out] *data
  *A pointer to type void is required to process optional additional data,
  *specifically a pointer to type GDATA is passed to terminate or start the game
  *on certain keystrokes.
  *@see keycheck
  *@see keyup
  *@see keydown
  *@see keyrepeat
  *@see keyupdate
  *@see keyclear
  *@return
  *Returns a void pointer, so any data can be returned if need be.
  */
void* keyhandler(String key, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void* mousehandler(MOUSE* mouse_s, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void* buttonhandler(BUTTONPTR button, void* data, int type);

/*----------------------------------------------------------------------------------------------------------*/

void execute_on_button_press(void);

/*----------------------------------------------------------------------------------------------------------*/

void execute_on_M_press(void);

/*----------------------------------------------------------------------------------------------------------*/

void return_to_main_menu(GDATAPTR game);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
