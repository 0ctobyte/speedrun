#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include <chipmunk/chipmunk.h>
#include <stdio.h>
#include <commons.h>
#include <imagescale.h>
#include <progressbar.h>
#include <inits.h>
#include <keyboard.h>
#include <mouse.h>
#include <buttons.h>
#include <eventhandler.h>
#include <sprites.h>
#include <maingame.h>
#include <render.h>
#include <physcol.h>
#include <options.h>
#include <main.h>

/*----------------------------------------------------------------------------*/

static GDATAPTR data;

/*----------------------------------------------------------------------------*/

// TODO: remove init_core_sprites, put instead ini_base_images.
// Game entry point, calls all initialization functions before calling main_loop
int main(int argc, char** argv)
{
    // Declare main struct containing the important data
    data = (GDATAPTR)malloc(sizeof(GDATA));

    // Initialize Allegro 5 and addon routines
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    PHYSFS_init(argv[0]);

    // Initialize the core game data structure
    if(!data_init()) exit(EXIT_FAILURE);

    // Creates a player sprite
    if(!init_core_sprites()) exit(EXIT_FAILURE);

    // Initializes the buttons
    if(!init_buttons()) exit(EXIT_FAILURE);

    // Initializes the physics and collision detection
    if(!init_chipmunk()) exit(EXIT_FAILURE);

    // Create the progress bar
    loader();

    // Enters the main loop, where everything happens
    main_loop();

    // Cleanup before exit
    cleanup(data);

    // Return 0 before exit
    return 0;
}

/*----------------------------------------------------------------------------------------------------------*/

