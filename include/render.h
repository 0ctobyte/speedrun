/**
  *@file render.h
  *Routines to queue objects in a list and draw them on screen in the order they arrived in the queue
  */
//    /**
//      *@defgroup renderh render.h
//      *Routines to queue objects in a list and draw them on screen in the order they arrived in the queue
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

#define RCOLOR(r, g, b, a) al_map_rgba(r, g, b, a)
#define RDEFAULT al_map_rgba(255, 255, 255, 255)

/*----------------------------------------------------------------------------------------------------------*/

typedef void(*RENDER_CALLBACK)(ALLEGRO_BITMAP*, float, float, int, ALLEGRO_COLOR);

/*----------------------------------------------------------------------------------------------------------*/

typedef struct render_queue {
    ALLEGRO_BITMAP *image;
    float x;
    float y;
    int nflags;
    ALLEGRO_COLOR blend_color;
    RENDER_CALLBACK rcallb;
    struct render_queue *next;
    struct render_queue *prev;
} RENDERQUEUE, *RENDERQUEUEPTR;

/*----------------------------------------------------------------------------------------------------------*/

RENDERQUEUEPTR get_first_element_from_render_queue(void);

/*----------------------------------------------------------------------------------------------------------*/

RENDERQUEUEPTR set_first_element_in_render_queue(RENDERQUEUEPTR *newfirst);

/*----------------------------------------------------------------------------------------------------------*/

RENDERQUEUEPTR add_element_to_render_queue(ALLEGRO_BITMAP *image, float x, float y, int nflags,
                                           ALLEGRO_COLOR blendcol, RENDER_CALLBACK rcallback);

/*----------------------------------------------------------------------------------------------------------*/

RENDERQUEUEPTR remove_element_from_render_queue(RENDERQUEUEPTR *currentptr);

/*----------------------------------------------------------------------------------------------------------*/

void render(void);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_render_queue(RENDERQUEUEPTR rfirstptr);

/*----------------------------------------------------------------------------------------------------------*/

void render_mouse_cursor(ALLEGRO_BITMAP *cursor);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
