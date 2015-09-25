#ifndef MEM_H
#define MEM_H

/**
 * mem file data structures defined and function prototypes
 * associated with extracting and storing data to and from mem data structures
 * @author Alex Cole
 */

/*point struct to store width (x) and height (y)*/
struct point
{
    int x;
    int y;
};
typedef struct point point_t;

/*struct to store text position*/
struct position
{
    char *name;
    point_t startpoint;
};
typedef struct position position_t;

/*struct to store a meme*/
struct s_meme
{
    char *name;
    char *file;
    int num_pos;
    position_t *positions;
};
typedef struct s_meme meme_t;

/*data structure to store mem file info*/
struct mem
{
    int num_memes;
    int num_fonts;
    meme_t *memes;
    char **fonts;
};
typedef struct mem mem_t;

/**
 * @brief assign values to the memes specified in the
 * mem file.
 * @param ifp the file to read
 * @param meme the mem struct
 * @return 0 if the memes were successfully filled otherwise 1
 * if an error occurred
 */
int fill_memes(FILE *ifp, mem_t *meme);

/**
 * @brief sets the name for each meme
 * @param ifp the file to read
 * @param memes an array of memes
 * @param length the number of items in the array
 */
void fill_meme_names(FILE *ifp, meme_t **memes, int length);

/**
 * @brief counts the text positions and sets the file
 * for each meme.
 * @param ifp the file to read
 * @param meme struct that has the memes stored in it
 * @return 0 if file was successfully set otherwise 1
 * is returned if the file is not given
 */
int count_num_and_set_file(FILE *ifp, mem_t *meme);

/**
 * @brief fills in all the text positions for each meme
 * @param ifp the file to read
 * @param meme the struc that stores all the memes
 * @return 0 if positions successfully filled otherwise 1
 */
int fill_meme_positions(FILE *ifp, mem_t *meme);

/**
 * @brief sets all the fonts specified in the mem file
 * @param ifp the file to read
 * @param meme the mem struct
 */
void fill_fonts(FILE *ifp, mem_t *meme);

/**
 * @brief reads, initializes and stores mem file data
 * in mem struct
 * @param name the file name
 * @param meme the struct to store the mem file data
 * @return 0 if the file was read successfully other 1
 * if an error occurred
 */
int read_mem_file(char *name, mem_t *meme);

/**
 * @brief gets the the position by the name given
 * @param positions an array of positions
 * @param length the number of items in the array
 * @param name the name of the position to be found
 * @return the position with the given name or if not
 * found, NULL
 */
position_t* get_position(position_t *positions, int length, char *name);

/**
 * @brief initializes the mem struct
 * @param meme the struct to be initialized
 */
void initialize_mem(mem_t *meme);

/**
 * @brief initialzes the meme struct
 * @param the meme struct to be initialized
 */
void initialize_meme(meme_t *meme);

/**
 * @brief frees the memory allocated for mem struct
 * @param meme the struct to be freed
 */
void deallocate_mem(mem_t *meme);

/**
 * @brief frees the memory allocated for an array of meme structs
 * @param memes the array of meme structs to be freed
 * @param length the number of items in the array
 */
void deallocate_memes(meme_t *memes, int length);

/**
 * @brief frees the memory allocated for an array of position structs
 * @param positions the array of position structs to be freed
 * @length the number of items in the array
 */
void deallocate_positions(position_t *positions, int length);

/**
 * @brief get the meme given the name of the meme
 * @param memes the mem struc that contains all the memes
 * @param target the name of the meme to get
 * @return a meme struct that matches the given name or if not
 * found, an initialized empty meme struct
 */
meme_t get_meme(mem_t *memes, char *target);

#endif
