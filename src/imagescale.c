#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <commons.h>
#include <imagescale.h>

/*----------------------------------------------------------------------------*/

void scale(int init_width, int init_height)
{
    ALLEGRO_TRANSFORM trans;
    float width = al_get_display_width(get_game_data()->display);
    float height = al_get_display_height(get_game_data()->display);
    al_identity_transform(&trans);
    al_scale_transform(&trans, width/init_width, height/init_height);
    al_use_transform(&trans);
}

/*----------------------------------------------------------------------------*/

void nscale(void)
{
    ALLEGRO_TRANSFORM trans;
    al_identity_transform(&trans);
    al_scale_transform(&trans, 1.0, 1.0);
    al_use_transform(&trans);
}

/*----------------------------------------------------------------------------*/
