#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <commons.h>
#include <buttons.h>
#include <render.h>
#include <highscores.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR back = NULL, clear = NULL;
static char* scorefile = NULL, *scores = NULL;

/*----------------------------------------------------------------------------*/

void highscores(void)
{
    GDATAPTR game = get_game_data();
    if(back == NULL)
    {
        back = create_new_button("BACK",
                                 "DEFAULT",
                                 "BACK",
                                 game->b_font,
                                 BCOLOR(255, 255, 255, 255),
                                 BCOLOR(65, 105, 255, 191),
                                 -280,
                                 500,
                                 50,
                                 BRIGHT,
                                 BVISIBLE,
                                 true
                                 );
    }
    if(clear == NULL)
    {
        clear = create_new_button("CLEAR",
                                  "DEFAULT",
                                  "CLEAR",
                                  game->b_font,
                                  BCOLOR(255, 255, 255, 255),
                                  BCOLOR(65, 105, 255, 191),
                                  805,
                                  500,
                                  475,
                                  BLEFT,
                                  BVISIBLE,
                                  true
                                  );
    }

    if(scorefile == NULL || scores == NULL)
    {
        load_file();
    }
    add_element_to_render_queue(NULL, 50, 0, 0, RCOLOR(0, 0, 0, 255), print_scores);
}

/*----------------------------------------------------------------------------------------------------------*/

void print_scores(ALLEGRO_BITMAP *image, float x, float y, int nflags, ALLEGRO_COLOR color)
{
    GDATAPTR game = get_game_data();
    char *buf, *temp = (char*)malloc(sizeof(char)*strlen(scorefile));
    int i = 0;
    int xx = x, yy = y;
    al_draw_textf(game->font, color, x, y+40, nflags, "Name");
    al_draw_textf(game->font, color, x+250, y+40, nflags, "Score");
    al_draw_textf(game->font, color, x+500, y+40, nflags, "Survival Time");
    strcpy(temp, scorefile);
    buf = strtok(temp, " ^");
    yy += 40;
    while(buf != NULL && i < 30)
    {
        if(i % 3 == 0)
        {
            yy += 40;
            xx = x;
        }
        al_draw_textf(game->font, color, xx, yy, nflags, "%s", buf);
        buf = strtok(NULL, " ^");
        xx += 250;
        i++;
    }
    free(temp);
}

/*----------------------------------------------------------------------------------------------------------*/

void load_file(void)
{
    FILE *file = NULL;
    if((file = fopen("highscores.database", "r")) == NULL)
    {
        create_blank_file();
        file = fopen("highscores.database", "r");
    }
    fseek(file , 0 , SEEK_END);
    long size = ftell(file);
    rewind(file);
    scorefile = (char*)malloc(size*sizeof(char));
    fread(scorefile, 1, size, file);
    fclose(file);
    file = NULL;
    if((file = fopen("scores.database", "r")) == NULL)
    {
        create_blank_file();
        file = fopen("scores.database", "r");
    }
    fseek(file , 0 , SEEK_END);
    size = ftell(file);
    rewind(file);
    scores = (char*)malloc(size*sizeof(char));
    fread(scores, 1, size, file);
    fclose(file);
}

/*----------------------------------------------------------------------------------------------------------*/

void clear_highscores(void)
{
    remove("highscores.database");
    free(scorefile);
    scorefile = NULL;
    load_file();
}

/*----------------------------------------------------------------------------------------------------------*/

void add_score(int score, char *survival_time)
{
    int *array = get_scores();
    int pos = get_score_pos(array, score);

    if(pos <= 10)
    {
        char *p = strchr(scores, '^');
        //char *q = scores;
        int i = 1;
        while(i <= 10)
        {
            if(i == pos) break;
            //q = p;
            p = strchr(p+1, '^');
            i++;
        }
    }
}

/*----------------------------------------------------------------------------------------------------------*/

int get_score_pos(int *array, int score)
{
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        if(score > array[i])
            break;
    }
    return i+1;
}

/*----------------------------------------------------------------------------------------------------------*/

int* get_scores(void)
{
    int *array = (int*)malloc(sizeof(int)*10);
    char *buf, *temp = (char*)malloc(sizeof(char)*strlen(scores));
    int i = 0;
    strcpy(temp, scores);
    buf = strtok(temp, "^");
    while(buf != NULL && i < 10)
    {
        array[i] = atoi(buf);
        buf = strtok(NULL, "^");
        i++;
    }
    free(temp);
    return array;
}

/*----------------------------------------------------------------------------------------------------------*/

void create_blank_file(void)
{
    FILE *file = fopen("highscores.database", "w");
    for(int i = 0; i < 10; i++)
    {
        if(i == 9)
            fprintf(file, "%d.Player%d ---- ----^", i, i);
        else
            fprintf(file, "%d.Player%d ---- ----^", i, i);
    }
    fclose(file);
    file = fopen("scores.database", "w");
    for(int i = 0; i < 10; i++)
    {
        fprintf(file, "0^");
    }
    fclose(file);
}

/*----------------------------------------------------------------------------------------------------------*/

void highscores_cleanup(void)
{
    remove_element_from_button_list(&back);
    back = NULL;
    remove_element_from_button_list(&clear);
    clear = NULL;
    free(scorefile);
    scorefile = NULL;
    free(scores);
    scores = NULL;
}

/*----------------------------------------------------------------------------------------------------------*/

void exit_highscores(GDATAPTR game)
{
    BUTTONPTR currentptr, firstptr = get_first_element_from_button_list();
    currentptr = search_button_list_for_element(&firstptr, "BACK");
    currentptr->bdata.limit = -280;
    currentptr->bdata.aflags = BLEFT;
    currentptr = search_button_list_for_element(&firstptr, "CLEAR");
    currentptr->bdata.limit = 805;
    currentptr->bdata.aflags = BRIGHT;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
