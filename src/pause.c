#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <chipmunk/chipmunk.h>
#include <commons.h>
#include <buttons.h>
#include <sprites.h>
#include <render.h>
#include <maingame.h>
#include <pause.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR resume = NULL, quit = NULL, exitgame = NULL;

/*----------------------------------------------------------------------------*/

void paused(int score, char *survival_time, int lives)
{
    GDATAPTR game = get_game_data();

    if(quit == NULL)
    {
        quit = create_new_button("QUITTOMENU",
                                 "DEFAULT",
                                 "QUIT TO MENU",
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
    if(exitgame == NULL)
    {
        exitgame = create_new_button("EXITGAME",
                                     "DEFAULT",
                                     "EXIT GAME",
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
    if(resume == NULL)
    {
        resume = create_new_button("RESUME",
                                   "DEFAULT",
                                   "RESUME",
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

    add_element_to_render_queue(NULL, 280, 325, 0, RCOLOR(0, 0, 0, 255), update_score);
    add_element_to_render_queue(NULL, 280, 375, 0, RCOLOR(0, 0, 0, 255), update_survivaltime);

    SPRITESPTR sprite = search_sprite_list_for_element("STICKMAN");
    SIMAGEPTR life = search_image_list_for_element(&(sprite->ifirstptr), "STICKFIGURE_LIVES");

    int x = 280;
    int y = 425;

    for(int i = 0; i < lives; i++)
    {
        add_element_to_render_queue(life->image, x, y, 0, RCOLOR(255, 255, 255, 255), NULL);
        x += life->width+10;
    }

}

/*----------------------------------------------------------------------------------------------------------*/

void pause_cleanup(void)
{
    remove_element_from_button_list(&quit);
    remove_element_from_button_list(&exitgame);
    remove_element_from_button_list(&resume);
    quit = NULL;
    exitgame = NULL;
    resume = NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void exit_pause(GDATAPTR game)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "QUITTOMENU");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "EXITGAME");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "RESUME");
    currentptr->bdata.limit = -600;
    currentptr->bdata.aflags = BLEFT;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
