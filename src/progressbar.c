#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <progressbar.h>

/*----------------------------------------------------------------------------*/

static PROGRESSBARPTR pbfirstptr;

/*----------------------------------------------------------------------------*/

PROGRESSBARPTR get_first_element_from_progress_bar_list(void)
{
    return pbfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR set_first_element_in_progress_bar_list(PROGRESSBARPTR *newfirst)
{
    pbfirstptr = *newfirst;
    return pbfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR create_new_progress_bar(char *label, float x, float y, float width, float height, float rx,
                                       float ry, ALLEGRO_COLOR out_color, ALLEGRO_COLOR in_color,
                                       float thickness, _Bool add_to_list)
{
    PROGRESSBARPTR newptr;
    if((newptr = (PROGRESSBARPTR)malloc(sizeof(PROGRESSBAR))) == NULL) return NULL;

    newptr->pblabel = label;
    newptr->x1 = x;
    newptr->y1 = y;
    newptr->width = width;
    newptr->height = height;
    newptr->x2 = x+width;
    newptr->y2 = y+height;
    newptr->line_thickness = thickness;
    newptr->rx = rx;
    newptr->ry = ry;
    newptr->bar_width = 0;
    newptr->increment = width/100;
    newptr->out_color = out_color;
    newptr->in_color = in_color;
    newptr->counter = 0;
    newptr->done = false;

    if(add_to_list)
        add_element_to_progress_bar_list(&newptr);

    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR add_element_to_progress_bar_list(PROGRESSBARPTR *progbar)
{
    PROGRESSBARPTR currentptr;
    if(pbfirstptr == NULL)
    {
        pbfirstptr = *progbar;
        (*progbar)->nextbar = *progbar;
        (*progbar)->prevbar = *progbar;
    }
    else
    {
        currentptr = pbfirstptr->prevbar;
        currentptr->nextbar = *progbar;
        (*progbar)->prevbar = currentptr;
        pbfirstptr->prevbar = *progbar;
        (*progbar)->nextbar = pbfirstptr;
    }
    return pbfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR remove_element_from_progress_bar_list(char *label)
{
    PROGRESSBARPTR currentptr;
    currentptr = pbfirstptr;
    if(currentptr == NULL || pbfirstptr == NULL) return NULL;
    if((currentptr = search_progress_bar_list_for_element(label)) == NULL) return pbfirstptr;
    if(currentptr == pbfirstptr && currentptr->nextbar == currentptr && currentptr->prevbar == currentptr)
    {
        free(currentptr);
        pbfirstptr = NULL;
    }
    else
    {
        currentptr->nextbar->prevbar = currentptr->prevbar;
        currentptr->prevbar->nextbar = currentptr->nextbar;
        if(currentptr == pbfirstptr)
            pbfirstptr = currentptr->nextbar;
        free(currentptr);
    }
    return pbfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR search_progress_bar_list_for_element(char *label)
{
    PROGRESSBARPTR currentptr = pbfirstptr;
    if(currentptr == NULL) return NULL;
    do
    {
        if(strcmp(currentptr->pblabel, label) == 0) break;
        currentptr = currentptr->nextbar;
    } while(currentptr != pbfirstptr);

    if(strcmp(currentptr->pblabel, label) != 0) return NULL;
    return currentptr;
}

/*----------------------------------------------------------------------------------------------------------*/

void render_progress_bars(void)
{
    PROGRESSBARPTR currentptr = pbfirstptr;
    if(pbfirstptr != NULL || currentptr != NULL)
    {
        do
        {
            if(currentptr->bar_width > currentptr->width)
            {
                currentptr->bar_width = currentptr->width;
                currentptr->done = true;
            }
            al_draw_rounded_rectangle(currentptr->x1, currentptr->y1, currentptr->x2, currentptr->y2, currentptr->rx,
                                      currentptr->ry, currentptr->out_color, currentptr->line_thickness);
            al_draw_filled_rounded_rectangle(currentptr->x1, currentptr->y1, currentptr->x1+currentptr->bar_width,
                                             currentptr->y2, currentptr->rx, currentptr->ry, currentptr->in_color);
            currentptr = currentptr->nextbar;
        } while(currentptr != pbfirstptr);
    }
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_progress_bar_list(PROGRESSBARPTR firstptr)
{
    PROGRESSBARPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextbar == firstptr && firstptr->prevbar == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextbar == firstptr->prevbar)
    {
        currentptr = currentptr->nextbar;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextbar;
        firstptr->prevbar->nextbar = NULL;
        currentptr->prevbar = NULL;
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextbar;
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
