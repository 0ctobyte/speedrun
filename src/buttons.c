#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <commons.h>
#include <imagescale.h>
#include <buttons.h>

/*----------------------------------------------------------------------------*/

static BUTTONPTR bfirstptr = NULL;

/*----------------------------------------------------------------------------*/

static BIMAGESPTR bitoptr = NULL;

/*----------------------------------------------------------------------------*/

static BUTTON_CALLBACK bcallback_func;

/*----------------------------------------------------------------------------*/

static SBANIMATIONS sb = SBNONE;

/*----------------------------------------------------------------------------*/

BUTTONPTR get_first_element_from_button_list(void)
{
    return bfirstptr;
}

/*----------------------------------------------------------------------------*/

BIMAGESPTR get_first_element_from_button_image_list(void)
{
    return bitoptr;
}

/*----------------------------------------------------------------------------*/

BUTTONPTR set_first_element_in_button_list(BUTTONPTR *newfirst)
{
    bfirstptr = *newfirst;
    return bfirstptr;
}

/*----------------------------------------------------------------------------*/

BUTTON_CALLBACK get_button_callback(void)
{
    return bcallback_func;
}

/*----------------------------------------------------------------------------*/

BUTTON_CALLBACK set_button_callback(BUTTON_CALLBACK bcallb_func)
{
    bcallback_func = bcallb_func;
    return bcallback_func;
}

/*----------------------------------------------------------------------------*/

void buttoncheck(BUTTON_CALLBACK bcallb_func, void *data)
{
    BUTTONPTR currentptr = bfirstptr;
    do
    {
        if((currentptr->bdata.bflags & BVISIBLE))
        {
            if(currentptr->bdata.aflags == BNONE)
                check_for_button_events(currentptr);
            if((currentptr->bdata.bflags & BMOUSEOVER) && (currentptr->bdata.bflags & BLRELEASED))
                bcallb_func(currentptr, data, BPRESSED_CALL);
            standard_button_animations(currentptr);
            custom_button_animations(currentptr, currentptr->bdata.aflags, currentptr->bdata.limit, bcallb_func, data);
        }
    } while((currentptr = currentptr->nextbutton) != bfirstptr);
}

/*----------------------------------------------------------------------------------------------------------*/

void render_buttons(void)
{
    BUTTONPTR currentptr = bfirstptr;
    do
    {
        if((currentptr->bdata.bflags & BVISIBLE))
        {
            draw_button(currentptr);
            if((currentptr->bdata.bflags & BLPRESSED) && !(currentptr->bdata.bflags & BLRELEASED))
                remove_bflags_on_button(currentptr, BLRELEASED | BRPRESSED | BRRELEASED | BMRELEASED | BMPRESSED |
                                                BDRAW | BMOUSEOVER);
            else
                remove_bflags_on_button(currentptr, BLPRESSED | BLRELEASED | BMRELEASED | BMPRESSED | BRPRESSED |
                                                BRRELEASED | BDRAW | BMOUSEOVER);
        }
    } while((currentptr = currentptr->nextbutton) != bfirstptr);
}

/*----------------------------------------------------------------------------------------------------------*/

