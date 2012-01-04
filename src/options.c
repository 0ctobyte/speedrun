#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <commons.h>
#include <buttons.h>
#include <options.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR fullscreen = NULL, fpscount = NULL, back = NULL;

/*----------------------------------------------------------------------------*/

static _Bool fps = true;

/*----------------------------------------------------------------------------------------------------------*/

_Bool get_fps_status(void)
{
    return fps;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool set_fps_status(_Bool _fps)
{
    fps = _fps;
    return fps;
}

/*----------------------------------------------------------------------------------------------------------*/

void options(void)
{
    GDATAPTR game = get_game_data();
    char *text, *onoff;
    int flags = al_get_display_flags(game->display);
    if(flags & ALLEGRO_FULLSCREEN_WINDOW)
        text = "WINDOWED";
    else
        text = "FULLSCREEN";

    if(fps)
        onoff = "FPS COUNTER: ON";
    else
        onoff = "FPS COUNTER: OFF";

    if(fullscreen == NULL)
    {
        fullscreen = create_new_button("FULLSCREEN",
                                       "DEFAULT",
                                       text,
                                       game->b_font,
                                       BCOLOR(255, 255, 255, 255), //80, 112/122, 255
                                       BCOLOR(65, 105, 255, 191),
                                       -280, //263
                                       150, //225
                                       263,
                                       BRIGHT,
                                       BVISIBLE,
                                       true
                                       );
    }
    if(fpscount == NULL)
    {
        fpscount = create_new_button("FPS",
                                     "DEFAULT",
                                     onoff,
                                     game->b_font,
                                     BCOLOR(255, 255, 255, 255), //80, 112/122, 255
                                     BCOLOR(65, 105, 255, 191),
                                     -280, //263
                                     250, //225
                                     263,
                                     BRIGHT,
                                     BVISIBLE,
                                     true
                                     );
    }
    if(back == NULL)
    {
        back = create_new_button("BACK",
                                 "DEFAULT",
                                 "BACK",
                                 game->b_font,
                                 BCOLOR(255, 255, 255, 255),
                                 BCOLOR(65, 105, 255, 191),
                                 -280,
                                 500,
                                 50,
                                 BRIGHT,
                                 BVISIBLE,
                                 true
                                 );
    }
}

/*----------------------------------------------------------------------------------------------------------*/

void options_cleanup(void)
{
    remove_element_from_button_list(&fullscreen);
    remove_element_from_button_list(&fpscount);
    remove_element_from_button_list(&back);
    fullscreen = NULL;
    fpscount = NULL;
    back = NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void exit_options(GDATAPTR game)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "FULLSCREEN");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "FPS");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "BACK");
    currentptr->bdata.limit = -600;
    currentptr->bdata.aflags = BLEFT;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