// Initializes the the GDATA struct
_Bool data_init(void)
{
    // Create a window to display things on: 800x600 pixels
    al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_OPENGL);
    al_set_new_display_refresh_rate(60);
    data->display = al_create_display(res_width, res_height);
    if(data->display == NULL)
    {
        al_show_native_message_box(data->display, "Error!", "Display Error:", "Failed to create window!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Sets the physfs file interface to be used for loading files
    al_set_physfs_file_interface();
    PHYSFS_mount("images", NULL, 1);
    PHYSFS_mount("fonts", NULL, 1);
    PHYSFS_mount("buttons", NULL, 1);

    // Well, looks like we're gonna have to draw our own mouse *SIGH*
    al_hide_mouse_cursor(data->display);
    data->cursor = al_load_bitmap("cursor_darkgrey.png");
    if(data->cursor == NULL)
    {
        al_show_native_message_box(data->display, "Error!", "Cursor Error:", "Failed to locate cursor!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Set the title of the window
    al_set_window_title(data->display, "SpeedRun!");

    // Sets the window's icon
    data->icon = al_load_bitmap("speedrundisplayicon.png");
    if(data->icon == NULL)
    {
        al_show_native_message_box(data->display, "Error!", "Icon Error:", "Failed to locate icon!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }
    al_set_display_icon(data->display, data->icon);

    // Load a font
    data->font = al_load_ttf_font("times.ttf", 25, 0);
    data->b_font = al_load_ttf_font("impact.ttf", 25, 0);
    if(data->font == NULL || data->b_font == NULL)
    {
        al_show_native_message_box(data->display, "Error!", "Font Error:", "Failed to load font!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Make and set a color to draw with
    data->text_color = al_map_rgba(80, 112, 255, 255);

    // Set background color
    data->background_color = al_map_rgba(0, 0, 0, 0);

    // Install the keyboard handler
    if(!al_install_keyboard())
    {
        al_show_native_message_box(data->display, "Error!", "Keyboard Error:", "Failed to install keyboard handler!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Install the mouse handler
    if(!al_install_mouse())
    {
        al_show_native_message_box(data->display, "Error!", "Mouse Error:", "Failed to install mouse handler!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return false;
    }

    // Detect and set refresh rate
    int refresh_rate = al_get_display_refresh_rate(data->display);
    if(refresh_rate == 0)
    {
        refresh_rate = 60;
    }

    // Install timer with refresh rate
    data->timer = al_create_timer(1.0/refresh_rate);
    if(data->timer == NULL)
    {
        al_show_native_message_box(data->display, "Error!", "Timer Error:", "Failed to initialize timer!", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);
        return 1;
    }
    al_start_timer(data->timer);


    // Start the event queues to handle keyboard input, mouse input, display input and timer input
    data->queue = al_create_event_queue();
    al_register_event_source(data->queue, (ALLEGRO_EVENT_SOURCE*)data->timer);
    data->queue2 = al_create_event_queue();
    al_register_event_source(data->queue2, al_get_keyboard_event_source());
    al_register_event_source(data->queue2, (ALLEGRO_EVENT_SOURCE*)data->display);
    al_register_event_source(data->queue2, al_get_mouse_event_source());

    // Set the quit and gamestarted flags to false initially
    data->exit = false;
    data->gamestarted = false;
    data->options = false;
    data->highscores = false;
    data->howtoplay = false;

    al_start_timer(data->timer);

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// The main Allegro loop, all input handling, animation and drawing is done here
_Bool main_loop(void)
{
    // Flag for drawing
    _Bool needredraw = true;
    // Declare primitive data types
    float old_time = 0.0, current_time = 0, dt = 0;

    while(!data->exit)
    {
        if(needredraw && al_event_queue_is_empty(data->queue) && al_event_queue_is_empty(data->queue2))
        {
            // Clear, draw, flip
            al_clear_to_color(data->background_color);
            render();
            if(get_fps_status())
                al_draw_textf(data->font, data->text_color, 0, res_height-30, 0, "fps: %.2f", 1/dt);
            al_flip_display();
            needredraw = false;
        }

        // Block until an event enters the queue
        al_wait_for_event(data->queue, &(data->event));

        while(!al_event_queue_is_empty(data->queue2))
        {
            al_get_next_event(data->queue2, &(data->event2));
            switch(data->event2.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                {
                    // If x button is pressed on window
                    data->exit = true;
                    data->gamestarted = false;
                }
                break;
                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                {
                    al_acknowledge_resize(data->event2.display.source);
                    scale(res_width, res_height);
                }
                break;
                case ALLEGRO_EVENT_MOUSE_AXES:
                {
                    // Stores the mouse's new position and change in position
                    mouseaxes(&(data->event2.mouse));
                }
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                {
                    // Stores the mouse button pressed
                    mousedown(&(data->event2.mouse));
                }
                break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                {
                    // Stores the mouse button released
                    mouseup(&(data->event2.mouse));
                }
                break;
                case ALLEGRO_EVENT_KEY_DOWN:
                {
                    // Stores keydown keycode into keycode array for processing
                    keydown(&(data->event2.keyboard));
                }
                break;
                case ALLEGRO_EVENT_KEY_UP:
                {
                    // Stores keycode into keycode array for processing
                    keyup(&(data->event2.keyboard));
                }
                break;
                default:
                break;
            }
        }

        switch (data->event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            {
                // Determine the change in time between frames, in seconds
				current_time = al_current_time();
				dt = current_time-old_time;

				// If the computer lags for some reason, don't penalize the player
				// Cap dt at 0.5 seconds
				if(dt > 0.25)
				{
                    dt = 0.25;
				}

				// Handle Mouse and Keyboard events and Button Events
				buttoncheck(&buttonhandler, data);
				keycheck(&keyhandler, data);
				mousecheck(&mousehandler, data);
				keyupdate();
                mouseupdate();

                // Check if data->quit has been set before updating and drawing
                if(data->exit) break;

                // Update the game, always
                update();

                // Skip drawing frames if computer lags
                if(current_time - data->event.timer.timestamp <= 1.0/al_get_display_refresh_rate(data->display))
                {
                    needredraw = true;
                }

				// Make the time at this frame the old time, for the next frame
				old_time = current_time;
            }
            break;
            default:
            break;
        }
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// Returns a pointer to the main game struct, GDATA *data
GDATAPTR get_game_data(void)
{
    return data;
}

/*----------------------------------------------------------------------------------------------------------*/

void loader(void)
{
    ALLEGRO_BITMAP *bg = al_load_bitmap("background_day.png");
    PROGRESSBARPTR pb1 = create_new_progress_bar("pb1", 243, 275, 300, 50, 10, 10, al_map_rgba(0, 0, 0, 127),
                                                 al_map_rgba(0, 0, 255, 127), 5, true);
    while(pb1->bar_width < pb1->width)
    {
        pb1->counter++;
        al_acknowledge_resize(get_game_data()->display);
        scale(res_width, res_height);
        al_clear_to_color(data->background_color);
        al_draw_bitmap(bg, 0, 0, 0);
        render_progress_bars();
        al_flip_display();
        if(pb1->counter == 3)
        {
            pb1->bar_width += pb1->increment;
            pb1->counter = 0;
        }
    }
    al_destroy_bitmap(bg);
    remove_element_from_progress_bar_list("pb1");
}

/*----------------------------------------------------------------------------------------------------------*/

void cleanup(GDATAPTR game)
{
    empty_render_queue(get_first_element_from_render_queue());
    empty_sprite_list(get_first_element_from_sprite_list());
    empty_base_image_list(get_first_element_from_base_image_list());
    empty_button_list(get_first_element_from_button_list());
    empty_button_image_list(get_first_element_from_button_image_list());
    empty_progress_bar_list(get_first_element_from_progress_bar_list());
    al_destroy_event_queue(game->queue);
    al_destroy_timer(game->timer);
    al_destroy_font(game->font);
    al_destroy_font(game->b_font);
    al_destroy_bitmap(game->icon);
    al_destroy_bitmap(game->cursor);
    PHYSFS_deinit();
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
