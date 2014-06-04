#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "utility.h"

/**
* Implementation of utility prototypes in utility.h
* @author Alex Cole
*/

/**
* @brief removes leading and trailing whitespace
* @param str the string that needs to be trimmed
*/
void trim(char **str)
{
	if(*str == NULL) { return; }
	left_trim(str);
	right_trim(str);
}

/**
* @brief removes leading whitespace
* @param str the string that needs leading whitespace removed
*/
void left_trim(char **str)
{
	int i;
	char *temp;
	size_t length;
	
	length = strlen(*str);
	i = 0;
	while(i < length && ((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\r'))
	{
		i++;
	}
	if(i != 0)
	{
		/*creates temp string to store non-leading-whitespace string*/
		temp = (char*) malloc(sizeof(char) * (length - i) + 1);
		temp[0] = '\0';
		strncat(temp, *str + i, (length - i));

		/*copies temp to original string*/
		(*str)[0] = '\0';
		strncat(*str, temp, strlen(temp));
		free(temp);
	}
}

/**
* @brief removes trailing whitespace
* @ param str the string that needs tailing whitespace removed
*/
void right_trim(char **str)
{
	int i;

	i = strlen(*str) - 1;
	while(i >= 0)
	{
		if((*str)[i] == ' ' || (*str)[i] == '\t' || (*str)[i] == '\n' || (*str)[i] == '\r')
		{
			i--;
		}
		else
		{
			(*str)[i + 1] = '\0';
			return;
		}
	}
	(*str)[i + 1] = '\0';
}

/**
* @brief counts the number of words in the value portion of a file
* with the given keyword to identify which line to read. Default count is 0.
* @param ifp the file to be read
* @param name the keyword to find the line
* @param count counts the number of works in the value
*/
void get_count(FILE *ifp, char *name, int *count)
{
	char *value;
	char *occurrence;

	*count = 0;
	get_value(ifp, &value, name);
	if(value != NULL)
	{
		occurrence = strtok(value, " ");
		while(occurrence != NULL)
		{
			(*count)++;
			occurrence = strtok(NULL, " ");
		}
	}
	free(value);
}

/**
* @brief gets the value portion of a line and store it in
* dest. Determines which line to get the value by target name.
* The default value for dest is NULL.
* @param ifp the file to be read
* @param dest the location for the value to be stored
* @param name the keyword to find the line
*/
void get_value(FILE *ifp, char **dest, char *name)
{
	char *variable;
	char *value;
	char line[1000];

	fseek(ifp, 0, SEEK_SET);
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
		variable = strtok(line, ":");
		trim(&variable);
		value = strtok(NULL, ":");
		trim(&value);
		if(is_valid_line(variable, value) && !strcasecmp(variable, name))
		{
			set_string_value(dest, value);
			return;
		}
	}
	*dest = NULL;
}

/**
* @brief copies the src string into the dest string
* @param dest the location for the src to be store
* @param src the string to be stored
*/
void set_string_value(char **dest, char *src)
{
	size_t length;

	length = strlen(src) + 1;
	*dest = (char*)malloc(sizeof(char) * length);
	*dest[0] = '\0';
	strncat(*dest, src, length - 1);
}

/**
* @brief checks to see if line is valid format: var:value
* @return non-zero value if line is valid and 0 if line is invalid
*/
int is_valid_line(char *variable, char *value)
{
	return !str_is_empty_or_null(variable) && !str_is_empty_or_null(value);
}

/**
* @brief checks to see if the string is null or empty
* @return non-zero value if null or empty and 0 if not
*/
int str_is_empty_or_null(char *str)
{
	return str == NULL || !strcasecmp(str, "");
}
