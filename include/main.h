/**
  *@file main.h
  *The entry point of the program and contains the main_loop function.
  */
/**
  *@mainpage SpeedRun!
  *@author Sekhar Bhattacharya
  *@date March-20-2010
  *
  *@section intro Introduction
  *
  *The game is actually a final project for grade 12 computer science course.
  *It is basically a clone of the popular iPhone game, Run!
  *The game uses the Allegro game/graphics library and the chipmunk physics engine to do all
  *the hard work!
  *
  *At the time of writing this game I was actually still learning C I thought this would
  *be a good way to learn; by programming a game. Also, this was an excellent setting for me
  *to use my newly found knowledge of linked lists and queues!
  *
  *Take a look around this documentation and see how I created this game \n \n
  *FILE LIST: Lists all the source and header files used in this game, you can even view all the code \n
  *MODULE LIST: Lists all the files like file list but...displays them differently \n 
  *DATA STRUCTURES: Lists all the structs in the game, click on them to see what they are all about \n
  *
  *
  *@section body1 How To Play
  *I never got time to actually implement the How to Play menu in game, so here are the basic rules \n \n
  *1. Arrow keys to move, or WASD \n
  *2. Up/Down or W/S to jump/slide \n
  *3. Spacebar to attack, you can attack while jumping/sliding \n
  *4. Jump over the metal looking box/walls, they are invincible \n
  *5. Slide under the fist, invincible \n
  *6. The red boxes/walls are also invincible! But you can destroy them by clicking on them with the mouse \n
  *7. Avoid/dodge/attack all other enemies \n
  *8. Points are scored for destroying the enemies, and there is a survival timer \n
  *9. P to PAUSE! \n
  *10. Press M to return to main menu if it gets to hard! \n
  *
  *
  *@section body2 Compile from source on Windows
  *This should compile on Windows XP/Vista/7, it might lag if the computer is old.
  *You must have TDM Dragon's version of MINGW32 INSTALLED! (google it)  With gcc version 4.5
  *MAKE SURE MinGW32/bin IS IN YOUR PATH AND Mingw32-make.exe WORKS
  *
  *You must use the makefile provided to build the game. Follow the steps \n \n
  *1. Open a command prompt \n
  *2. cd to the speedrun directory \n
  *3. type in Mingw32-make \n
  *4. Let it run to completion \n
  *5. The executable is in the newly created DIST folder with all required files/folders \n
  *
  *
  *@section info Update
  *
  *This project is will always be a work in progress!
  *There is still a lot to do!
  */
//    /**
//      *@defgroup mainh main.h
//      *The entry point of the program and contains the main_loop function.
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

// MUST define this for static linking
#define ALLEGRO_STATICLINK 1

/*----------------------------------------------------------------------------------------------------------*/

/**
  *@brief
  *The entry point of the game
  *
  *Initializes all needed assets and transfer control to the
  *main_loop.
  *@param [in] argc
  *The number of command line arguments passed to the program for processing
  *@param [in] *argv[]
  *The commands passed to the program, contained in an array of char*'s
  *@return
  *Returns 1 and exits if any of the initialization functions fail, otherwise
  *it returns 0 at the end of program execution.
  *@see gdata
  *@see data_init
  *@see init_core_sprites
  *@see init_buttons
  *@see main_loop
  *@todo
  *remove init_core_sprites, put instead ini_base_images,
  *instead of initializing sprites at startup,
  *initialize them before the game starts.
  *This way the sprites can be reset to their default x and y coordinates without
  *the need of additional functions. Also, empty sprite list when the game is exited
  *back to the menu.
  */
int main(int argc, char** argv);

/*----------------------------------------------------------------------------------------------------------*/

/**
  *@brief
  *Everything happens here!
  *
  *The main game loop, all other function are directly or indirectly called from
  *this function. The fucntion does not return until the game quits, i.e. when the user
  *hits the escape key or closes the Allegro window.
  *@return
  *Returns true when the game exits.
  *@note A good place to start when tracing errors!
  */
_Bool main_loop(void);

/*----------------------------------------------------------------------------------------------------------*/

/**
  *@brief
  *Initializes the gdata structure.
  *
  *Initializes all members of the gdata structure, *data.
  *Specifically, the screen is set, timer started, keyboard and mouse installed,
  *allegro events registered and other important routines are executed.
  *@return
  *Returns true if all initializes were executed correctly, otherwise
  *false is returned and program will then exit
  */
_Bool data_init(void);

/*----------------------------------------------------------------------------------------------------------*/

void loader(void);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
