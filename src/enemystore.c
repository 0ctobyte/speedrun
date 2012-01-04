#include <allegro5/allegro.h>
#include <chipmunk/chipmunk.h>
#include <sprites.h>
#include <physcol.h>
#include <enemystore.h>

/*----------------------------------------------------------------------------*/

static int total_enemies = 0, ameans = 0, bwall = 0, clamp = 0, swall = 0, fist = 0, spikes = 0, raw = 0, plants = 0;

/*----------------------------------------------------------------------------------------------------------*/

int rand_int(int max)
{
    srand((unsigned int)clock() * rand());
    return (rand() % max) + 1;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR create_new_enemy(char *enemy_type)
{
    SPRITESPTR enemy = NULL;
    if(strcmp(enemy_type, "AMEAN") == 0)
    {
        ameans++;
        char *labels[3] = {"AMEAN_1", "AMEAN_2", "AMEAN_3"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "AMEAN_1",
                                  805,
                                  450,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "BRICK_WALL") == 0)
    {
        bwall++;
        char *labels[1] = {"BRICK_WALL"};
        int y = 450;

        if(rand_int(2) == 1)
            y = 400;

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "BRICK_WALL",
                                  805,
                                  y,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "CLAMP") == 0)
    {
        clamp++;
        char *labels[3] = {"CLAMP_OPEN", "CLAMP_CLOSE", "ARM"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "CLAMP_OPEN",
                                  805,
                                  0,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "STEEL_WALL") == 0)
    {
        swall++;
        char *labels[1] = {"STEEL_WALL"};
        int y = 450;

        if(rand_int(2) == 1)
            y = 380;

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "STEEL_WALL",
                                  805,
                                  y,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "FLYING_FIST") == 0)
    {
        fist++;
        char *labels[1] = {"FLYING_FIST"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "FLYING_FIST",
                                  805,
                                  410,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "SPIKES") == 0)
    {
        spikes++;
        char *labels[1] = {"SPIKES"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "SPIKES",
                                  805,
                                  475,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "RAW") == 0)
    {
        raw++;
        char *labels[3] = {"RAW_1", "RAW_2", "LAZER"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "RAW_1",
                                  805,
                                  465,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }
    else if(strcmp(enemy_type, "PLANT") == 0)
    {
        plants++;
        char *labels[3] = {"PLANT_1", "PLANT_2", "STEM"};

        enemy = create_new_sprite(enemy_type,
                                  labels,
                                  sizeof(labels)/sizeof(*labels),
                                  NULL,
                                  NULL,
                                  NULL,
                                  0,
                                  "PLANT_2",
                                  805,
                                  465,
                                  3,
                                  0,
                                  0,
                                  MNONE,
                                  true
                                );
        if(enemy == NULL) return false;
        if(create_physics_object(enemy, 60, 0.1f, 0.85f, 2, enemy) == NULL) return false;
    }

    total_enemies = ameans + bwall + clamp + swall + fist + spikes + plants + raw;
    cpSpaceResizeActiveHash(get_global_cpSpace(), 80.0, total_enemies+1*10);


    return enemy;
}

/*----------------------------------------------------------------------------------------------------------*/

void remove_enemy(SPRITESPTR sprite)
{
    if(strcmp(sprite->slabel, "AMEAN") == 0)
        ameans--;
    else if(strcmp(sprite->slabel, "BRICK_WALL") == 0)
        bwall--;
    else if(strcmp(sprite->slabel, "CLAMP") == 0)
        clamp--;
    else if(strcmp(sprite->slabel, "STEEL_WALL") == 0)
        swall--;
    else if(strcmp(sprite->slabel, "FLYING_FIST") == 0)
        fist--;
    else if(strcmp(sprite->slabel, "SPIKES") == 0)
        spikes--;
    else if(strcmp(sprite->slabel, "RAW") == 0)
        raw--;
    else if(strcmp(sprite->slabel, "PLANT") == 0)
        plants--;
    remove_physics_object(sprite);
    remove_element_from_sprite_list_ptr(sprite);
}

/*----------------------------------------------------------------------------------------------------------*/

void remove_all_enemies_of_type(char *enemy_label)
{
    SPRITESPTR sprite;
    if(strcmp(enemy_label, "AMEAN") == 0)
    {
        while((sprite = search_sprite_list_for_element("AMEAN")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        ameans = 0;
    }
    else if(strcmp(enemy_label, "BRICK_WALL") == 0)
    {
        while((sprite = search_sprite_list_for_element("BRICK_WALL")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        bwall = 0;
    }
    else if(strcmp(enemy_label, "CLAMP") == 0)
    {
        while((sprite = search_sprite_list_for_element("CLAMP")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        clamp = 0;
    }
    else if(strcmp(enemy_label, "STEEL_WALL") == 0)
    {
        while((sprite = search_sprite_list_for_element("STEEL_WALL")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        swall = 0;
    }
    else if(strcmp(enemy_label, "FLYING_FIST") == 0)
    {
        while((sprite = search_sprite_list_for_element("FLYING_FIST")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        fist = 0;
    }
    else if(strcmp(enemy_label, "SPIKES") == 0)
    {
        while((sprite = search_sprite_list_for_element("SPIKES")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        spikes = 0;
    }
    else if(strcmp(enemy_label, "RAW") == 0)
    {
        while((sprite = search_sprite_list_for_element("RAW")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        raw = 0;
    }
    else if(strcmp(enemy_label, "PLANT") == 0)
    {
        while((sprite = search_sprite_list_for_element("PLANT")) != NULL)
        {
            remove_physics_object(sprite);
            remove_element_from_sprite_list_ptr(sprite);
        }
        plants = 0;
    }
}

/*----------------------------------------------------------------------------------------------------------*/

void remove_all_enemies(void)
{
    SPRITESPTR sprite;
    while((sprite = search_sprite_list_for_element("AMEAN")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("BRICK_WALL")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("CLAMP")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("STEEL_WALL")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("FLYING_FIST")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("SPIKES")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("RAW")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    while((sprite = search_sprite_list_for_element("PLANT")) != NULL)
    {
        remove_physics_object(sprite);
        remove_element_from_sprite_list_ptr(sprite);
    }
    total_enemies = 0;
    ameans = 0;
    bwall = 0;
    clamp = 0;
    swall = 0;
    fist = 0;
    spikes = 0;
    raw = 0;
    plants = 0;
}

/*----------------------------------------------------------------------------------------------------------*/


//    /**
//      *@}
//      */
