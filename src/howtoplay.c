#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <commons.h>
#include <buttons.h>
#include <howtoplay.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR back = NULL;

/*----------------------------------------------------------------------------*/

void howtoplay(void)
{
    GDATAPTR game = get_game_data();
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

void howtoplay_cleanup(void)
{
    remove_element_from_button_list(&back);
    back = NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void exit_howtoplay(GDATAPTR game)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "BACK");
    currentptr->bdata.limit = -280;
    currentptr->bdata.aflags = BLEFT;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
