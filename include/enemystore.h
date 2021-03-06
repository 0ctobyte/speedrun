/**
  *@file enemystore.h
  *Functions to create and keep track of enemies
  */
//    /**
//      *@defgroup enemystoreh enemystore.h
//      *Functions to create and keep track of enemies
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

int rand_int(int max);

/*----------------------------------------------------------------------------------------------------------*/

void remove_enemy(cpSpace *space, void *obj, void *data);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR create_new_enemy(char *enemy_type);

/*----------------------------------------------------------------------------------------------------------*/

void remove_all_enemies_of_type(char *enemy_label);

/*----------------------------------------------------------------------------------------------------------*/

void remove_all_enemies(void);

/*----------------------------------------------------------------------------------------------------------*/


//    /**
//      *@}
//      */
