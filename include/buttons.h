/**
  *@file buttons.h
  *Routines to create and manage the buttons linked list. Handles all mouse events related to buttons.
  */
//    /**
//      *@defgroup buttonsh buttons.h
//      *Routines to create and manage the buttons linked list. Handles all mouse events related to buttons.
//      *@{
//      */

/*----------------------------------------------------------------------------------------------------------*/

#define BPRESSED_CALL 2345
#define CBANIMATION_CALL 6574

/*----------------------------------------------------------------------------------------------------------*/

#define BCOLOR(r, g, b, a) al_map_rgba(r, g, b, a)

/*----------------------------------------------------------------------------------------------------------*/

#define TDEFAULT al_map_rgba(0, 0, 0, 255)
#define BDEFAULT al_map_rgba(255, 255, 255, 255)
#define BRED al_map_rgba(255, 0, 0, 255)
#define BGREEN al_map_rgba(0, 255, 0, 255)
#define BBLUE al_map_rgba(0, 0, 255, 255)
#define BBLACK al_map_rgba(0, 0, 0, 255)
#define BWHITE al_map_rgba(255, 255, 255, 255)
#define BHTRANSPARENT al_map_rgba(255, 255, 255, 127)
#define BQTRANSPARENT al_map_rgba(255, 255, 255, 191)
#define WHTRANSPARENT al_map_rgba(0, 0, 0, 127)
#define WQTRANSPARENT al_map_rgba(0, 0, 0, 191)

/*----------------------------------------------------------------------------------------------------------*/

typedef enum button_properties {
    BVISIBLE = 0x1,
    BMOUSEOVER = 0x2,
    BLPRESSED = 0x4,
    BLRELEASED = 0x8,
    BRPRESSED = 0x10,
    BRRELEASED = 0x20,
    BMPRESSED = 0x40,
    BMRELEASED = 0x80,
    BDRAW = 0x100
} BPROPERTIES;

/*----------------------------------------------------------------------------------------------------------*/

typedef enum standard_button_animations {
    BSHIFTRIGHT,
    BBOUNCEVERT,
    BBOUNCEHORZ,
    BSHIFTLEFT,
    SBNONE,
    SBRIGHT,
    SBLEFT,
    SBUP,
    SBDOWN
} SBANIMATIONS;

/*----------------------------------------------------------------------------------------------------------*/

typedef enum custom_button_animations {
    BRIGHT,
    BLEFT,
    BUP,
    BDOWN,
    BNONE
} CBANIMATIONS;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct button_images {
    char *label;
    ALLEGRO_BITMAP *button_image;
    float width;
    float height;
    struct button_images *nextbimage;
    struct button_images *prevbimage;
} BIMAGES, *BIMAGESPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct button_text {
    char *text;
    ALLEGRO_FONT *text_f;
    ALLEGRO_COLOR text_c;
} BTEXT, *BTEXTPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct button_data {
    float x;
    float y;
    float ox;
    float oy;
    float limit;
    int alpha;
    ALLEGRO_COLOR b_color;
    SBANIMATIONS sflags;
    CBANIMATIONS aflags;
    BPROPERTIES bflags;
} BDATA, *BDATAPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef struct buttons {
    char *blabel;
    BIMAGESPTR bimage;
    BTEXT btext;
    BDATA bdata;
    struct buttons *nextbutton;
    struct buttons *prevbutton;
} BUTTON, *BUTTONPTR;

/*----------------------------------------------------------------------------------------------------------*/

typedef void* (*BUTTON_CALLBACK)(BUTTONPTR, void*, int);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR get_first_element_from_button_list(void);

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR get_first_element_from_button_image_list(void);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR set_first_element_in_button_list(BUTTONPTR *newfirst);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR create_new_button(char *label, char *bimage_label,
                            char *text, ALLEGRO_FONT *font,
                            ALLEGRO_COLOR text_color, ALLEGRO_COLOR button_color,
                            float x, float y, float limit,
                            CBANIMATIONS aflags, BPROPERTIES bflags,
                            _Bool add_to_list);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR add_element_to_button_list(BUTTONPTR *button);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR remove_element_from_button_list(BUTTONPTR *currentptr);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR search_button_list_for_element(BUTTONPTR *firstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR set_bflags_on_button(BUTTONPTR button, BPROPERTIES bflags);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR remove_bflags_on_button(BUTTONPTR button, BPROPERTIES bflags);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_button_list(BUTTONPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR create_new_button_image_list(char *labels[], char *images[], int num_elements);

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR add_element_to_button_image_list(BIMAGESPTR *firstptr, BIMAGESPTR *newptr);

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR remove_element_from_button_image_list(BIMAGESPTR *firstptr, BIMAGESPTR *currentptr);////////////

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR search_button_image_list_for_element(BIMAGESPTR firstptr, char *label);

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_button_image_list(BIMAGESPTR firstptr);

/*----------------------------------------------------------------------------------------------------------*/

BUTTON_CALLBACK set_button_callback(BUTTON_CALLBACK bcallb_func);

/*----------------------------------------------------------------------------------------------------------*/

BUTTON_CALLBACK get_button_callback(void);

/*----------------------------------------------------------------------------------------------------------*/

void buttoncheck(BUTTON_CALLBACK bcallb_func, void *data);

/*----------------------------------------------------------------------------------------------------------*/

_Bool is_mouse_over_button(ALLEGRO_MOUSE_STATE *mouse, BUTTONPTR currentptr);

/*----------------------------------------------------------------------------------------------------------*/

_Bool is_point_over_button(int x, int y, BUTTONPTR currentptr);

/*----------------------------------------------------------------------------------------------------------*/

void check_for_button_events(BUTTONPTR currentptr);

/*----------------------------------------------------------------------------------------------------------*/

void render_buttons(void);

/*----------------------------------------------------------------------------------------------------------*/

void draw_button(BUTTONPTR currentptr);

/*----------------------------------------------------------------------------------------------------------*/

SBANIMATIONS set_standard_button_animation(SBANIMATIONS sb_new);

/*----------------------------------------------------------------------------------------------------------*/

SBANIMATIONS get_standard_button_animation(void);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR standard_button_animations(BUTTONPTR button);

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR custom_button_animations(BUTTONPTR button, CBANIMATIONS cb, float limit, BUTTON_CALLBACK bcall,
                                   void *data);

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
