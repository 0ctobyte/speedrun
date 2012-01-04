#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <chipmunk/chipmunk.h>
#include <sprites.h>

/*----------------------------------------------------------------------------*/

// A pointer to the first sprite in the SPRITE structure linked list
static SPRITESPTR sfirstptr = NULL;

/*----------------------------------------------------------------------------*/

// A pointer to the first base image in the SIMAGE structure linked list
static SIMAGEPTR bifirstptr = NULL;

/*----------------------------------------------------------------------------------------------------------*/

// Returns the first image in the base image list
SIMAGEPTR get_first_element_from_base_image_list(void)
{
    return bifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Sets the first image in the base image list
// Should never be used, only here for internal use
SIMAGEPTR set_first_element_in_base_image_list(SIMAGEPTR *newfirst)
{
    bifirstptr = *newfirst;
    return bifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Creates a new base image list, which cannot be modified after created
// TODO: make sure the list cannot be modified after creation
SIMAGEPTR create_base_image_list(char* labels[], char *images[], int max)
{
    SIMAGEPTR newptr, ifirstptr = NULL;
    int i;

    for(i = 0; i < max; i++)
    {
        if((newptr = create_new_base_image(labels[i], images[i])) == NULL) return NULL;
        add_element_to_image_list(&ifirstptr, &newptr);
    }
    bifirstptr = ifirstptr;
    return bifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Creates a new base image to be added to the base image list
SIMAGEPTR create_new_base_image(char *label, char *file_name)
{
    SIMAGEPTR newptr;
    newptr = (SIMAGEPTR)malloc(sizeof(SIMAGE));
    if(newptr == NULL) return NULL;
    newptr->ilabel = label;
    newptr->image = al_load_bitmap(file_name);
    newptr->width = al_get_bitmap_width(newptr->image);
    newptr->height = al_get_bitmap_height(newptr->image);
    newptr->nextimage = NULL;
    newptr->previmage = NULL;
    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Adds an image to the base image list
SIMAGEPTR add_element_to_base_image_list(SIMAGEPTR *image)
{
    return add_element_to_image_list(&bifirstptr, image);
}

/*----------------------------------------------------------------------------------------------------------*/

// Removes an image from the base image list
SIMAGEPTR remove_element_from_base_image_list(char *label)
{
    SIMAGEPTR currentptr = NULL;
    currentptr = remove_element_from_image_list(&bifirstptr, label);
    if(currentptr == NULL) return NULL;
    return bifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Searches the base image list for the specified image with the corresponding label
SIMAGEPTR search_base_image_list_for_element(char *label)
{
    return search_image_list_for_element(&bifirstptr, label);
}

/*----------------------------------------------------------------------------------------------------------*/

// Empties the list, used only before exiting the program
_Bool empty_base_image_list(SIMAGEPTR firstptr)
{
    SIMAGEPTR currentptr = firstptr;
    if(firstptr != bifirstptr) return false;
    if(firstptr == NULL) return false;
    if(firstptr->nextimage == firstptr && firstptr->previmage == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextimage == firstptr->previmage)
    {
        currentptr = currentptr->nextimage;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextimage;
        firstptr->previmage->nextimage = NULL;
        currentptr->previmage = NULL;
        al_destroy_bitmap(firstptr->image);
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextimage;
            al_destroy_bitmap(firstptr->image);
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
        bifirstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

// Creates a new image list to be used with the SPRITE structure, images are grabbed (i.e. pointers)
// from the base image list, the base image list must not be empty
SIMAGEPTR create_new_image_list(char *labels[], int max)
{
    SIMAGEPTR newptr, ifirstptr = NULL;
    int i;
    for(i = 0; i < max; i++)
    {
        if((newptr = create_new_image(labels[i])) == NULL) return NULL;
        add_element_to_image_list(&ifirstptr, &newptr);
    }
    return ifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// A new image is created using a bitmap from the base image list
SIMAGEPTR create_new_image(char *label)
{
    SIMAGEPTR newptr, currentptr;
    newptr = (SIMAGEPTR)malloc(sizeof(SIMAGE));
    if((currentptr = search_base_image_list_for_element(label)) == NULL) return NULL;
    newptr->ilabel = currentptr->ilabel;
    newptr->image = currentptr->image;
    newptr->width = currentptr->width;
    newptr->height = currentptr->height;
    newptr->nextimage = NULL;
    newptr->previmage = NULL;
    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Adds the specified SIMAGE struct to the specified image list
SIMAGEPTR add_element_to_image_list(SIMAGEPTR *ifirstptr, SIMAGEPTR *image)
{
    SIMAGEPTR currentptr;
    if(*ifirstptr != NULL)
    {
        currentptr = (*ifirstptr)->previmage;
        currentptr->nextimage = *image;
        (*image)->previmage = currentptr;
        (*ifirstptr)->previmage = *image;
        (*image)->nextimage = *ifirstptr;
    }
    else
    {
        *ifirstptr = *image;
        (*image)->nextimage = *image;
        (*image)->previmage = *image;
    }
    return *ifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Removes the specified struct from the specified image list
SIMAGEPTR remove_element_from_image_list(SIMAGEPTR *ifirstptr, char *label)
{
    SIMAGEPTR currentptr = *ifirstptr;
    if(currentptr == NULL) return NULL;
    if((currentptr = search_image_list_for_element(ifirstptr, label)) == NULL) return *ifirstptr;
    currentptr->nextimage->previmage = currentptr->previmage;
    currentptr->previmage->nextimage = currentptr->nextimage;
    if(currentptr == *ifirstptr)
        *ifirstptr = currentptr->nextimage;
    free(currentptr);
    return *ifirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

// Searches the specified list for the SIMAGE with the given label
SIMAGEPTR search_image_list_for_element(SIMAGEPTR *ifirstptr, char *label)
{
    SIMAGEPTR currentptri = *ifirstptr;
    if(currentptri == NULL) return NULL;
    do
    {
        if(strcmp(currentptri->ilabel, label) == 0) break;
        currentptri = currentptri->nextimage;
    } while(currentptri != *ifirstptr);
    if(strcmp(currentptri->ilabel, label) != 0) return NULL;
    return currentptri;
}

/*----------------------------------------------------------------------------------------------------------*/

// Empties an image list
_Bool empty_image_list(SIMAGEPTR firstptr)
{
    SIMAGEPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextimage == firstptr && firstptr->previmage == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextimage == firstptr->previmage)
    {
        currentptr = currentptr->nextimage;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextimage;
        firstptr->previmage->nextimage = NULL;
        currentptr->previmage = NULL;
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextimage;
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR create_new_datax_list(char *labels[], char *types[], void *data[], int max)
{
    SDATAXPTR newptr, dfirstptr = NULL;
    int i;
    for(i = 0; i < max; i++)
    {
        newptr = create_new_datax(labels[i], types[i], data[i]);
        add_element_to_datax_list(&dfirstptr, &newptr);
    }
    return dfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR create_new_datax(char *label, char *type, void *data)
{
    SDATAXPTR newptr;
    if((newptr = (SDATAXPTR)malloc(sizeof(SDATAX))) == NULL) return NULL;
    newptr->dlabel = label;
    newptr->dtype = type;
    newptr->data = data;
    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR add_element_to_datax_list(SDATAXPTR *dfirstptr, SDATAXPTR *datax)
{
    SDATAXPTR currentptr;
    if(*dfirstptr != NULL)
    {
        currentptr = (*dfirstptr)->prevdata;
        currentptr->nextdata = *datax;
        (*datax)->prevdata = currentptr;
        (*dfirstptr)->prevdata = *datax;
        (*datax)->nextdata = *dfirstptr;
    }
    else
    {
        *dfirstptr = *datax;
        (*datax)->nextdata = *datax;
        (*datax)->prevdata = *datax;
    }
    return *dfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR remove_element_from_datax_list(SDATAXPTR *dfirstptr, char *label)
{
    SDATAXPTR currentptr = *dfirstptr;
    if(currentptr == NULL) return NULL;
    if((currentptr = search_datax_list_for_element(dfirstptr, label)) == NULL) return *dfirstptr;
    currentptr->nextdata->prevdata = currentptr->prevdata;
    currentptr->prevdata->nextdata = currentptr->nextdata;
    if(currentptr == *dfirstptr)
        *dfirstptr = currentptr->nextdata;
    free(currentptr);
    return *dfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SDATAXPTR search_datax_list_for_element(SDATAXPTR *dfirstptr, char *label)
{
    SDATAXPTR currentptr = *dfirstptr;
    if(currentptr == NULL) return NULL;
    do
    {
        if(strcmp(currentptr->dlabel, label) == 0) break;
        currentptr = currentptr->nextdata;
    } while(currentptr != *dfirstptr);
    if(strcmp(currentptr->dlabel, label) != 0) return NULL;
    return currentptr;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_datax_list(SDATAXPTR firstptr)
{
    SDATAXPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextdata == firstptr && firstptr->prevdata == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextdata == firstptr->prevdata)
    {
        currentptr = currentptr->nextdata;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextdata;
        firstptr->prevdata->nextdata = NULL;
        currentptr->prevdata = NULL;
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextdata;
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
    return true;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR get_first_element_from_sprite_list(void)
{
    return sfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR set_first_element_in_sprite_list(SPRITESPTR *newfirst)
{
    sfirstptr = *newfirst;
    return sfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR create_new_sprite(char *label, char *imagelabels[], int num_images,
                             char *datalabels[], char *datatypes[], void *data[],
                             int num_data, char *currentimg, float x, float y,
                             float dx, float dy, int anim_counter, ANIMATION animflags,
                             _Bool add_to_list)
{
    SPRITESPTR newptr;

    if((newptr = (SPRITESPTR)malloc(sizeof(SPRITES))) == NULL) return NULL;
    newptr->slabel = label;
    newptr->ifirstptr = create_new_image_list(imagelabels, num_images);
    newptr->dfirstptr = create_new_datax_list(datalabels, datatypes, data, num_data);
    newptr->sdata.currentimg = (search_image_list_for_element(&(newptr->ifirstptr), currentimg));
    newptr->sdata.x = x;
    newptr->sdata.y = y;
    newptr->sdata.dx = dx;
    newptr->sdata.dy = dy;
    newptr->sdata.anim_counter = anim_counter;
    newptr->sdata.animflags = animflags;

    if(add_to_list)
        add_element_to_sprite_list(&newptr);
    return newptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR add_element_to_sprite_list(SPRITESPTR *sprite)
{
    SPRITESPTR currentptr;
    if(sfirstptr == NULL)
    {
        sfirstptr = *sprite;
        (*sprite)->nextsprite = *sprite;
        (*sprite)->prevsprite = *sprite;
    }
    else
    {
        currentptr = sfirstptr->prevsprite;
        currentptr->nextsprite = *sprite;
        (*sprite)->prevsprite = currentptr;
        sfirstptr->prevsprite = *sprite;
        (*sprite)->nextsprite = sfirstptr;
    }
    return sfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_element_from_sprite_list(char *label)
{
    SPRITESPTR currentptr;
    currentptr = sfirstptr;
    if(currentptr == NULL || sfirstptr == NULL) return NULL;
    if((currentptr = search_sprite_list_for_element(label)) == NULL) return sfirstptr;
    currentptr->nextsprite->prevsprite = currentptr->prevsprite;
    currentptr->prevsprite->nextsprite = currentptr->nextsprite;
    if(currentptr == sfirstptr)
        sfirstptr = currentptr->nextsprite;
    free(currentptr);
    return sfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_element_from_sprite_list_ptr(SPRITESPTR sprite)
{
    SPRITESPTR currentptr;
    currentptr = sfirstptr;
    if(currentptr == NULL || sfirstptr == NULL) return NULL;
    if((currentptr = sprite) == NULL) return sfirstptr;
    currentptr->nextsprite->prevsprite = currentptr->prevsprite;
    currentptr->prevsprite->nextsprite = currentptr->nextsprite;
    if(currentptr == sfirstptr)
        sfirstptr = currentptr->nextsprite;
    free(currentptr);
    return sfirstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR search_sprite_list_for_element(char *label)
{
    SPRITESPTR currentptr = sfirstptr;
    if(currentptr == NULL) return NULL;
    do
    {
        if(strcmp(currentptr->slabel, label) == 0) break;
        currentptr = currentptr->nextsprite;
    } while(currentptr != sfirstptr);
    if(strcmp(currentptr->slabel, label) != 0) return NULL;
    return currentptr;
}

/*----------------------------------------------------------------------------------------------------------*/

_Bool empty_sprite_list(SPRITESPTR firstptr)
{
    SPRITESPTR currentptr = firstptr;
    if(firstptr == NULL) return false;
    if(firstptr->nextsprite == firstptr && firstptr->prevsprite == firstptr)
    {
        free(firstptr);
        firstptr = NULL;
    }
    else if(firstptr->nextsprite == firstptr->prevsprite)
    {
        currentptr = currentptr->nextsprite;
        free(firstptr);
        free(currentptr);
        firstptr = NULL;
    }
    else
    {
        currentptr = currentptr->nextsprite;
        firstptr->prevsprite->nextsprite = NULL;
        currentptr->prevsprite = NULL;
        empty_image_list(firstptr->ifirstptr);
        empty_datax_list(firstptr->dfirstptr);
        free(firstptr);
        firstptr = currentptr;

        while(currentptr != NULL)
        {
            currentptr = currentptr->nextsprite;
            empty_image_list(firstptr->ifirstptr);
            empty_datax_list(firstptr->dfirstptr);
            free(firstptr);
            firstptr = currentptr;
        }
        firstptr = NULL;
    }
     return true;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR set_anim_flags_on_sprite(SPRITESPTR sprite, ANIMATION nflags)
{
    if((nflags & MLEFT))
        sprite->sdata.animflags |= MLEFT;
    if((nflags & MRIGHT))
        sprite->sdata.animflags |= MRIGHT;
    if((nflags & MUP))
        sprite->sdata.animflags |= MUP;
    if((nflags & MDOWN))
        sprite->sdata.animflags |= MDOWN;
    if((nflags & MATTACK))
        sprite->sdata.animflags |= MATTACK;
    if((nflags & MDAMAGED))
        sprite->sdata.animflags |= MDAMAGED;
    if((nflags & MRECOVER))
        sprite->sdata.animflags |= MRECOVER;
    if((nflags & MNONE))
        sprite->sdata.animflags |= MNONE;
    return sprite;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_anim_flags_on_sprite(SPRITESPTR sprite, ANIMATION nflags)
{
    if((nflags & MLEFT))
        sprite->sdata.animflags &= ~MLEFT;
    if((nflags & MRIGHT))
        sprite->sdata.animflags &= ~MRIGHT;
    if((nflags & MUP))
        sprite->sdata.animflags &= ~MUP;
    if((nflags & MDOWN))
        sprite->sdata.animflags &= ~MDOWN;
    if((nflags & MATTACK))
        sprite->sdata.animflags &= ~MATTACK;
    if((nflags & MDAMAGED))
        sprite->sdata.animflags &= ~MDAMAGED;
    if((nflags & MRECOVER))
        sprite->sdata.animflags &= ~MRECOVER;
    if((nflags & MNONE))
        sprite->sdata.animflags &= ~MNONE;
    return sprite;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR remove_anim_flags_on_sprite_list(SPRITESPTR firstptr, ANIMATION nflags)
{
    SPRITESPTR currentptr = firstptr;
    do
    {
        remove_anim_flags_on_sprite(currentptr, nflags);
        currentptr = currentptr->nextsprite;
    } while(currentptr != firstptr);
    return firstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR clear_anim_flags_on_sprite(SPRITESPTR sprite)
{
    remove_anim_flags_on_sprite(sprite, MLEFT | MRIGHT | MATTACK | MUP | MDOWN | MDAMAGED | MRECOVER | MNONE);
    set_anim_flags_on_sprite(sprite, MNONE);
    return sprite;
}

/*----------------------------------------------------------------------------------------------------------*/

SPRITESPTR clear_anim_flags_on_sprite_list(SPRITESPTR firstptr)
{
    SPRITESPTR currentptr = firstptr;
    do
    {
        clear_anim_flags_on_sprite(currentptr);
        set_anim_flags_on_sprite(currentptr, MNONE);
        currentptr = currentptr->nextsprite;
    } while(currentptr != firstptr);
    return firstptr;
}

/*----------------------------------------------------------------------------------------------------------*/

//    /**
//      *@}
//      */