void draw_button(BUTTONPTR currentptr)
{
    const int c = 2, d = 2, x = 0, y = 0;
    nscale();
    static ALLEGRO_BITMAP *newbitm = NULL;
    if(newbitm == NULL)
        newbitm = al_create_bitmap(currentptr->bimage->width, currentptr->bimage->height);
    al_set_target_bitmap(newbitm);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    if((currentptr->bdata.bflags & BDRAW) && !(currentptr->bdata.bflags & BLPRESSED))
    {
        al_draw_tinted_bitmap(currentptr->bimage->button_image, currentptr->bdata.b_color, x, y, 0);
        al_draw_text(currentptr->btext.text_f,
                     currentptr->btext.text_c,
                     currentptr->bimage->width/d,
                     currentptr->bimage->height/d-al_get_font_line_height(currentptr->btext.text_f)/d,
                     ALLEGRO_ALIGN_CENTRE,
                     currentptr->btext.text
                     );
    }
    else if((currentptr->bdata.bflags & BDRAW) && (currentptr->bdata.bflags & BLPRESSED))
    {
        al_draw_tinted_bitmap(currentptr->bimage->button_image, currentptr->bdata.b_color, x, y, ALLEGRO_FLIP_VERTICAL);
        al_draw_text(currentptr->btext.text_f,
                     currentptr->btext.text_c,
                     currentptr->bimage->width/d+c,
                     currentptr->bimage->height/d-al_get_font_line_height(currentptr->btext.text_f)/d+c,
                      ALLEGRO_ALIGN_CENTRE,
                      currentptr->btext.text
                      );
    }
    else
    {
        al_draw_tinted_bitmap(currentptr->bimage->button_image, currentptr->bdata.b_color, x, y, 0);
        al_draw_text(currentptr->btext.text_f,
                     currentptr->btext.text_c,
                     currentptr->bimage->width/d,
                     currentptr->bimage->height/d-al_get_font_line_height(currentptr->btext.text_f)/d,
                     ALLEGRO_ALIGN_CENTRE,
                     currentptr->btext.text
                     );
    }
    scale(800.0, 600.0);
    al_set_target_backbuffer(get_game_data()->display);
    al_draw_bitmap(newbitm, currentptr->bdata.x, currentptr->bdata.y, 0);
}

/*----------------------------------------------------------------------------------------------------------*/

