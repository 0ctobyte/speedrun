#include <allegro5/allegro5.h>
#include <keyboard.h>

/*----------------------------------------------------------------------------*/

static char key[256];			// Keyboards only have upto 256 keycodes, so no array out of bounds can occur

/*----------------------------------------------------------------------------*/

// If a key is pressed down, add it to the key array
void keydown(ALLEGRO_KEYBOARD_EVENT *kb)
{
	key[kb->keycode] = KEYPRESSED | KEYNEW;
}

/*----------------------------------------------------------------------------------------------------------*/

// If a key is released, mark it as unpressed
// But if it was not yet processed, leave the keynew flag
void keyup(ALLEGRO_KEYBOARD_EVENT *kb)
{
	key[kb->keycode] &= ~KEYPRESSED;
}

/*----------------------------------------------------------------------------------------------------------*/

// If an operating system repeat event comes in, set the flag
void keyrepeat(ALLEGRO_KEYBOARD_EVENT *kb)
{
	key[kb->keycode] |= KEYREPEAT;
}

/*----------------------------------------------------------------------------------------------------------*/

// Called once per frame: removes the KEYNEW and KEYREPEAT status from all keys
void keyupdate(void)
{
	int i;
	static int val =  ((KEYNEW | KEYREPEAT) << 24) | ((KEYNEW | KEYREPEAT) << 16) |
                      ((KEYNEW | KEYREPEAT) << 8) | KEYNEW | KEYREPEAT;

	for(i=0; i<64; i++)
	{
        ((int*)key)[i] &= ~val;
	}
}

/*----------------------------------------------------------------------------------------------------------*/

// Empties the key buffer
void keyclear(void)
{
	memset(key, 0, sizeof(*key)*256);
}

/*----------------------------------------------------------------------------------------------------------*/

// Check for keyboard input
void* keycheck(KEY_CALLBACK func, void *data)
{
	return func(key, data);
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
