#ifndef UTILITY_H
#define UTILITY_H

/**
* function prototypes for functions that can be used by all programs 
* @author Alex Cole
*/

/**
* @brief removes leading and trailing whitespace
* @param str the string that needs to be trimmed
*/
void trim(char **str);

/**
* @brief removes leading whitespace
* @param str the string that needs leading whitespace removed
*/
void left_trim(char **str);

/**
* @brief removes trailing whitespace
* @ param str the string that needs tailing whitespace removed
*/
void right_trim(char **str);

/**
* @brief counts the number of words in the value portion of a file
* with the given keyword to identify which line to read. Default count is 0.
* @param ifp the file to be read
* @param name the keyword to find the line
* @param count counts the number of works in the value
*/
void get_count(FILE *ifp, char *name, int *count);

/**
* @brief gets the value portion of a line and store it in
* dest. Determines which line to get the value by target name.
* The default value for dest is NULL.
* @param ifp the file to be read
* @param dest the location for the value to be stored
* @param name the keyword to find the line
*/
void get_value(FILE *ifp, char **dest, char *name);

/**
* @brief copies the src string into the dest string
* @param dest the location for the src to be store
* @param src the string to be stored
*/
void set_string_value(char **dest, char *src);

/**
* @brief checks to see if line is valid format: var:value
* @return non-zero value if line is valid and 0 if line is invalid
*/
int is_valid_line(char *variable, char *value);

/**
* @brief checks to see if the string is null or empty
* @return non-zero value if null or empty and 0 if not
*/
int str_is_empty_or_null(char *str);

#endif