void check_for_button_events(BUTTONPTR currentptr)
{
    const int MOUSEL = 1;// MOUSER = 2, MOUSEM = 3;
    static int mx, my;
    static _Bool mdown = false;
    ALLEGRO_MOUSE_STATE mouse;
    al_get_mouse_state(&mouse);

    set_bflags_on_button(currentptr, BDRAW);
    if(al_mouse_button_down(&mouse, MOUSEL) && !mdown)
    {
        mx = mouse.x;
        my = mouse.y;
        mdown = true;
    }
    if(!al_mouse_button_down(&mouse, MOUSEL))
    {
        mdown = false;
    }
    if(is_point_over_button(mx, my, currentptr))
    {
        if(is_mouse_over_button(&mouse, currentptr))
        {
            set_bflags_on_button(currentptr, BMOUSEOVER);
        }
        if(al_mouse_button_down(&mouse, MOUSEL) && (currentptr->bdata.bflags & BMOUSEOVER))
        {
            set_bflags_on_button(currentptr, BLPRESSED);
        }
        if(!al_mouse_button_down(&mouse, MOUSEL) && (currentptr->bdata.bflags & BLPRESSED))
        {
            set_bflags_on_button(currentptr, BLRELEASED);
        }
    }
    else
    {
        if(is_mouse_over_button(&mouse, currentptr))
        {
            set_bflags_on_button(currentptr, BMOUSEOVER);
        }
    }
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR search_button_list_for_element(BUTTONPTR *firstptr, char *label)
{
    BUTTONPTR currentptr = *firstptr;
    if(currentptr == NULL) return NULL;
    do
    {
        if(strcmp(currentptr->blabel, label) == 0) break;
        currentptr = currentptr->nextbutton;
    } while(currentptr != *firstptr);

    if(strcmp(currentptr->blabel, label) != 0) return NULL;
    return currentptr;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR create_new_button(char *label, char *bimage_label,
                            char *text, ALLEGRO_FONT *font,
                            ALLEGRO_COLOR text_color, ALLEGRO_COLOR button_color,
                            float x, float y, float limit,
                            CBANIMATIONS aflags, BPROPERTIES bflags,
                            _Bool add_to_list)
{
    BUTTONPTR newptr;
    BIMAGESPTR bcurrentptr = search_button_image_list_for_element(bitoptr, bimage_label);
    unsigned char r, g, b, a;
    if((newptr = (BUTTONPTR)malloc(sizeof(BUTTON))) == NULL) return NULL;

    newptr->blabel = label;
    newptr->bimage = bcurrentptr;
    newptr->btext.text = text;
    newptr->btext.text_f = font;
    newptr->btext.text_c = text_color;
    newptr->bdata.x = x;
    newptr->bdata.y = y;
    newptr->bdata.ox = x;
    newptr->bdata.oy = y;
    newptr->bdata.limit = limit;
    newptr->bdata.b_color = button_color;
    newptr->bdata.sflags = 0;
    newptr->bdata.aflags = aflags;
    newptr->bdata.bflags = bflags;

    al_unmap_rgba(newptr->bdata.b_color, &r, &g, &b, &a);

    newptr->bdata.alpha = a;

    if(add_to_list)
        add_element_to_button_list(&newptr);

    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR add_element_to_button_list(BUTTONPTR *button)
{
    BUTTONPTR currentptr;
    if(bfirstptr != NULL)
    {
        currentptr = bfirstptr->prevbutton;
        currentptr->nextbutton = *button;
        (*button)->prevbutton = currentptr;
        bfirstptr->prevbutton = *button;
        (*button)->nextbutton = bfirstptr;
    }
    else
    {
        bfirstptr = *button;
        (*button)->nextbutton = *button;
        (*button)->prevbutton = *button;
    }
    return *button;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR remove_element_from_button_list(BUTTONPTR *currentptr)
{
    if(bfirstptr == NULL) return NULL;
    if(*currentptr == NULL) return NULL;
    if(*currentptr == bfirstptr && (*currentptr)->nextbutton == *currentptr && (*currentptr)->prevbutton == *currentptr)
    {
        free(*currentptr);
        bfirstptr = NULL;
    }
    else
    {
        (*currentptr)->nextbutton->prevbutton = (*currentptr)->prevbutton;
        (*currentptr)->prevbutton->nextbutton = (*currentptr)->nextbutton;
        if(*currentptr == bfirstptr)
            bfirstptr = (*currentptr)->nextbutton;
        free(*currentptr);
    }
    return bfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_button_list(BUTTONPTR firstptr)
{
    BUTTONPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextbutton == firstptr && firstptr->prevbutton == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextbutton == firstptr->prevbutton)
    {
        currentptr = currentptr->nextbutton;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextbutton;
        firstptr->prevbutton->nextbutton = NULL;
        currentptr->prevbutton = NULL;
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextbutton;
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_button_image_list(BIMAGESPTR firstptr)
{
    BIMAGESPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextbimage == firstptr && firstptr->prevbimage == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextbimage == firstptr->prevbimage)
    {
        currentptr = currentptr->nextbimage;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextbimage;
        firstptr->prevbimage->nextbimage = NULL;
        currentptr->prevbimage = NULL;
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextbimage;
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR set_bflags_on_button(BUTTONPTR button, BPROPERTIES bflags)
{
    if((bflags & BVISIBLE))
        button->bdata.bflags |= BVISIBLE;
    if((bflags & BLPRESSED))
        button->bdata.bflags |= BLPRESSED;
    if((bflags & BLRELEASED))
        button->bdata.bflags |= BLRELEASED;
    if((bflags & BRPRESSED))
        button->bdata.bflags |= BRPRESSED;
    if((bflags & BRRELEASED))
        button->bdata.bflags |= BRRELEASED;
    if((bflags & BMPRESSED))
        button->bdata.bflags |= BMPRESSED;
    if((bflags & BMRELEASED))
        button->bdata.bflags |= BMRELEASED;
    if((bflags & BMOUSEOVER))
        button->bdata.bflags |= BMOUSEOVER;
    if((bflags & BDRAW))
        button->bdata.bflags |= BDRAW;

    return button;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR remove_bflags_on_button(BUTTONPTR button, BPROPERTIES bflags)
{
    if((bflags & BVISIBLE))
        button->bdata.bflags &= ~BVISIBLE;
    if((bflags & BLPRESSED))
        button->bdata.bflags &= ~BLPRESSED;
    if((bflags & BLRELEASED))
        button->bdata.bflags &= ~BLRELEASED;
    if((bflags & BRPRESSED))
        button->bdata.bflags &= ~BRPRESSED;
    if((bflags & BRRELEASED))
        button->bdata.bflags &= ~BRRELEASED;
    if((bflags & BMPRESSED))
        button->bdata.bflags &= ~BMPRESSED;
    if((bflags & BMRELEASED))
        button->bdata.bflags &= ~BMRELEASED;
    if((bflags & BMOUSEOVER))
        button->bdata.bflags &= ~BMOUSEOVER;
    if((bflags & BDRAW))
        button->bdata.bflags &= ~BDRAW;

    return button;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR standard_button_animations(BUTTONPTR button)
{
    const int dx = 1, dy = 1, limit = 20;
    unsigned char r, g, b, a;
    al_unmap_rgba(button->bdata.b_color, &r, &g, &b, &a);
    if((button->bdata.bflags & BMOUSEOVER))
    {
        button->bdata.b_color = BCOLOR(r, g, b, 255);
        switch(sb)
        {
            default:
            case SBLEFT:
            case SBRIGHT:
            case SBUP:
            case SBDOWN:
            case SBNONE:
            break;
            case BBOUNCEHORZ:
            {
                if(button->bdata.sflags == SBRIGHT)
                    button->bdata.x += dx;
                else if(button->bdata.sflags == SBLEFT)
                    button->bdata.x -= dx;
                if(button->bdata.x >= button->bdata.ox+limit)
                    button->bdata.sflags = SBLEFT;
                if(button->bdata.x <= button->bdata.ox-limit)
                    button->bdata.sflags = SBRIGHT;
                if(button->bdata.sflags == 0)
                    button->bdata.sflags = SBRIGHT;
            }
            break;
            case BSHIFTRIGHT:
            {
                if(button->bdata.x < button->bdata.ox+limit)
                    button->bdata.x += 1;
            }
            break;
            case BSHIFTLEFT:
            {
                if(button->bdata.x > button->bdata.ox-limit)
                    button->bdata.x -= 1;
            }
            break;
            case BBOUNCEVERT:
            {
                if(button->bdata.sflags == SBDOWN)
                    button->bdata.y += dy;
                else if(button->bdata.sflags == SBUP)
                    button->bdata.y -= dy;
                if(button->bdata.y >= button->bdata.oy+limit)
                    button->bdata.sflags = SBUP;
                if(button->bdata.y <= button->bdata.oy-limit)
                    button->bdata.sflags = SBDOWN;
                if(button->bdata.sflags == 0)
                    button->bdata.sflags = SBDOWN;
            }
        }
    }
    else
    {
       button->bdata.b_color = BCOLOR(r, g, b, button->bdata.alpha);
       button->bdata.sflags = 0;
       if(button->bdata.x > button->bdata.ox)
            button->bdata.x -= 1;
       if(button->bdata.x < button->bdata.ox)
            button->bdata.x += 1;
       if(button->bdata.y > button->bdata.oy)
            button->bdata.y -= 1;
       if(button->bdata.y < button->bdata.oy)
            button->bdata.y += 1;
    }
    return button;
}

/*----------------------------------------------------------------------------------------------------------*/

BUTTONPTR custom_button_animations(BUTTONPTR button, CBANIMATIONS cb, float limit, BUTTON_CALLBACK bcall,
                                   void *data)
{
    const int dx = 10, dy = 10;
    switch(cb)
    {
        case BNONE:
        break;
        case BRIGHT:
        {
            if(button->bdata.x < limit)
                button->bdata.x += dx;
            else
            {
                button->bdata.x = limit;
                button->bdata.ox = limit;
                bcall(button, data, CBANIMATION_CALL);
                button->bdata.aflags = BNONE;
            }
        }
        break;
        case BLEFT:
        {
            if(button->bdata.x > limit)
                button->bdata.x -= dx;
            else
            {
                button->bdata.x = limit;
                button->bdata.ox = limit;
                bcall(button, data, CBANIMATION_CALL);
                button->bdata.aflags = BNONE;
            }
        }
        break;
        case BUP:
        {
            if(button->bdata.y > limit)
                button->bdata.y -= dy;
            else
            {
                button->bdata.y = limit;
                button->bdata.oy = limit;
                bcall(button, data, CBANIMATION_CALL);
                button->bdata.aflags = BNONE;
            }
        }
        break;
        case BDOWN:
        {
            if(button->bdata.y < limit)
                button->bdata.y += dy;
            else
            {
                button->bdata.y = limit;
                button->bdata.oy = limit;
                bcall(button, data, CBANIMATION_CALL);
                button->bdata.aflags = BNONE;
            }
        }
        break;
        default:
        break;
    }
    return button;
}

/*----------------------------------------------------------------------------------------------------------*/

SBANIMATIONS set_standard_button_animation(SBANIMATIONS sb_new)
{
    sb = sb_new;
    return sb;
}

/*----------------------------------------------------------------------------------------------------------*/

SBANIMATIONS get_standard_button_animation(void)
{
    return sb;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool is_mouse_over_button(ALLEGRO_MOUSE_STATE *mouse, BUTTONPTR currentptr)
{
    if((mouse->x >= currentptr->bdata.x && mouse->x  <= (currentptr->bdata.x+currentptr->bimage->width)) &&
       (mouse->y >= currentptr->bdata.y && mouse->y <= (currentptr->bdata.y+currentptr->bimage->height)))
        return true;
    else
        return false;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool is_point_over_button(int x, int y, BUTTONPTR currentptr)
{
    if((x >= currentptr->bdata.x && x  <= (currentptr->bdata.x+currentptr->bimage->width)) &&
       (y >= currentptr->bdata.y && y <= (currentptr->bdata.y+currentptr->bimage->height)))
        return true;
    else
        return false;
}

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR create_new_button_image_list(char *labels[], char *images[], int num_elements)
{
    BIMAGESPTR newptr;
    int i;

    for(i = 0; i < num_elements; i++)
    {
        if((newptr = (BIMAGESPTR)malloc(sizeof(BIMAGES))) == NULL) return NULL;
        newptr->label = labels[i];
        newptr->button_image = al_load_bitmap(images[i]);
        newptr->width = al_get_bitmap_width(newptr->button_image);
        newptr->height = al_get_bitmap_height(newptr->button_image);
        add_element_to_button_image_list(&bitoptr, &newptr);
    }
    return bitoptr;
}

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR add_element_to_button_image_list(BIMAGESPTR *firstptr, BIMAGESPTR *newptr)
{
    BIMAGESPTR currentptr;
    if(*firstptr != NULL)
    {
        currentptr = (*firstptr)->prevbimage;
        currentptr->nextbimage = *newptr;
        (*newptr)->prevbimage = currentptr;
        (*firstptr)->prevbimage = *newptr;
        (*newptr)->nextbimage = *firstptr;
    }
    else
    {
        *firstptr = *newptr;
        (*newptr)->nextbimage = *newptr;
        (*newptr)->prevbimage = *newptr;
    }
    return *newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

BIMAGESPTR search_button_image_list_for_element(BIMAGESPTR firstptr, char *label)
{
    BIMAGESPTR currentptr = firstptr;
    if(currentptr == NULL) return NULL;
    do
    {
        if(strcmp(currentptr->label, label) == 0) break;
        currentptr = currentptr->nextbimage;
    } while(currentptr != firstptr);

    if(strcmp(currentptr->label, label) != 0) return NULL;
    return currentptr;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
