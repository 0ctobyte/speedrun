/**
  *@file sprites.h
  *Manages the base image linked list and the sprite linked list, provides function to create new sprites
  *and add them to sprite list as well as removing sprites from the list
  */
//    /**
//      *@defgroup spritesh sprites.h
//      *Manages the base image linked list and the sprite linked list, provides function to create new sprites
//      *and add them to sprite list as well as removing sprites from the list
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

typedef enum animation {
    MLEFT = 0x1,
    MRIGHT = 0x2,
    MUP = 0x4,
    MDOWN = 0x8,
    MATTACK = 0x10,
    MDAMAGED = 0x20,
    MRECOVER = 0x40,
    MNONE = 0x80
} ANIMATION;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct sprite_images {
    char *ilabel;
    ALLEGRO_BITMAP *image;
    float width;
    float height;
    struct sprite_images *nextimage;
    struct sprite_images *previmage;
} SIMAGE, *SIMAGEPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct sprite_data_aux {
    char *dlabel;
    char *dtype;
    void *data;
    struct sprite_data_aux *nextdata;
    struct sprite_data_aux *prevdata;
} SDATAX, *SDATAXPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct sprite_data_core {
    SIMAGEPTR currentimg;
    float x;
    float y;
    float dx;
    float dy;
    int anim_counter;
    ANIMATION animflags;
} SDATAC, *SDATACPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct sprites {
    char *slabel;
    SIMAGEPTR ifirstptr;
    SDATAXPTR dfirstptr;
    SDATAC sdata;
    struct cpShape *shape;
    struct sprites *nextsprite;
    struct sprites *prevsprite;
} SPRITES, *SPRITESPTR;

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR get_first_element_from_sprite_list(void);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR set_first_element_in_sprite_list(SPRITESPTR *newfirst);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR create_new_sprite(char *label, char *imagelabels[], int num_images,
                             char *datalabels[], char *datatypes[], void *data[],
                             int num_data, char *currentimg, float x, float y,
                             float dx, float dy, int anim_counter, ANIMATION animflags,
                             _Bool add_to_list);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR add_element_to_sprite_list(SPRITESPTR *sprite);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_element_from_sprite_list(char *label);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_element_from_sprite_list_ptr(SPRITESPTR sprite);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR search_sprite_list_for_element(char *label);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_sprite_list(SPRITESPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR set_anim_flags_on_sprite(SPRITESPTR sprite, ANIMATION nflags);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_anim_flags_on_sprite(SPRITESPTR sprite, ANIMATION nflags);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR clear_anim_flags_on_sprite(SPRITESPTR sprite);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR clear_anim_flags_on_sprite_list(SPRITESPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_anim_flags_on_sprite_list(SPRITESPTR firstptr, ANIMATION nflags);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR get_first_element_from_base_image_list(void);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR set_first_element_in_base_image_list(SIMAGEPTR *newfirst);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR create_base_image_list(char* labels[], char *images[], int max);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR create_new_base_image(char *label, char *file_name);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR add_element_to_base_image_list(SIMAGEPTR *image);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR remove_element_from_base_image_list(char *label);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR search_base_image_list_for_element(char *label);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_base_image_list(SIMAGEPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR create_new_image_list(char *labels[], int max);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR create_new_image(char *label);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR add_element_to_image_list(SIMAGEPTR *ifirstptr, SIMAGEPTR *image);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR remove_element_from_image_list(SIMAGEPTR *ifirstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

SIMAGEPTR search_image_list_for_element(SIMAGEPTR *ifirstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_image_list(SIMAGEPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR create_new_datax_list(char *labels[], char *types[], void *data[], int max);

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR create_new_datax(char *label, char *type, void *data);

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR add_element_to_datax_list(SDATAXPTR *dfirstptr, SDATAXPTR *datax);

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR remove_element_from_datax_list(SDATAXPTR *dfirstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR search_datax_list_for_element(SDATAXPTR *dfirstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_datax_list(SDATAXPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
