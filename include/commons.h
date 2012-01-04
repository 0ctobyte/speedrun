/**
  *@file commons.h
  *defines of all needed macros for the program, this module is global and is included in all other modules
  */
//    /**
//      *@defgroup commonsh commons.h
//      *defines of all needed macros for the program, this module is global and is included in all other modules
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

// Main stucture containing the core data needed to run the game
typedef struct gdata {
    ALLEGRO_DISPLAY *display;        // Holds the handle to the Allegro canvas
    ALLEGRO_EVENT event;             // Contains the data on triggered events
    ALLEGRO_EVENT_QUEUE *queue;      // Holds a list of events to be processed
    ALLEGRO_EVENT event2;            // Contains the data on triggered events
    ALLEGRO_EVENT_QUEUE *queue2;     // Holds a list of events to be processed
    ALLEGRO_TIMER *timer;            // Contains the timer struct, for animation
    ALLEGRO_FONT *font;              // Contains a font
    ALLEGRO_FONT *b_font;            // Contains the buttons's font
    ALLEGRO_COLOR background_color;  // The current background color
    ALLEGRO_COLOR text_color;        // The current text color
    ALLEGRO_BITMAP *icon;            // Holds the application icon image
    ALLEGRO_BITMAP *cursor;          // Image of custom mouse cursor
    _Bool exit;                      // Determines if the game should exit
    _Bool gamestarted;               // Determines when the game should start
    _Bool options;                   // Set to true when option button is clicked
    _Bool highscores;                // Set to true when highscore buttion is clicked
    _Bool howtoplay;                 // Set to true when howtoplay button is clicked
    _Bool paused;                    // Set to true when pause button is clicked
} GDATA, *GDATAPTR;

/*----------------------------------------------------------------------------------------------------------*/

/**
  *@brief
  *Grabs the main GDATA structure
  *
  *Returns a pointer to 'data', a pointer to a structure of type GDATA
  *@return
  *returns GDATAPTR
  */
GDATAPTR get_game_data(void);

/*----------------------------------------------------------------------------------------------------------*/

void cleanup(GDATAPTR game);

/*----------------------------------------------------------------------------------------------------------*/

// Now everyone understands!!!
typedef char* String;

/*----------------------------------------------------------------------------------------------------------*/

#define res_width            800
#define res_height           600

#define _I(x)                (int*)x
#define _B(x)                (double*)x
#define _C(x)                (char*)x
#define _D(x)                (double*)x
#define __I(x)               *(int*)x
#define __B(x)               *(_Bool*)x
#define __C(x)               *(char*)x
#define __D(x)               *(double*)x

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
