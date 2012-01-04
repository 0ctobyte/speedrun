#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <chipmunk/chipmunk.h>
#include <stdio.h>
#include <commons.h>
#include <keyboard.h>
#include <mouse.h>
#include <buttons.h>
#include <sprites.h>
#include <maingame.h>
#include <options.h>
#include <howtoplay.h>
#include <highscores.h>
#include <pause.h>
#include <gameover.h>
#include <render.h>
#include <inits.h>
#include <eventhandler.h>

/*----------------------------------------------------------------------------*/

static _Bool mpressed = false;

/*----------------------------------------------------------------------------*/

// Checks for keyboard input, called once every frame
void* keyhandler(String key, void *data)
{
    GDATAPTR game = (GDATAPTR)data;
	if(game->gamestarted)
	{
		if((key[ALLEGRO_KEY_W] & KEYNEW) || (key[ALLEGRO_KEY_UP] & KEYNEW))
		{
			set_anim_flags_on_sprite(search_sprite_list_for_element("STICKMAN"),
				MUP);
		}
		if((key[ALLEGRO_KEY_S] & KEYNEW) || (key[ALLEGRO_KEY_DOWN] & KEYNEW))
		{
			set_anim_flags_on_sprite(search_sprite_list_for_element("STICKMAN"),
				MDOWN);
		}
		if((key[ALLEGRO_KEY_SPACE] & KEYNEW))
		{
			set_anim_flags_on_sprite(search_sprite_list_for_element("STICKMAN"),
				MATTACK);
		}
	}
	if((key[ALLEGRO_KEY_ESCAPE] & KEYPRESSED))
	{
	    game->exit = true;
	    game->gamestarted = false;
	}
	if((key[ALLEGRO_KEY_M] & KEYNEW))
	{
        return_to_main_menu(game);
	}
	if((key[ALLEGRO_KEY_P] & KEYNEW))
	{
	    if(game->paused)
	    {
            exit_pause(game);
            mpressed = true;
	    }
	    else
	    {
            game->paused = true;
	    }
	}
	return NULL;
}


/*----------------------------------------------------------------------------------------------------------*/

// Checks for mouse input, called once every frame
void* mousehandler(MOUSE* mouse_s, void *data)
{
    MOUSE *mouse = (MOUSE*)mouse_s;
    GDATAPTR game = (GDATAPTR)data;

    if((mouse->button & MOUSE_L_NEW) && game->gamestarted)
    {
        SPRITESPTR sprite = search_sprite_list_for_element("BRICK_WALL");
        SPRITESPTR fsprite = sprite;
        if(sprite != NULL)
        {
            do
            {
                if(strcmp(sprite->slabel, "BRICK_WALL") == 0)
                    set_anim_flags_on_sprite(sprite, MDOWN);
                sprite = sprite->nextsprite;
            } while(sprite != fsprite);
        }
    }
//    if((mouse->button & MOUSE_R))
//    {
//        set_anim_flags_on_sprite(search_sprite_list_for_element("STICKMAN"), MRIGHT);
//    }
//    if(mouse->dz > 0)
//    {
//        set_anim_flags_on_sprite(search_sprite_list_for_element("STICKMAN"), MRIGHT);
//    }

    return NULL;
}


/*----------------------------------------------------------------------------------------------------------*/

