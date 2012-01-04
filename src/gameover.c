#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <chipmunk/chipmunk.h>
#include <commons.h>
#include <buttons.h>
#include <sprites.h>
#include <render.h>
#include <maingame.h>
#include <gameover.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR quit = NULL;

/*----------------------------------------------------------------------------*/

void gameover(int score, char *survival_time)
{
    GDATAPTR game = get_game_data();

    if(quit == NULL)
    {
        quit = create_new_button("QUITTOMENUGO",
                                 "DEFAULT",
                                 "QUIT TO MENU",
                                 game->b_font,
                                 BCOLOR(255, 255, 255, 255), //80, 112/122, 255
                                 BCOLOR(65, 105, 255, 191),
                                 -280, //263
                                 500, //225
                                 50,
                                 BRIGHT,
                                 BVISIBLE,
                                 true
                                );
    }

    add_element_to_render_queue(NULL, 280, 250, 0, RCOLOR(0, 0, 0, 255), update_score);
    add_element_to_render_queue(NULL, 280, 300, 0, RCOLOR(0, 0, 0, 255), update_survivaltime);
}

/*----------------------------------------------------------------------------------------------------------*/

void gameover_cleanup(void)
{
    remove_element_from_button_list(&quit);
    quit = NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void exit_gameover(GDATAPTR game)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "QUITTOMENU");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
