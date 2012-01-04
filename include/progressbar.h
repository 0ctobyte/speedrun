/**
  *@file progressbar.h
  *Routines to draw and update progress bars
  */
//    /**
//      *@defgroup progressbarh progressbar.h
//      *Routines to draw and update progress bars
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

typedef struct progress_bar {
    char *pblabel;
    float x1;
    float y1;
    float x2;
    float y2;
    float line_thickness;
    float width;
    float height;
    float rx;
    float ry;
    float bar_width;
    float increment;
    int counter;
    _Bool done;
    ALLEGRO_COLOR out_color;
    ALLEGRO_COLOR in_color;
    struct progress_bar *nextbar;
    struct progress_bar *prevbar;
} PROGRESSBAR, *PROGRESSBARPTR;

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR get_first_element_from_progress_bar_list(void);

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR set_first_element_in_progress_bar_list(PROGRESSBARPTR *newfirst);

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR create_new_progress_bar(char *label, float x, float y, float width, float height, float rx,
                                       float ry, ALLEGRO_COLOR out_color, ALLEGRO_COLOR in_color,
                                       float thickness, _Bool add_to_list);

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR add_element_to_progress_bar_list(PROGRESSBARPTR *progbar);

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR remove_element_from_progress_bar_list(char *label);

/*----------------------------------------------------------------------------------------------------------*/

PROGRESSBARPTR search_progress_bar_list_for_element(char *label);

/*----------------------------------------------------------------------------------------------------------*/

void render_progress_bars(void);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_progress_bar_list(PROGRESSBARPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