// Handles button events, may be called once every frame
void* buttonhandler(BUTTONPTR button, void* data, int type)
{
    typedef enum button_pressed {
        NONE,
        STARTB,
        HOWTOPLAYB,
        OPTIONSB,
        HIGHSCOREB,
        EXITB
    } BPRESSED;

    GDATAPTR game = (GDATAPTR)data;
    ALLEGRO_DISPLAY *display = game->display;
    static BPRESSED bpressed = NONE;

    if(strcmp(button->blabel, "STARTBUTTON") == 0 && type == BPRESSED_CALL)
    {
        game_start_init();
        execute_on_button_press();
        bpressed = STARTB;
    }
    if(strcmp(button->blabel, "HOWTOPLAYBUTTON") == 0 && type == BPRESSED_CALL)
    {
        execute_on_button_press();
        bpressed = HOWTOPLAYB;
    }
    if(strcmp(button->blabel, "OPTIONSBUTTON") == 0 && type == BPRESSED_CALL)
    {
        execute_on_button_press();
        bpressed = OPTIONSB;
    }
    if(strcmp(button->blabel, "HIGHSCOREBUTTON") == 0 && type == BPRESSED_CALL)
    {
        execute_on_button_press();
        bpressed = HIGHSCOREB;
    }
    if(strcmp(button->blabel, "EXITBUTTON") == 0 && type == BPRESSED_CALL)
    {
        execute_on_button_press();
        bpressed = EXITB;
    }
    if(strcmp(button->blabel, "FULLSCREEN") == 0 && type == BPRESSED_CALL)
    {
        (al_get_display_flags(display) & ALLEGRO_FULLSCREEN_WINDOW) ?
        al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, false), 
        al_resize_display(display, 800, 600) :
        al_toggle_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, true);

        if(strcmp(button->btext.text, "FULLSCREEN") == 0)
            button->btext.text = "WINDOWED";
        else
            button->btext.text = "FULLSCREEN";
    }
    if(strcmp(button->blabel, "FPS") == 0 && type == BPRESSED_CALL)
    {
        set_fps_status(!get_fps_status());

        if(strcmp(button->btext.text, "FPS COUNTER: ON") == 0)
            button->btext.text = "FPS COUNTER: OFF";
        else
            button->btext.text = "FPS COUNTER: ON";
    }
    if(strcmp(button->blabel, "BACK") == 0 && type == BPRESSED_CALL)
    {
        return_to_main_menu(game);
    }
    if(strcmp(button->blabel, "RESUME") == 0 && type == BPRESSED_CALL)
    {
        exit_pause(game);
        mpressed = true;
    }
    if(strcmp(button->blabel, "EXITGAME") == 0 && type == BPRESSED_CALL)
    {
        game->exit = true;
    }
    if(strcmp(button->blabel, "QUITTOMENU") == 0 && type == BPRESSED_CALL)
    {
        return_to_main_menu(game);
    }
    if(strcmp(button->blabel, "QUITTOMENUGO") == 0 && type == BPRESSED_CALL)
    {
        return_to_main_menu(game);
    }
    if(strcmp(button->blabel, "CLEAR") == 0 && type == BPRESSED_CALL)
    {
        set_bflags_on_button(button, BLRELEASED);
        remove_bflags_on_button(button, BLPRESSED);
        remove_bflags_on_button(button, BVISIBLE);
        clear_highscores();
    }
    if(type == CBANIMATION_CALL && (game->options || game->howtoplay || game->highscores || game->paused) && mpressed)
    {
        mpressed = false;
        if(game->paused)
	    {
	        pause_cleanup();
	        game->gamestarted = true;
	        game->paused = false;
	    }
	    else
	    {
            execute_on_M_press();
            options_cleanup();
            howtoplay_cleanup();
            highscores_cleanup();
            gameover_cleanup();

            game->gamestarted = false;
            game->exit = false;
            game->options = false;
            game->highscores = false;
            game->howtoplay = false;
	    }
    }
    if(type == CBANIMATION_CALL && bpressed != NONE)
    {
        BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
        currentptr = search_button_list_for_element(&firstptr, "STARTBUTTON");
        remove_bflags_on_button(currentptr, BVISIBLE);
        currentptr = search_button_list_for_element(&firstptr, "HOWTOPLAYBUTTON");
        remove_bflags_on_button(currentptr, BVISIBLE);
        currentptr = search_button_list_for_element(&firstptr, "OPTIONSBUTTON");
        remove_bflags_on_button(currentptr, BVISIBLE);
        currentptr = search_button_list_for_element(&firstptr, "HIGHSCOREBUTTON");
        remove_bflags_on_button(currentptr, BVISIBLE);
        currentptr = search_button_list_for_element(&firstptr, "EXITBUTTON");
        remove_bflags_on_button(currentptr, BVISIBLE);

        switch (bpressed)
        {
            case NONE: break;
            case STARTB: game->gamestarted = true; break;
            case HOWTOPLAYB: game->howtoplay = true; break;
            case OPTIONSB: game->options = true; break;
            case HIGHSCOREB: game->highscores = true; break;
            case EXITB: game->exit = true; break;
            default: bpressed = NONE; break;
        }
        bpressed = NONE;
    }
    return NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void execute_on_button_press(void)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "STARTBUTTON");
    currentptr->bdata.x = 263;
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "HOWTOPLAYBUTTON");
    currentptr->bdata.x = 263;
    currentptr->bdata.x += 10;
    currentptr->bdata.limit = 815;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "OPTIONSBUTTON");
    currentptr->bdata.x = 263;
    currentptr->bdata.x += 20;
    currentptr->bdata.limit = 825;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "HIGHSCOREBUTTON");
    currentptr->bdata.x = 263;
    currentptr->bdata.x += 30;
    currentptr->bdata.limit = 835;
    currentptr->bdata.aflags = BRIGHT;
    currentptr = search_button_list_for_element(&firstptr, "EXITBUTTON");
    currentptr->bdata.x = 263;
    currentptr->bdata.x += 40;
    currentptr->bdata.limit = 845;
    currentptr->bdata.aflags = BRIGHT;
}

