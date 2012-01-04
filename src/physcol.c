#include <allegro5/allegro5.h>
#include <chipmunk/chipmunk.h>
#include <sprites.h>
#include <enemystore.h>
#include <maingame.h>
#include <physcol.h>

/*----------------------------------------------------------------------------*/

static cpSpace *space = NULL;

/*----------------------------------------------------------------------------*/

cpSpace* set_global_cpSpace(cpSpace *newspace)
{
    space = newspace;
    return space;
}

/*----------------------------------------------------------------------------------------------------------*/

cpSpace* get_global_cpSpace(void)
{
    return space;
}

/*----------------------------------------------------------------------------------------------------------*/

cpBody* create_new_body(SPRITESPTR sprite, float weight)
{
    float width = sprite->sdata.currentimg->width;
    float height = sprite->sdata.currentimg->height;
    cpBody *spriteBody = cpBodyNew(weight, INFINITY);;
    spriteBody->p = cpv(sprite->sdata.x+width/2, sprite->sdata.y+height/2);
    cpSpaceAddBody(space, spriteBody);
    return spriteBody;
}

/*----------------------------------------------------------------------------------------------------------*/

cpShape* create_new_shape(SPRITESPTR sprite, cpBody *spriteBody, float e, float u, int coltype, void *data)
{
    float width = sprite->sdata.currentimg->width;
    float height = sprite->sdata.currentimg->height;
    cpVect vects[4] = {cpv(0-width/2, 0-height/2),
                       cpv(0-width/2, 0+height/2),
                       cpv(0+width/2, 0+height/2),
                       cpv(0+width/2, 0-height/2)};
    cpShape *spriteShape = cpPolyShapeNew(spriteBody, 4, vects, cpvzero);
    spriteShape->e = e;
    spriteShape->u = u;
    spriteShape->collision_type = coltype;
    spriteShape->data = data;
    sprite->shape = spriteShape;
    cpSpaceAddShape(space, spriteShape);
    return spriteShape;
}

/*----------------------------------------------------------------------------------------------------------*/

cpShape* create_physics_object(SPRITESPTR sprite, float w, float e, float u, int coltype, void *data)
{
    cpBody *spriteBody = create_new_body(sprite, w);
    cpShape *spriteShape = create_new_shape(sprite, spriteBody, e, u, coltype, data);
    return spriteShape;
}

/*----------------------------------------------------------------------------------------------------------*/

void remove_physics_object(SPRITESPTR sprite)
{
    cpSpaceRemoveBody(space, sprite->shape->body);
    cpBodyFree(sprite->shape->body);
    cpSpaceRemoveShape(space, sprite->shape);
    cpShapeFree(sprite->shape);
}

/*----------------------------------------------------------------------------------------------------------*/

int collision_begin(cpArbiter *arb, cpSpace *Space, void *data)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);
    SPRITESPTR stman = search_sprite_list_for_element((char*)a->data);
    SPRITESPTR sprite = (SPRITESPTR)b->data;
    if((stman->sdata.animflags & MRECOVER))
    {
        return 0;
    }
    else
    {
        if(strcmp(sprite->slabel, "BRICK_WALL") == 0)
        {
            if(sprite->sdata.y < 405)
            {
                if((stman->sdata.animflags & MDOWN))
                    return 0;
                else
                    cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            }
            else if(stman->sdata.y+stman->sdata.currentimg->height > sprite->sdata.y)
                cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            return 1;
        }
        else if(strcmp(sprite->slabel, "CLAMP") == 0)
        {
            if((stman->sdata.animflags & MDOWN))
                return 0;
            else
            {
                set_anim_flags_on_sprite(sprite, MATTACK);
                cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
                return 1;
            }
        }
        else if(strcmp(sprite->slabel, "STEEL_WALL") == 0)
        {
            if(sprite->sdata.y < 385)
            {
                if((stman->sdata.animflags & MDOWN))
                    return 0;
                else
                    cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            }
            else if(stman->sdata.y+stman->sdata.currentimg->height > sprite->sdata.y)
                cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            return 1;
        }
        else if(strcmp(sprite->slabel, "FLYING_FIST") == 0)
        {
            if(!(stman->sdata.animflags & MDOWN))
                cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            return 1;
        }
        else if(strcmp(sprite->slabel, "SPIKES") == 0)
        {
            cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
            return 1;
        }
        else if((stman->sdata.animflags & MATTACK))
            cpSpaceAddPostStepCallback(Space, collision_end_win, b, NULL);
        else
            cpSpaceAddPostStepCallback(Space, collision_end_lose, b, NULL);
    }
    return 1;
}

/*----------------------------------------------------------------------------------------------------------*/

int collision_pre_solve(cpArbiter *arb, cpSpace *Space, void *data)
{
    return 1;
}

/*----------------------------------------------------------------------------------------------------------*/

void collision_post_solve(cpArbiter *arb, cpSpace *Space, void *data)
{

}

/*----------------------------------------------------------------------------------------------------------*/

void collision_separate(cpArbiter *arb, cpSpace *Space, void *data)
{
}

/*----------------------------------------------------------------------------------------------------------*/

int collision_static_begin(cpArbiter *arb, cpSpace *Space, void *data)
{
    cpShape *a, *b;
    cpArbiterGetShapes(arb, &a, &b);

    if(b->collision_type == 1 && strcmp((char*)a->data, "LEFTSHAPE") == 0)
    {
        SPRITESPTR stman = search_sprite_list_for_element((char*)b->data);
        if((stman->sdata.animflags & MDAMAGED))
            return 0;
        else
            return 1;
    }
    else if(strcmp((char*)a->data, "FLOORSHAPE") == 0)
        return 1;
    else if(strcmp((char*)a->data, "TOPSHAPE") == 0)
        return 1;
    else
        return 0;
}

/*----------------------------------------------------------------------------------------------------------*/

int collision_static_pre_solve(cpArbiter *arb, cpSpace *Space, void *data)
{
    return 1;
}

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_post_solve(cpArbiter *arb, cpSpace *Space, void *data)
{

}

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_separate(cpArbiter *arb, cpSpace *Space, void *data)
{

}

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_end(cpSpace *Space, void *obj, void *unused)
{

}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
