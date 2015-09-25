#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "mem.h"
#include "../utility/utility.h"

/**
 * Implementation of mem prototypes in mem.h
 * @author Alex Cole
 */

/**
 * @brief assign values to the memes specified in the
 * mem file.
 * @param ifp the file to read
 * @param meme the mem struct
 * @return 0 if the memes were successfully filled otherwise 1
 * if an error occurred
 */
int fill_memes(FILE *ifp, mem_t *meme)
{
    fill_meme_names(ifp, &meme->memes, meme->num_memes);

    if(count_num_and_set_file(ifp, meme) != 0)
    {
        deallocate_mem(meme);
        fclose(ifp);
        return 1;
    }

    if(fill_meme_positions(ifp, meme) != 0)
    {
        deallocate_mem(meme);
        fclose(ifp);
        return 1;
    }

    return 0;
}

/**
 * @brief sets the name for each meme
 * @param ifp the file to read
 * @param memes an array of memes
 * @param length the number of items in the array
 */
void fill_meme_names(FILE *ifp, meme_t **memes, int length)
{
    char *value;

    get_value(ifp, &value, "MEMES");
    if(value != NULL)
    {
        int i;
        char *meme;

        meme = strtok(value, " ");
        *memes = (meme_t*) malloc(sizeof(meme_t) * length);
        for(i = 0; i < length; i++)
        {
            initialize_meme(&(*memes)[i]);
            set_string_value(&((*memes)[i].name), meme);
            meme = strtok(NULL, " ");
        }
    }
    free(value);
}

/**
 * @brief counts the text positions and sets the file
 * for each meme.
 * @param ifp the file to read
 * @param meme struct that has the memes stored in it
 * @return 0 if file was successfully set otherwise 1
 * is returned if the file is not given
 */
int count_num_and_set_file(FILE *ifp, mem_t *meme)
{
    int i, error;
    char *variable;
    char *meme_variable;
    char *value;
    char line[1000];

    error = 0;
    for(i = 0; i < meme->num_memes; i++)
    {
        meme->memes[i].num_pos = 0;
        fseek(ifp, 0, SEEK_SET);
        while(fgets(line, sizeof(line), ifp) != NULL)
        {
            variable = strtok(line, ":");
            trim(&variable);

            value = strtok(NULL, ":");
            trim(&value);

            meme_variable = is_valid_line(variable, value) ? strtok(variable, " ") : NULL;
            if(meme_variable != NULL && !strcasecmp(meme_variable, meme->memes[i].name))
            {
                meme_variable = strtok(NULL, " ");
                if(meme_variable != NULL && !strcasecmp(meme_variable, "FILE"))
                {
                    set_string_value(&meme->memes[i].file, value);
                }
                else
                {
                    meme->memes[i].num_pos++;
                }
            }
        }
        if(meme->memes[i].file == NULL)
        {
            fprintf(stderr, "No file specified for meme: %s\n", meme->memes[i].name);
            error = 1;
        }
    }

    /*if any of the memes did not have a file specified for it, it results in an error
    and the number of positions must be set back to 0*/
    if(error)
    {
        for(i = 0; i < meme->num_memes; i++)
        {
            meme->memes[i].num_pos = 0;
        }
        return 1;
    }

    return 0;
}

/**
 * @brief fills in all the text positions for each meme
 * @param ifp the file to read
 * @param meme the struc that stores all the memes
 * @return 0 if positions successfully filled otherwise 1
 */
int fill_meme_positions(FILE *ifp, mem_t *meme)
{
    int i, j;
    char *variable;
    char *meme_variable;
    char *value;
    char line[1000];

    for(i = 0; i < meme->num_memes; i++)
    {
        j = 0;
        meme->memes[i].positions = (position_t*) malloc(sizeof(position_t) * meme->memes[i].num_pos);
        fseek(ifp, 0, SEEK_SET);
        while(fgets(line, sizeof(line), ifp) != NULL)
        {
            if(j >= meme->memes[i].num_pos) break;

            variable = strtok(line, ":");
            trim(&variable);

            value = strtok(NULL, ":");
            trim(&value);

            meme_variable = is_valid_line(variable, value) ? strtok(variable, " ") : NULL;
            if(meme_variable != NULL && !strcasecmp(meme_variable, meme->memes[i].name))
            {
                meme_variable = strtok(NULL, " ");
                if(meme_variable != NULL && strcasecmp(meme_variable, "FILE"))
                {
                    char *num;
                    set_string_value(&meme->memes[i].positions[j].name, meme_variable);

                    num = strtok(value, " ");
                    if(num == NULL)
                    {
                        fprintf(stderr, "Missing position value: %s\n", meme->memes[i].positions[j].name);
                        j++;
                        meme->memes[i].num_pos = j;
                        return 1;
                    }
                    meme->memes[i].positions[j].startpoint.x = atoi(num);

                    num = strtok(NULL, " ");
                    if(num == NULL)
                    {
                        fprintf(stderr, "Missing position value: %s\n", meme->memes[i].positions[j].name);
                        j++;
                        meme->memes[i].num_pos = j;
                        return 1;
                    }
                    meme->memes[i].positions[j].startpoint.y = atoi(num);
                    j++;
                }
            }
        }
        meme->memes[i].num_pos = j;
    }
    return 0;
}

