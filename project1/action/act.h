#ifndef ACT_H
#define ACT_H

/**
 * act file data structures defined and function prototypes
 * associated with extracting and storing data to and from act data structures
 * @author Alex Cole
 */

/*struct stores text id and the text in value*/
struct line
{
    char *id;
    char *value;
};
typedef struct line line_t;

/*act struct stores act file info*/
struct act
{
    char *outfile;
    char *meme;
    char *font;
    int num_ids;
    line_t *lines;
};
typedef struct act act_t;

/**
 * @brief sets the potential count for text ids
 * @param ifp the file to read
 * @param count the count of text ids
 */
void get_num_ids(FILE *ifp, int *count);

/**
 * @brief fills in the ids and values for each
 * of the text ids if they are valid text ids
 * @param ifp the file to read
 * @param action the act struct to store the text
 * ids
 */
void find_text_ids(FILE *ifp, act_t *action);

/**
 * @brief read through the act file, initialize act struct
 * and fill in act data structure
 * @param name the file name
 * @param action the struct to store the act file data
 * @return 0 if the file was successfully read and 1 if
 * an error occurred.
 */
int read_act_file(char *name, act_t *action);

/**
 * @brief frees memory allocated for act struct
 * @param action the struc to be freed
 */
void deallocate_act(act_t *action);

/**
 * @brief frees the memory allocated for line array
 * @param lines array of line structs
 * @param length the number of items in the array
 */
void deallocate_line(line_t *lines, int length);

/**
 * @brief initializes the act struct
 * @action the stuct to be initialized
 */
void initialize_act(act_t *action);

#endif
