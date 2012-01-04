#include <allegro5/allegro5.h>
#include <mouse.h>

/*----------------------------------------------------------------------------*/

// A structure that contains info on mouse input, state etc
// FIXME: A duplicate of the Allegro provided mouse structure, find a more elegant solution
static MOUSE mouse;

/*----------------------------------------------------------------------------*/

// Set the MOUSE_? and MOUSE_?_NEW flags
void mousedown(ALLEGRO_MOUSE_EVENT *mouse_data)
{
	mouse.button |= (MOUSE_L | MOUSE_L_NEW) << ((mouse_data->button-1)*2);
}

/*----------------------------------------------------------------------------------------------------------*/

// Clear the MOUSE_? flag, but not the MOUSE_?_NEW flag
void mouseup(ALLEGRO_MOUSE_EVENT *mouse_data)
{
	mouse.button &= (~MOUSE_L) << ((mouse_data->button-1)*2);
}

/*----------------------------------------------------------------------------------------------------------*/

// Updates mouse coordinate states
void mouseaxes(ALLEGRO_MOUSE_EVENT *mouse_data)
{
	mouse.dx = mouse_data->x - mouse.x;
	mouse.dy = mouse_data->y - mouse.y;
	mouse.dz = mouse_data->z - mouse.z;
	mouse.x = mouse_data->x;
	mouse.y = mouse_data->y;
	mouse.z = mouse_data->z;
}

/*----------------------------------------------------------------------------------------------------------*/

// Clears mouse flags and mouse axes states
void mouseupdate(void)
{
	// Clear all the MOUSE_?_NEW flags
	mouse.button &= ~0xAAAAAAAA;

	// Clear all change in mouse axes states
	mouse.dx = 0;
	mouse.dy = 0;
	mouse.dz = 0;
}

/*----------------------------------------------------------------------------------------------------------*/

// Check for mouse input, calls a fucntion pointer too by the function pointer
void* mousecheck(MOUSE_CALLBACK func, void* data)
{
    return func(&mouse, data);
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