/*----------------------------------------------------------------------------------------------------------*/

void execute_on_M_press(void)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "STARTBUTTON");
    currentptr->bdata.x = -280;
    currentptr->bdata.limit = 263;
    currentptr->bdata.aflags = BRIGHT;
    set_bflags_on_button(currentptr, BVISIBLE);
    currentptr = search_button_list_for_element(&firstptr, "HOWTOPLAYBUTTON");
    currentptr->bdata.x = -290;
    currentptr->bdata.limit = 263;
    currentptr->bdata.aflags = BRIGHT;
    set_bflags_on_button(currentptr, BVISIBLE);
    currentptr = search_button_list_for_element(&firstptr, "OPTIONSBUTTON");
    currentptr->bdata.x = -300;
    currentptr->bdata.limit = 263;
    currentptr->bdata.aflags = BRIGHT;
    set_bflags_on_button(currentptr, BVISIBLE);
    currentptr = search_button_list_for_element(&firstptr, "HIGHSCOREBUTTON");
    currentptr->bdata.x = -310;
    currentptr->bdata.limit = 263;
    currentptr->bdata.aflags = BRIGHT;
    set_bflags_on_button(currentptr, BVISIBLE);
    currentptr = search_button_list_for_element(&firstptr, "EXITBUTTON");
    currentptr->bdata.x = -320;
    currentptr->bdata.limit = 263;
    currentptr->bdata.aflags = BRIGHT;
    set_bflags_on_button(currentptr, BVISIBLE);
}

/*----------------------------------------------------------------------------------------------------------*/

void return_to_main_menu(GDATAPTR game)
{
    if(game->options)
    {
        exit_options(game);
        mpressed = true;
    }
    if(game->howtoplay)
    {
        exit_howtoplay(game);
        mpressed = true;
    }
    if(game->highscores)
    {
        exit_highscores(game);
        mpressed = true;
    }
    if(game->paused)
    {
        execute_on_M_press();
        maingame_cleanup();
        pause_cleanup();

        game->gamestarted = false;
        game->exit = false;
        game->options = false;
        game->howtoplay = false;
        game->paused = false;
    }
    if(game->gamestarted)
    {
        execute_on_M_press();
        maingame_cleanup();
        gameover_cleanup();

        game->gamestarted = false;
        game->exit = false;
        game->options = false;
        game->howtoplay = false;
        game->paused = false;
    }
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
