#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "act.h"
#include "utility.h"

/**
* Implementation of act prototypes in act.h
* @author Alex Cole
*/

/**
* @brief sets the potential count for text ids
* @param ifp the file to read
* @param count the count of text ids
*/
void get_num_ids(FILE *ifp, int *count)
{
	char *variable;
	char line[1000];
	
	*count = 0;
	fseek(ifp, 0, SEEK_SET);
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
		variable = strtok(line, ":");
		trim(&variable);
		if(!str_is_empty_or_null(variable) && strcasecmp(variable, "OUTFILE") && strcasecmp(variable, "MEME") && strcasecmp(variable, "FONT"))
		{
			(*count)++;
		}
	}
}

/**
* @brief fills in the ids and values for each
* of the text ids if they are valid text ids
* @param ifp the file to read
* @param action the act struct to store the text
* ids
*/
void find_text_ids(FILE *ifp, act_t *action)
{
	int i;
	char *variable;
	char *value;
	char line[1000];

	get_num_ids(ifp, &action->num_ids);
	
	i = 0;
	action->lines = (line_t*) malloc(sizeof(line_t) * action->num_ids);
	fseek(ifp, 0, SEEK_SET);
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
		char *temp;
		size_t length;
		if(i >= action->num_ids) break;
		
		length = strlen(line) + 1;
		temp = (char*) malloc(sizeof(char) * length);
		temp[0] = '\0';
		strcat(temp, line);

		variable = strtok(line, ":");
		trim(&variable);

		value = strstr(temp, ":"); /*makes sure text can have ':' in it*/
		if(value != NULL && value[0] == ':') value[0] = ' ';
		trim(&value);
		if(is_valid_line(variable, value) && strcasecmp(variable, "OUTFILE") && strcasecmp(variable, "MEME") && strcasecmp(variable, "FONT"))
		{
			set_string_value(&action->lines[i].id, variable);
			set_string_value(&action->lines[i].value, value);
			i++;
		}
		free(temp);
	}
	action->num_ids = i;
}

/**
* @brief read through the act file, initialize act struct
* and fill in act data structure
* @param name the file name
* @param action the struct to store the act file data
* @return 0 if the file was successfully read and 1 if
* an error occurred.
*/
int read_act_file(char *name, act_t *action)
{
	FILE *in;

	in = fopen(name, "r");
	if(!in)
	{
		fprintf(stderr, "Could not open file: %s\n", name);
		return 1;
	}

	initialize_act(action);
	get_value(in, &action->outfile, "OUTFILE");
	if(action->outfile == NULL)
	{
		fprintf(stderr, "No outfile specified in action file\n");
		fclose(in);
		deallocate_act(action);
		return 1;
	}

	get_value(in, &action->meme, "MEME");
	if(action->meme == NULL)
	{
		fprintf(stderr, "No meme specified in action file\n");
		fclose(in);
		deallocate_act(action);
		return 1;
	}

	get_value(in, &action->font, "FONT");
	if(action->font == NULL)
	{
		fprintf(stderr, "No font specified in action file\n");
		fclose(in);
		deallocate_act(action);
		return 1;
	}

	find_text_ids(in, action);

	fclose(in);
	return 0;
}

/**
* @brief frees memory allocated for act struct
* @param action the struc to be freed
*/
void deallocate_act(act_t *action)
{
	free(action->outfile);
	free(action->meme);
	free(action->font);
	deallocate_line(action->lines, action->num_ids);
}

/**
* @brief frees the memory allocated for line array
* @param lines array of line structs
* @param length the number of items in the array
*/
void deallocate_line(line_t *lines, int length)
{
	int i;
	for(i = 0; i < length; i++)
	{
		free(lines[i].id);
		free(lines[i].value);
	}
	free(lines);
}

/**
* @brief initializes the act struct
* @action the stuct to be initialized
*/
void initialize_act(act_t *action)
{
	action->outfile = NULL;
	action ->meme = NULL;
	action->font = NULL;
	action->num_ids = 0;
	action->lines = NULL;
}
