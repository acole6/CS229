#ifndef FSF_H
#define FSF_H

/**
 * fsf file data structures defined and function prototypes
 * associated with extracting and storing data to and from fsf data structures
 * @author Alex Cole
 */

/*struct to store character data. ch is the character
position[0] is the x pos, position[1] is the y pos,
position[2] is the width, and position[3] us the height*/
struct character
{
    char ch;
    int position[4];
};
typedef struct character character_t;

/*struct to store fsf file info*/
struct fsf
{
    char *name;
    char *image;
    int num_characters;
    character_t *characters;
};
typedef struct fsf fsf_t;

/**
 * @brief counts the total number of characters. default count is 0.
 * @param ifp the file to read
 * @param count stores the character count
 */
void character_count(FILE *ifp, int *count);

/**
 * @brief initializes all the characters for a given font
 * @param ifp the file the read
 * @param font the font that needs its characters initialized
 * @return 0 if characters successfully filled other 1
 */
int fill_characters(FILE *ifp, fsf_t *font);

/**
 * @brief reads the fsf file and creates fsf data structure
 * @param name the name of the file
 * @param font the struct to store the data from the file
 * @return 0 if the file was read successfully and 1 if there was an
 * error while reading the file
 */
int read_fsf_file(char *name, fsf_t *font);

/**
 * @brief finds a character based on the given character in an array of
 * characters
 * @param characters an array of character structs
 * @param length how many items are in the array
 * @param ch the character to be found
 * @return a character_t struct with the data for that character
 */
character_t* get_character(character_t *characters, int length, char ch);

/**
 * @brief calculates the width of a phrase
 * @param characters an array of character structs
 * @param how many items are in the array
 * @param phrase the text phrase
 * @return returns the width of the given phrase. default value is 0
 */
int get_phrase_width(character_t *characters, int length, char *phrase);

/**
 * @brief gets the height of the characters
 * @param characters an array of character stucts
 * @return the height of the characters. Default is 0
 */
int get_height(character_t *characters);

/**
 * @brief initializes the font struct
 * @param font the struct to be initialized
 */
void initialize_fsf(fsf_t *font);

/**
 * @brief frees memory used by font struct
 * @param font the struct to be freed
 */
void deallocate_fsf(fsf_t *font);

/**
 * @brief finds a with the given name
 * @param font_names an array of font names
 * @param target the name of the font to find
 * @param length the number of items in the array
 * @return a font struct if fount otherwise an initialized
 * empty font struct
 */
fsf_t get_font(char **font_names, char *target, int length);

#endif
