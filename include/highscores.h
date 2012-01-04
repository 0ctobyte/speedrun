/**
  *@file highscores.h
  *Displays and updates the highscores menu
  */
//    /**
//      *@defgroup highscoresh highscores.h
//      *Displays and updates the highscores menu
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

void highscores(void);

/*----------------------------------------------------------------------------------------------------------*/

void print_scores(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color);

/*----------------------------------------------------------------------------------------------------------*/

void load_file(void);

/*----------------------------------------------------------------------------------------------------------*/

void create_blank_file(void);

/*----------------------------------------------------------------------------------------------------------*/

void clear_highscores(void);

/*----------------------------------------------------------------------------------------------------------*/

void add_score(int score, char *survival_time);

/*----------------------------------------------------------------------------------------------------------*/

int get_score_pos(int *array, int score);

/*----------------------------------------------------------------------------------------------------------*/

int* get_scores(void);

/*----------------------------------------------------------------------------------------------------------*/

void highscores_cleanup(void);

/*----------------------------------------------------------------------------------------------------------*/

void exit_highscores(GDATAPTR game);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
