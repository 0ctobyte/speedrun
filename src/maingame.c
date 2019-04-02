#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <chipmunk/chipmunk.h>
#include <stdio.h>
#include <commons.h>
#include <sprites.h>
#include <render.h>
#include <physcol.h>
#include <progressbar.h>
#include <options.h>
#include <howtoplay.h>
#include <highscores.h>
#include <pause.h>
#include <gameover.h>
#include <enemystore.h>
#include <maingame.h>

/*----------------------------------------------------------------------------*/

static _Bool start = false;
static int lives = 3;
static int score = 0;
static int minutes = 0;
static int seconds = 0;
static char *survival_time = NULL;

/*----------------------------------------------------------------------------*/

// Updates all nescessary sprites, images, buttons etc.
void update(void)
{
    static _Bool called = false;
    GDATAPTR game = get_game_data();
    update_background();
    if(game->gamestarted && game->paused)
    {
        paused(score, survival_time, lives);
    }
    else if(lives == 0)
    {
        gameover(score, survival_time);
    }
    else if(game->gamestarted)
    {
        if(!called)
        {
            //cpSpaceResizeStaticHash(get_global_cpSpace(), 700.0, 4*10);
            cpCollisionHandler* c = cpSpaceAddCollisionHandler(get_global_cpSpace(), 1, 2);
            c->beginFunc = collision_begin;
            c = cpSpaceAddCollisionHandler(get_global_cpSpace(), 0, 2);
            c->beginFunc = collision_static_begin;
            c = cpSpaceAddCollisionHandler(get_global_cpSpace(), 0, 1);
            c->beginFunc = collision_static_begin;
            called = false;
        }
        logic();
        update_clouds();
        cpSpaceStep(get_global_cpSpace(), 1.0f/60.0f);
        cpSpaceEachBody(get_global_cpSpace(), &update_sprites, NULL);
        update_ground();
        update_lives();
        add_element_to_render_queue(NULL, 0, 0, 0, RCOLOR(0, 0, 0, 255), update_score);
        add_element_to_render_queue(NULL, 290, 0, 0, RCOLOR(0, 0, 0, 255), update_survivaltime);
    }
    else if(game->options)
    {
        options();
    }
    else if(game->howtoplay)
    {
        howtoplay();
    }
    else if(game->highscores)
    {
        highscores();
    }
}

/*----------------------------------------------------------------------------------------------------------*/