/**
 * @brief sets all the fonts specified in the mem file
 * @param ifp the file to read
 * @param meme the mem struct
 */
void fill_fonts(FILE *ifp, mem_t *meme)
{
    char *value;

    get_value(ifp, &value, "FONTS");
    if(value != NULL)
    {
        int i;
        char *font;

        font = strtok(value, " ");
        meme->fonts = (char**) malloc(sizeof(char*) * meme->num_fonts);
        for(i = 0; i < meme->num_fonts; i++)
        {
            set_string_value(&meme->fonts[i], font);
            font = strtok(NULL, " ");
        }
    }
    free(value);
}

/**
 * @brief reads, initializes and stores mem file data
 * in mem struct
 * @param name the file name
 * @param meme the struct to store the mem file data
 * @return 0 if the file was read successfully other 1
 * if an error occurred
 */
int read_mem_file(char *name, mem_t *meme)
{
    FILE *in;

    in = fopen(name, "r");
    if(!in)
    {
        fprintf(stderr, "Could not open file: %s\n", name);
        return 1;
    }

    initialize_mem(meme);
    get_count(in, "MEMES", &meme->num_memes);
    if(meme->num_memes)
    {
        if(fill_memes(in, meme) != 0) { return 1; }
    }
    else
    {
        fprintf(stderr, "Meme file had no memes\n");
        fclose(in);
        deallocate_mem(meme);
        return 1;
    }

    get_count(in, "FONTS", &meme->num_fonts);
    if(meme->num_fonts)
    {
        fill_fonts(in, meme);
    }
    else
    {
        fprintf(stderr, "Meme file had no fonts\n");
        fclose(in);
        deallocate_mem(meme);
        return 1;
    }

    fclose(in);
    return 0;
}

/**
 * @brief gets the the position by the name given
 * @param positions an array of positions
 * @param length the number of items in the array
 * @param name the name of the position to be found
 * @return the position with the given name or if not
 * found, NULL
 */
position_t* get_position(position_t *positions, int length, char *name)
{
    int i;

    for(i = 0; i < length; i++)
    {
        if(!strcasecmp(positions[i].name, name)) return &positions[i];
    }
    return NULL;
}

/**
 * @brief initializes the mem struct
 * @param meme the struct to be initialized
 */
void initialize_mem(mem_t *meme)
{
    meme->num_memes = 0;
    meme->num_fonts = 0;
    meme->memes = NULL;
    meme->fonts = NULL;
}

/**
 * @brief initialzes the meme struct
 * @param the meme struct to be initialized
 */
void initialize_meme(meme_t *meme)
{
    meme->name = NULL;
    meme->file = NULL;
    meme->num_pos = 0;
    meme->positions = NULL;
}

/**
 * @brief frees the memory allocated for mem struct
 * @param meme the struct to be freed
 */
void deallocate_mem(mem_t *meme)
{
    int i;
    for(i = 0; i < meme->num_fonts; i++)
    {
        free(meme->fonts[i]);
    }
    free(meme->fonts);
    deallocate_memes(meme->memes, meme->num_memes);
}

/**
 * @brief frees the memory allocated for an array of meme structs
 * @param memes the array of meme structs to be freed
 * @param length the number of items in the array
 */
void deallocate_memes(meme_t *memes, int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
        free(memes[i].name);
        free(memes[i].file);
        deallocate_positions(memes[i].positions, memes[i].num_pos);
    }
    free(memes);
}

/**
 * @brief frees the memory allocated for an array of position structs
 * @param positions the array of position structs to be freed
 * @length the number of items in the array
 */
void deallocate_positions(position_t *positions, int length)
{
    int i;
    if(positions != NULL)
    {
        for(i = 0; i < length; i++)
        {
            free(positions[i].name);
        }
    }
    free(positions);
}

/**
 * @brief get the meme given the name of the meme
 * @param memes the mem struc that contains all the memes
 * @param target the name of the meme to get
 * @return a meme struct that matches the given name or if not
 * found, an initialized empty meme struct
 */
meme_t get_meme(mem_t *memes, char *target)
{
    int i;
    meme_t ret;

    for(i = 0; i < memes->num_memes; i++)
    {
        if(!strcasecmp(memes->memes[i].name, target)) return memes->memes[i];
    }
    initialize_meme(&ret);
    return ret;
}
