#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <commons.h>
#include <buttons.h>
#include <progressbar.h>
#include <render.h>

/*----------------------------------------------------------------------------*/

// A pointer to the first object in the render queue
static RENDERQUEUEPTR firstptr = NULL;

/*----------------------------------------------------------------------------*/

// Returns the first object in the RENDERQUEUE
RENDERQUEUEPTR get_first_element_from_render_queue(void)
{
    return firstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Sets the first item in the RENDERQUEUE to the specified item
// This function should never be used in other modules, it should only be used internally in this module
RENDERQUEUEPTR set_first_element_in_render_queue(RENDERQUEUEPTR *newfirst)
{
    firstptr = *newfirst;
    return firstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Takes the first item in the RENDERQUEUE, processes it, draws it, removes it from the queue and moves on to
// the next item in the queue
void render(void)
{
    RENDERQUEUEPTR currentptr;
    currentptr = firstptr;
    while(currentptr != NULL)
    {
        if(currentptr->rcallb != NULL)
            currentptr->rcallb(currentptr->image, currentptr->x, currentptr->y, currentptr->nflags,
                               currentptr->blend_color);
        else
            al_draw_tinted_bitmap(currentptr->image, currentptr->blend_color, currentptr->x, currentptr->y, currentptr->nflags);
        currentptr = remove_element_from_render_queue(&currentptr);
    }
    render_buttons();
    render_progress_bars();
    render_mouse_cursor(get_game_data()->cursor);
}

/*----------------------------------------------------------------------------------------------------------*/

// Adds an element to the queue, this function is used mainly by other modules when something needs to be
// drawn

RENDERQUEUEPTR add_element_to_render_queue(ALLEGRO_BITMAP *image, float x, float y, int nflags,
                                           ALLEGRO_COLOR blendcol, RENDER_CALLBACK rcallback)
{
    RENDERQUEUEPTR newptr, currentptr;

    newptr = (RENDERQUEUEPTR)malloc(sizeof(RENDERQUEUE));
    if(newptr != NULL)
    {
        newptr->image = image;
        newptr->x = x;
        newptr->y = y;
        newptr->nflags = nflags;
        newptr->blend_color = blendcol;
        newptr->rcallb = rcallback;
        newptr->next = NULL;
        newptr->prev = NULL;

        currentptr = firstptr;

        while(currentptr != NULL && currentptr->next != NULL)
            currentptr = currentptr->next;

        if(currentptr == NULL)
        {
            currentptr = newptr;
            firstptr = currentptr;
        }
        else
        {
            currentptr->next = newptr;
            newptr->prev = currentptr;
        }
        return newptr;
    }
    else
    {
         return NULL;
    }
}

/*----------------------------------------------------------------------------------------------------------*/

// Removes an item from the queue, mainly used after the item has been drawn
RENDERQUEUEPTR remove_element_from_render_queue(RENDERQUEUEPTR *currentptr)
{
    if(*currentptr == NULL || firstptr == NULL) return NULL;
    if((*currentptr)->next != NULL)
    {
        (*currentptr)->next->prev = NULL;
        firstptr = (*currentptr)->next;
        free(*currentptr);
    }
    else
    {
        firstptr = NULL;
        free(*currentptr);
    }
    return firstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Empties render queue of all pending items
_Bool empty_render_queue(RENDERQUEUEPTR rfirstptr)
{
    RENDERQUEUEPTR currentptr = rfirstptr;
    if(rfirstptr == NULL) return false;

    while(currentptr != NULL)
    {
        currentptr = currentptr->next;
        free(rfirstptr);
        rfirstptr = currentptr;
    }

    firstptr = NULL;
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

void render_mouse_cursor(ALLEGRO_BITMAP *cursor)
{
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);
    al_draw_bitmap(cursor, mouse.x, mouse.y, 0);
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
