#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <chipmunk/chipmunk.h>
#include <commons.h>
#include <buttons.h>
#include <sprites.h>
#include <physcol.h>
#include <inits.h>

/*----------------------------------------------------------------------------*/

// Initializes the base image list, where all images are grabbed by SPRITE structures
_Bool init_base_images(void)
{
    SIMAGEPTR ptri;
    String images[27] = {"amean_1.png", "amean_2.png", "amean_3.png", "arm.png", "background_day.png",
                         "brick_wallx2.png", "clamp_close.png", "clamp_open.png", "cloud.png", "flying_fist.png",
                         "ground_block.png", "lazer.png", "plant_1.png", "plant_2.png", "raw_1.png", "raw_2.png",
                         "spikes.png", "steel_wall.png", "stem.png", "stickfigure_attack_run.png",
                         "stickfigure_attack_jump.png", "stickfigure_attack_slide.png", "stickfigure_dead.png",
                         "stickfigure_lives.png", "stickfigure_move_1.png", "stickfigure_move_2.png", "stickfigure_slide.png"};

    String labels[27] = {"AMEAN_1", "AMEAN_2", "AMEAN_3", "ARM", "BACKGROUND_DAY", "BRICK_WALL", "CLAMP_CLOSE",
                         "CLAMP_OPEN", "CLOUD", "FLYING_FIST", "GROUND_BLOCK", "LAZER", "PLANT_1", "PLANT_2", "RAW_1",
                         "RAW_2", "SPIKES", "STEEL_WALL", "STEM", "STICKFIGURE_ATTACK_RUN", "STICKFIGURE_ATTACK_JUMP",
                         "STICKFIGURE_ATTACK_SLIDE", "STICKFIGURE_DEAD", "STICKFIGURE_LIVES", "STICKFIGURE_MOVE_1",
                         "STICKFIGURE_MOVE_2", "STICKFIGURE_SLIDE"};

    ptri = create_base_image_list(labels, images, sizeof(labels)/sizeof(*labels));

    if(ptri == NULL) return false;

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// Initializes the main sprites; stickman, background etc.
_Bool init_core_sprites(void)
{
    if(!init_base_images()) return false;

    SPRITESPTR ptrs;

    String jlabels[1] = {"BACKGROUND_DAY"};
    ptrs = create_new_sprite("BACKGROUND",
                             jlabels,
                             sizeof(jlabels)/sizeof(*jlabels),
                             NULL,
                             NULL,
                             NULL,
                             0,
                             "BACKGROUND_DAY",
                             0,
                             0,
                             0,
                             0,
                             0,
                             MNONE,
                             true
                            );
    if(ptrs == NULL) return false;

    String llabels[1] = {"GROUND_BLOCK"};
    ptrs = create_new_sprite("GROUND",
                             llabels,
                             sizeof(llabels)/sizeof(*llabels),
                             NULL,
                             NULL,
                             NULL,
                             0,
                             "GROUND_BLOCK",
                             0,
                             510,
                             3,
                             0,
                             0,
                             MNONE,
                             true
                            );
    if(ptrs == NULL) return false;

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool game_start_init(void)
{
    SPRITESPTR ptrs;

       String ilabels[8] = {"STICKFIGURE_ATTACK_RUN", "STICKFIGURE_ATTACK_JUMP", "STICKFIGURE_ATTACK_SLIDE",
                            "STICKFIGURE_DEAD", "STICKFIGURE_LIVES", "STICKFIGURE_MOVE_1", "STICKFIGURE_MOVE_2",
                            "STICKFIGURE_SLIDE"};
    ptrs = create_new_sprite("STICKMAN",
                             ilabels,
                             sizeof(ilabels)/sizeof(*ilabels),
                             NULL,
                             NULL,
                             NULL,
                             0,
                             "STICKFIGURE_MOVE_1",
                             50,
                             150,
                             3,
                             350,
                             0,
                             MNONE,
                             true
                            );
    if(ptrs == NULL) return false;
    if(create_physics_object(ptrs, 60, 1, 0.85f, 1, "STICKMAN") == NULL) return false;

    String klabels[1] = {"CLOUD"};
    ptrs = create_new_sprite("CLOUD",
                             klabels,
                             sizeof(klabels)/sizeof(*klabels),
                             NULL,
                             NULL,
                             NULL,
                             0,
                             "CLOUD",
                             263,
                             225,
                             3,
                             0,
                             0,
                             MNONE,
                             true
                            );
    if(ptrs == NULL) return false;

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// Initializes the startup buttons
_Bool init_buttons(void)
{
    if(!init_button_images()) return false;

    BUTTONPTR ptrb;
    GDATAPTR game = get_game_data();

    ptrb = create_new_button("STARTBUTTON",
                             "DEFAULT",
                             "NEW GAME",
                             game->b_font,
                             BCOLOR(255, 255, 255, 255), //80, 112/122, 255
                             BCOLOR(65, 105, 255, 191),
                             -280, //263
                             125, //225
                             263,
                             BRIGHT,
                             BVISIBLE,
                             true
                            );

    if(ptrb == NULL) return false;

    ptrb = create_new_button("HOWTOPLAYBUTTON",
                             "DEFAULT",
                             "HOW TO PLAY",
                             game->b_font,
                             BCOLOR(255, 255, 255, 255), //80, 112, 255
                             BCOLOR(65, 105, 255, 191),
                             -290, //263
                             200, //225
                             263,
                             BRIGHT,
                             BVISIBLE,
                             true
                            );

    if(ptrb == NULL) return false;

    ptrb = create_new_button("OPTIONSBUTTON",
                             "DEFAULT",
                             "OPTIONS",
                             game->b_font,
                             BCOLOR(255, 255, 255, 255), //80, 112, 255
                             BCOLOR(65, 105, 255, 191),
                             -300, //263
                             275, //225
                             263,
                             BRIGHT,
                             BVISIBLE,
                             true
                            );

    if(ptrb == NULL) return false;

    ptrb = create_new_button("HIGHSCOREBUTTON",
                             "DEFAULT",
                             "HIGH SCORE",
                             game->b_font,
                             BCOLOR(255, 255, 255, 255), //80, 112, 255
                             BCOLOR(65, 105, 255, 191),
                             -310, //263
                             350, //225
                             263,
                             BRIGHT,
                             BVISIBLE,
                             true
                            );

    if(ptrb == NULL) return false;

    ptrb = create_new_button("EXITBUTTON",
                             "DEFAULT",
                             "Exit",
                             game->b_font,
                             BCOLOR(255, 255, 255, 255), //80, 112, 255
                             BCOLOR(65, 105, 255, 191),
                             -320, //263
                             425, //225
                             263,
                             BRIGHT,
                             BVISIBLE,
                             true
                            );

    if(ptrb == NULL) return false;

    set_standard_button_animation(BSHIFTRIGHT);

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// Initializes the button image list, where all BUTTON structures grab the button images from
_Bool init_button_images(void)
{
    BIMAGESPTR ptrbi;

    char *labels[1] = {"DEFAULT"};
    char *images[1] = {"button_n.png"};

    ptrbi = create_new_button_image_list(labels, images, sizeof(labels)/sizeof(*labels));

    if(ptrbi == NULL) return false;
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool init_chipmunk(void)
{
    cpSpace *space = cpSpaceNew();
    // Define a gravity vector
    cpSpaceSetGravity(space, cpv(0, 600));
    cpSpaceSetIterations(space, 10);
    //space->elasticIterations = 10;
    if(set_global_cpSpace(space) == NULL) return false;
    //float width, height;

    SPRITESPTR ground = search_sprite_list_for_element("GROUND");
    //width = ground->sdata.currentimg->width;
    //height = ground->sdata.currentimg->height;
    cpBody *staticBody = cpBodyNewStatic();
    cpBodySetPosition(staticBody, cpv(0+res_width/2, 0+res_height/2));
    cpShape *floorShape = cpSegmentShapeNew(staticBody,
                                            cpv(0-res_width/2, 0+res_height/2-(res_height-ground->sdata.y)),
                                            cpv(0+res_width, 0+res_height/2-(res_height-ground->sdata.y)),
                                            0);
    cpShapeSetElasticity(floorShape, 0.5f);
    cpShapeSetFriction(floorShape, 0.2f);
    cpShapeSetCollisionType(floorShape, 0);
    cpShapeSetUserData(floorShape, "FLOORSHAPE");
    cpSpaceAddShape(space, floorShape);

    cpShape *leftShape = cpSegmentShapeNew(staticBody,
                                           cpv(0-res_width/2, 0+res_height/2),
                                           cpv(0-res_width/2, 0-res_height/2),
                                           0);
    cpShapeSetElasticity(leftShape, 0.5f);
    cpShapeSetFriction(leftShape, 0.2f);
    cpShapeSetCollisionType(leftShape, 0);
    cpShapeSetUserData(leftShape, "LEFTSHAPE");
    cpSpaceAddShape(space, leftShape);

    cpShape *rightShape = cpSegmentShapeNew(staticBody,
                                            cpv(0+res_width/2, 0+res_height/2),
                                            cpv(0+res_width/2, 0-res_height/2),
                                            0);
    cpShapeSetElasticity(rightShape, 0.5f);
    cpShapeSetFriction(rightShape, 0.2f);
    cpShapeSetCollisionType(rightShape, 0);
    cpShapeSetUserData(rightShape, "RIGHTSHAPE");
    cpSpaceAddShape(space, rightShape);

    cpShape *topShape = cpSegmentShapeNew(staticBody,
                                          cpv(0-res_width/2, 0-res_height/2),
                                          cpv(0+res_width/2, 0-res_height/2),
                                          0);
    cpShapeSetElasticity(topShape, 0.5f);
    cpShapeSetFriction(topShape, 0.2f);
    cpShapeSetCollisionType(topShape, 0);
    cpShapeSetUserData(topShape, "TOPSHAPE");
    cpSpaceAddShape(space, topShape);

    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