// Performs animations for the stickman and adds the sprites to the render queue
void update_stickman(void)
{
    SPRITESPTR stman = search_sprite_list_for_element("STICKMAN");
    SPRITESPTR ground = search_sprite_list_for_element("GROUND");
    float height = (search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_MOVE_1"))->height;
    float y = cpBodyGetPosition(cpShapeGetBody(stman->shape)).y-height/2;
    int cx = 0, cy = 0, nflags = 0;
    static _Bool up = false, down = false;
    ALLEGRO_COLOR color = RCOLOR(255, 255, 255, 255);

    if(!start)
    {
        //static int sx = 0;
        //static int sy = 0;
        if(fabs(y+height-ground->sdata.y) <= 1.f)
        {
            stman->sdata.anim_counter++;
        }
        stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_MOVE_1");
        if(stman->sdata.anim_counter >= 20)
        {
            stman->sdata.anim_counter = 0;
            cpShapeSetElasticity(stman->shape, 0.1f);
            cpShapeSetFriction(stman->shape, 0.9f);
            //sx = stman->shape->body->p.x;
            //sy = stman->shape->body->p.y;
            start = true;
        }
    }
    else if((stman->sdata.animflags & MUP) && !down)
    {
        if(y+height >= ground->sdata.y && !up)
        {
            cpBody* body = cpShapeGetBody(stman->shape);
            cpVect currentvel = cpBodyGetVelocity(body);
			cpBodySetVelocity(body, cpv(0, -stman->sdata.dy));
            cpVect newvel = cpBodyGetVelocity(body);
            cpBodySetVelocity(body, cpvadd(currentvel, newvel));
            up = true;
        }
        else if(y+height >= ground->sdata.y && up)
        {
           remove_anim_flags_on_sprite(stman, MUP);
           up = false;
        }
        stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_MOVE_1");
    }
    else if((stman->sdata.animflags & MDOWN))
    {
        down = true;
        static int dcounter = 0;
        dcounter++;
        if(dcounter > 65)
        {
            down = false;
            remove_anim_flags_on_sprite(stman, MDOWN);
            dcounter = 0;
        }
        stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_SLIDE");
        cy = 15;
    }
    else
    {
        stman->sdata.anim_counter++;
        if(stman->sdata.anim_counter < 5)
            stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_MOVE_1");
        else if(stman->sdata.anim_counter > 5 && stman->sdata.anim_counter < 10)
            stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_MOVE_2");
        else if(stman->sdata.anim_counter > 10)
            stman->sdata.anim_counter = 0;
    }

    if((stman->sdata.animflags & MATTACK))
    {
        static int counter = 0;
        counter++;
        if(counter > 44)
        {
            remove_anim_flags_on_sprite(stman, MATTACK);
            counter = 0;
        }
        if(up)
        {
            stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_ATTACK_JUMP");
        }
        else if(down)
        {
            stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_ATTACK_SLIDE");
            cy = 20;
        }
        else
            stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_ATTACK_RUN");
    }
    if ((stman->sdata.animflags & MDAMAGED))
    {
        static int counter = 0;
        counter++;
        stman->sdata.currentimg = search_image_list_for_element(&stman->ifirstptr, "STICKFIGURE_DEAD");

        if(stman->sdata.x+stman->sdata.currentimg->width <= 0 || counter >= 60)
        {
            remove_anim_flags_on_sprite(stman, MDAMAGED);
            set_anim_flags_on_sprite(stman, MRECOVER);
            cpBody* body = cpShapeGetBody(stman->shape);
            cpBodySetPosition(body, cpv(70, cpBodyGetPosition(body).y));
            cpBodySetVelocity(body, cpvzero);
            counter = 0;
        }
    }
    if((stman->sdata.animflags & MRECOVER))
    {
        static int counter = 0;
        counter++;

        if(counter >= 15 && counter <= 30)
            color = RCOLOR(255, 255, 255, 105);
        else if(counter >= 45 && counter <= 60)
            color = RCOLOR(255, 255, 255, 105);
        else if(counter >= 75 && counter <= 90)
            color = RCOLOR(255, 255, 255, 105);
        else if(counter >= 105 && counter <= 120)
            color = RCOLOR(255, 255, 255, 105);

        if(counter >= 120)
        {
            counter = 0;
            remove_anim_flags_on_sprite(stman, MRECOVER);
        }
    }

    cpBody* body = cpShapeGetBody(stman->shape);
    cpVect position = cpBodyGetPosition(body);
    if((int)position.x != 50 && start && y+height >= ground->sdata.y && !(stman->sdata.animflags & MDAMAGED))
    {
        cpBodySetPosition(body, cpv(70, position.y));
    }

    position = cpBodyGetPosition(body);
    add_element_to_render_queue(stman->sdata.currentimg->image, stman->sdata.x+cx, stman->sdata.y+cy, nflags,
                                color, NULL);
    stman->sdata.x = position.x-stman->sdata.currentimg->width/2;
    stman->sdata.y = position.y-stman->sdata.currentimg->height/2;
}

/*----------------------------------------------------------------------------------------------------------*/

void update_lives(void)
{
    SPRITESPTR sprite = search_sprite_list_for_element("STICKMAN");
    SIMAGEPTR life = search_image_list_for_element(&(sprite->ifirstptr), "STICKFIGURE_LIVES");

    int x = res_width-life->width;
    int y = 0;

    for(int i = 0; i < lives; i++)
    {
        add_element_to_render_queue(life->image, x, y, 0, RCOLOR(255, 255, 255, 255), NULL);
        x -= life->width+10;
    }
}

/*----------------------------------------------------------------------------------------------------------*/

void update_score(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color)
{
    GDATAPTR game = get_game_data();
    al_draw_textf(game->font, color, x, y, nflags, "Score: %d", score);
}

/*----------------------------------------------------------------------------------------------------------*/

void collision_end_win(cpSpace *Space, void *obj, void *unused)
{
    cpShape *shape = (cpShape*)obj;
    SPRITESPTR sprite = (SPRITESPTR)cpShapeGetUserData(shape);

    if(strcmp(sprite->slabel, "AMEAN") == 0)
        score += 2;
    else if(strcmp(sprite->slabel, "PLANT") == 0)
        score += 6;
    else if(strcmp(sprite->slabel, "RAW") == 0)
        score += 10;

    remove_physics_object(sprite);
    remove_element_from_sprite_list_ptr(sprite);
}

/*----------------------------------------------------------------------------------------------------------*/

void collision_end_lose(cpSpace *Space, void *obj, void *unused)
{
    // cpShape *shape = (cpShape*)obj;
    // SPRITESPTR sprite = (SPRITESPTR)shape->data;
    SPRITESPTR stman = search_sprite_list_for_element("STICKMAN");
    lives--;
    set_anim_flags_on_sprite(stman, MDAMAGED);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_survivaltime(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color)
{
    static int counter = 0;
    GDATAPTR game = get_game_data();
    if(game->paused);
    else if(lives <= 0);
    else
        counter++;
    if(counter >= 60)
    {
        counter = 0;
        seconds++;
    }
    if(seconds >= 60)
    {
        seconds = 0;
        minutes++;
    }
	if(survival_time != NULL) free(survival_time);
    survival_time = (char*)malloc(7*sizeof(char));
    if(minutes < 10 && seconds < 10)
        sprintf(survival_time, "0%d:0%d", minutes, seconds);
    else if(minutes < 10)
        sprintf(survival_time, "0%d:%d", minutes, seconds);
    else if(seconds < 10)
        sprintf(survival_time, "%d:0%d", minutes, seconds);
    else
        sprintf(survival_time, "%d:%d", minutes, seconds);

    al_draw_textf(game->font, color,  x, y, nflags, "Survival Time: %s", survival_time);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_ameans(SPRITESPTR amean)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(amean->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    amean->sdata.anim_counter++;
    if(amean->sdata.anim_counter < 7)
    {
        amean->sdata.currentimg = search_image_list_for_element(&amean->ifirstptr, "AMEAN_1");
    }
    else if(amean->sdata.anim_counter > 7 && amean->sdata.anim_counter < 14)
    {
        amean->sdata.currentimg = search_image_list_for_element(&amean->ifirstptr, "AMEAN_2");
    }
    else if(amean->sdata.anim_counter > 14 && amean->sdata.anim_counter < 21)
    {
        amean->sdata.currentimg = search_image_list_for_element(&amean->ifirstptr, "AMEAN_3");
    }
    else if(amean->sdata.anim_counter > 21 && amean->sdata.anim_counter < 28)
    {
        amean->sdata.currentimg = search_image_list_for_element(&amean->ifirstptr, "AMEAN_2");
    }
    else if(amean->sdata.anim_counter > 28)
        amean->sdata.anim_counter = 0;

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(amean->sdata.currentimg->image, amean->sdata.x, amean->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    amean->sdata.x = position.x-amean->sdata.currentimg->width/2;
    amean->sdata.y = position.y-amean->sdata.currentimg->height/2;

    if(amean->sdata.x+amean->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, amean, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_brickwall(SPRITESPTR brickwall)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(brickwall->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(brickwall->sdata.currentimg->image, brickwall->sdata.x, brickwall->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    brickwall->sdata.x = position.x-brickwall->sdata.currentimg->width/2;
    brickwall->sdata.y = position.y-brickwall->sdata.currentimg->height/2;

    if((brickwall->sdata.animflags & MDOWN))
    {
        ALLEGRO_MOUSE_STATE mouse;
        al_get_mouse_state(&mouse);
        float x = brickwall->sdata.x;
        float y = brickwall->sdata.y;
        float width = brickwall->sdata.currentimg->width;
        float height = brickwall->sdata.currentimg->height;

        if((mouse.x >= x && mouse.x <= x+width) && (mouse.y >= y && mouse.y <= y+height))
        {
			cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, brickwall, NULL);
            score += 2;
        }
        remove_anim_flags_on_sprite(brickwall, MDOWN);
    }

    if(brickwall->sdata.x+brickwall->sdata.currentimg->width <= 0)
		cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, brickwall, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_clamp(SPRITESPTR clamp)
{
    int nflags = 0;
    SIMAGEPTR arm = search_image_list_for_element(&(clamp->ifirstptr), "ARM");

    cpBody* body = cpShapeGetBody(clamp->shape);
    if(clamp->sdata.x <= 200)
    {
        if(clamp->sdata.y+clamp->sdata.currentimg->height >= 470)
			cpBodySetVelocity(body, cpv(-180, 0));
        else
			cpBodySetVelocity(body, cpv(-180, 500));
    }
    else
	    cpBodySetVelocity(body, cpv(-180, 0));

    if((clamp->sdata.animflags & MATTACK))
        clamp->sdata.currentimg = search_image_list_for_element(&clamp->ifirstptr, "CLAMP_CLOSE");

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(clamp->sdata.currentimg->image, clamp->sdata.x, clamp->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    add_element_to_render_queue(arm->image, clamp->sdata.x, clamp->sdata.y-arm->height, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    add_element_to_render_queue(arm->image, clamp->sdata.x, clamp->sdata.y-arm->height-arm->height, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    clamp->sdata.x = position.x-clamp->sdata.currentimg->width/2;
    clamp->sdata.y = position.y-clamp->sdata.currentimg->height/2;

    if(clamp->sdata.x+clamp->sdata.currentimg->width <= 0)
		cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, clamp, NULL);
}


/*----------------------------------------------------------------------------------------------------------*/

void update_steelwall(SPRITESPTR steelwall)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(steelwall->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(steelwall->sdata.currentimg->image, steelwall->sdata.x, steelwall->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    steelwall->sdata.x = position.x-steelwall->sdata.currentimg->width/2;
    steelwall->sdata.y = position.y-steelwall->sdata.currentimg->height/2;

    if(steelwall->sdata.x+steelwall->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, steelwall, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_fist(SPRITESPTR fist)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(fist->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(fist->sdata.currentimg->image, fist->sdata.x, fist->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    fist->sdata.x = position.x-fist->sdata.currentimg->width/2;
    fist->sdata.y = position.y-fist->sdata.currentimg->height/2;

    if(fist->sdata.x+fist->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, fist, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_spikes(SPRITESPTR spikes)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(spikes->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(spikes->sdata.currentimg->image, spikes->sdata.x, spikes->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    spikes->sdata.x = position.x-spikes->sdata.currentimg->width/2;
    spikes->sdata.y = position.y-spikes->sdata.currentimg->height/2;

    if(spikes->sdata.x+spikes->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, spikes, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_raw(SPRITESPTR raw)
{
    int nflags = 0;

    cpBody* body = cpShapeGetBody(raw->shape);
	cpBodySetVelocity(body, cpv(-180, 0));

    if(raw->sdata.x <= 600 && raw->sdata.x >= 550)
    {
        set_anim_flags_on_sprite(raw, MATTACK);
    }

    add_element_to_render_queue(raw->sdata.currentimg->image, raw->sdata.x, raw->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);

    if((raw->sdata.animflags & MATTACK))
    {
        int x = raw->sdata.x-5*raw->sdata.anim_counter;
        int y = raw->sdata.y+30;
        SIMAGEPTR lazer = search_image_list_for_element(&(raw->ifirstptr), "LAZER");
        raw->sdata.anim_counter++;
        raw->sdata.currentimg = search_image_list_for_element(&(raw->ifirstptr), "RAW_2");
        if(x+lazer->width <= raw->sdata.x)
        {
            raw->sdata.currentimg = search_image_list_for_element(&(raw->ifirstptr), "RAW_1");
        }
        if(x+lazer->width <= 0)
        {
            raw->sdata.anim_counter = 0;
            remove_anim_flags_on_sprite(raw, MATTACK);
        }
        SPRITESPTR stman = search_sprite_list_for_element("STICKMAN");
        if((x >= stman->sdata.x && x <= stman->sdata.x+stman->sdata.currentimg->width) &&
           (y >= stman->sdata.y && y <= stman->sdata.y+stman->sdata.currentimg->height) &&
           !(stman->sdata.animflags & MDAMAGED) && !(stman->sdata.animflags & MRECOVER))
        {
            lives--;
            set_anim_flags_on_sprite(stman, MDAMAGED);
            raw->sdata.anim_counter = 0;
            remove_anim_flags_on_sprite(raw, MATTACK);
        }
        add_element_to_render_queue(lazer->image, x, y, nflags,
                                    RCOLOR(255, 255, 255, 255), NULL);
    }

    cpVect position = cpBodyGetPosition(body);
    raw->sdata.x = position.x-raw->sdata.currentimg->width/2;
    raw->sdata.y = position.y-raw->sdata.currentimg->height/2;

    if(raw->sdata.x+raw->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, raw, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_plant(SPRITESPTR plant)
{
    int nflags = 0;
    SIMAGEPTR stem = search_image_list_for_element(&(plant->ifirstptr), "STEM");

    cpBody* body = cpShapeGetBody(plant->shape);
    if(plant->sdata.x <= res_width/4)
    {
        if(plant->sdata.y+plant->sdata.currentimg->height <= 440)
        {
			cpBodySetVelocity(body, cpv(-180, 0));
            plant->sdata.currentimg = search_image_list_for_element(&(plant->ifirstptr), "PLANT_1");
        }
        else
			cpBodySetVelocity(body, cpv(-180, -200));
    }
    else
	    cpBodySetVelocity(body, cpv(-180, 0));

    cpVect position = cpBodyGetPosition(body);
    add_element_to_render_queue(plant->sdata.currentimg->image, plant->sdata.x, plant->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    add_element_to_render_queue(stem->image, plant->sdata.x, plant->sdata.y+plant->sdata.currentimg->height, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
    plant->sdata.x = position.x-plant->sdata.currentimg->width/2;
    plant->sdata.y = position.y-plant->sdata.currentimg->height/2;

    if(plant->sdata.x+plant->sdata.currentimg->width <= 0)
        cpSpaceAddPostStepCallback(get_global_cpSpace(), &remove_enemy, plant, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_clouds(void)
{
    SPRITESPTR clouds = search_sprite_list_for_element("CLOUD");
    int nflags = 0;
    static int m = -1;

    clouds->sdata.x += m*clouds->sdata.dx;
    if(clouds->sdata.x+clouds->sdata.currentimg->width < 0)
    {
       clouds->sdata.y = rand_int(res_height-90-clouds->sdata.currentimg->height);
       m *= -1;
    }
    if(clouds->sdata.x > res_width)
    {
        clouds->sdata.y = rand_int(res_height-90-clouds->sdata.currentimg->height);
        m *= -1;
    }
    add_element_to_render_queue(clouds->sdata.currentimg->image, clouds->sdata.x, clouds->sdata.y, nflags,
                                RCOLOR(255, 255, 255, 255), NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_ground(void)
{
    SPRITESPTR ground = search_sprite_list_for_element("GROUND");
    if(start)
    {
        ground->sdata.x -= ground->sdata.dx;
        add_element_to_render_queue(ground->sdata.currentimg->image, ground->sdata.x, ground->sdata.y, 0,
                                    RCOLOR(255, 255, 255, 255), NULL);
        add_element_to_render_queue(ground->sdata.currentimg->image, ground->sdata.x+ground->sdata.currentimg->width,
                                    ground->sdata.y, 0, RCOLOR(255, 255, 255, 255), NULL);
        if(ground->sdata.x+ground->sdata.currentimg->width < 0)
            ground->sdata.x = 0;
    }
    else
        add_element_to_render_queue(ground->sdata.currentimg->image, ground->sdata.x, ground->sdata.y, 0,
                                    RCOLOR(255, 255, 255, 255), NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

// Updates the background image
void update_background(void)
{
    SPRITESPTR background = search_sprite_list_for_element("BACKGROUND");
    add_element_to_render_queue(background->sdata.currentimg->image, background->sdata.x, background->sdata.y,
                                0, RDEFAULT, NULL);
}

/*----------------------------------------------------------------------------------------------------------*/

void update_sprites(cpBody *body, void* unused)
{
	cpShape *shape = (cpShape*)cpBodyGetUserData(body);
    void* data = cpShapeGetUserData(shape);
    if(shape == NULL || cpShapeGetBody(shape) == NULL || data == NULL)
        return;

	SPRITES *sprite = (SPRITES*)data;

    if(strcmp((char*)data, "STICKMAN") == 0)
        update_stickman();
    else if(strcmp(sprite->slabel, "AMEAN") == 0)
        update_ameans(sprite);
    else if(strcmp(sprite->slabel, "BRICK_WALL") == 0)
        update_brickwall(sprite);
    else if(strcmp(sprite->slabel, "CLAMP") == 0)
        update_clamp(sprite);
    else if(strcmp(sprite->slabel, "STEEL_WALL") == 0)
        update_steelwall(sprite);
    else if(strcmp(sprite->slabel, "FLYING_FIST") == 0)
        update_fist(sprite);
    else if(strcmp(sprite->slabel, "SPIKES") == 0)
        update_spikes(sprite);
    else if(strcmp(sprite->slabel, "RAW") == 0)
        update_raw(sprite);
    else if(strcmp(sprite->slabel, "PLANT") == 0)
        update_plant(sprite);
}

/*----------------------------------------------------------------------------------------------------------*/

void logic(void)
{
    static int counter = 0;
    static _Bool startcounter = false;
    if(!startcounter)
    {
        if(rand_int(1000) == 76 && start)
        {
            create_new_enemy("AMEAN");
            startcounter = true;
        }
        else if(rand_int(1000) == 112 && start)
        {
            create_new_enemy("BRICK_WALL");
            startcounter = true;
        }
        else if(rand_int(500) == 255 && start)
        {
            create_new_enemy("STEEL_WALL");
            startcounter = true;
        }
        else if(rand_int(1000) == 305 && start)
        {
            create_new_enemy("SPIKES");
            startcounter = true;
        }
        else if(rand_int(1000) == 456 && start)
        {
            create_new_enemy("FLYING_FIST");
            startcounter = true;
        }
        else if(rand_int(5000) == 12 && start)
        {
            create_new_enemy("CLAMP");
            startcounter = true;
        }
        else if(rand_int(1000) == 91 && start)
        {
            create_new_enemy("RAW");
            startcounter = true;
        }
        else if(rand_int(1000) == 945 && start)
        {
            create_new_enemy("PLANT");
            startcounter = true;
        }
    }
    else
    {
        counter++;
        if(counter >= 120)
        {
            counter = 0;
            startcounter = false;
        }
    }
}

/*----------------------------------------------------------------------------------------------------------*/

void maingame_cleanup(void)
{
    SPRITESPTR stman = search_sprite_list_for_element("STICKMAN");
    SPRITESPTR ground = search_sprite_list_for_element("GROUND");
    GDATAPTR game = get_game_data();
    cpCollisionHandler* c = cpSpaceAddCollisionHandler(get_global_cpSpace(), 1, 2);
    c->beginFunc = NULL;
    remove_physics_object(stman);
    remove_element_from_sprite_list_ptr(stman);
    remove_element_from_sprite_list("CLOUD");

    ground->sdata.x = 0;
    ground->sdata.y = 510;

    remove_all_enemies();

    game->gamestarted = false;

    start = false;
    lives = 3;
    score = 0;
    minutes = 0;
    seconds = 0;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
