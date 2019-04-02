/**
  *@file physcol.h
  *Routines to perform physic simulation and collision detection using the chipmunk engine
  */
//    /**
//      *@defgroup physcolh physcol.h
//      *Routines to perform physic simulation and collision detection using the chipmunk engine
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

cpSpace* set_global_cpSpace(cpSpace *newspace);

/*----------------------------------------------------------------------------------------------------------*/

cpSpace* get_global_cpSpace(void);

/*----------------------------------------------------------------------------------------------------------*/

cpBody* create_new_body(SPRITESPTR sprite, float weight);

/*----------------------------------------------------------------------------------------------------------*/

cpShape* create_new_shape(SPRITESPTR sprite, cpBody *spriteBody, float e, float u, int coltype, void *data);

/*----------------------------------------------------------------------------------------------------------*/

cpShape* create_physics_object(SPRITESPTR sprite, float w, float e, float u, int coltype, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void remove_physics_object(SPRITESPTR sprite);

/*----------------------------------------------------------------------------------------------------------*/

unsigned char collision_begin(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

unsigned char collision_pre_solve(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void collision_post_solve(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void collision_separate(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

unsigned char  collision_static_begin(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

unsigned char collision_static_pre_solve(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_post_solve(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_separate(cpArbiter *arb, cpSpace *Space, void *data);

/*----------------------------------------------------------------------------------------------------------*/

void collision_static_end(cpSpace *Space, void *obj, void *unused);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
