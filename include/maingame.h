/**
  *@file maingame.h
  *Updates the game state every frame, performs all animations and game logic
  */
//    /**
//      *@defgroup maingameh maingame.h
//      *Updates the game state every frame, performs all animations and game logic
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

void update(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_background(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_stickman(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_lives(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_score(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color);

/*----------------------------------------------------------------------------------------------------------*/

void update_survivaltime(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color);

/*----------------------------------------------------------------------------------------------------------*/

void update_ameans(SPRITESPTR amean);

/*----------------------------------------------------------------------------------------------------------*/

void update_brickwall(SPRITESPTR brickwall);

/*----------------------------------------------------------------------------------------------------------*/

void update_steelwall(SPRITESPTR steelwall);

/*----------------------------------------------------------------------------------------------------------*/

void update_clamp(SPRITESPTR clamp);

/*----------------------------------------------------------------------------------------------------------*/

void update_spikes(SPRITESPTR spikes);

/*----------------------------------------------------------------------------------------------------------*/

void update_fist(SPRITESPTR fist);

/*----------------------------------------------------------------------------------------------------------*/

void update_raw(SPRITESPTR raw);

/*----------------------------------------------------------------------------------------------------------*/

void update_plant(SPRITESPTR plant);

/*----------------------------------------------------------------------------------------------------------*/

void update_clouds(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_ground(void);

/*----------------------------------------------------------------------------------------------------------*/

void update_sprites(cpBody *body, void* unused);

/*----------------------------------------------------------------------------------------------------------*/

void logic(void);

/*----------------------------------------------------------------------------------------------------------*/

void collision_end_win(cpSpace *Space, void *obj, void *unused);

/*----------------------------------------------------------------------------------------------------------*/

void collision_end_lose(cpSpace *Space, void *obj, void *unused);

/*----------------------------------------------------------------------------------------------------------*/

void maingame_cleanup(void);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
