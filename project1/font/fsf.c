#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "fsf.h"
#include "../utility/utility.h"

/**
* Implementation of fsf prototypes in fsf.h
* @author Alex Cole
*/

/**
* @brief counts the total number of characters. default count is 0.
* @param ifp the file to read
* @param count stores the character count
*/
void character_count(FILE *ifp, int *count)
{
	char *variable;
	char line[1000];
	
	*count = 0;
	fseek(ifp, 0, SEEK_SET);
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
		variable = strtok(line, ":");
		trim(&variable);
		if(variable != NULL && !strncasecmp(variable, "CHARACTER", 9)) (*count)++;
	}
}

/**
* @brief initializes all the characters for a given font
* @param ifp the file the read
* @param font the font that needs its characters initialized
* @return 0 if characters successfully filled other 1
*/
int fill_characters(FILE *ifp, fsf_t *font)
{
	int i;
	char *variable;
	char *value;
	char line[1000];
	
	i = 0;
	font->characters = (character_t*) malloc(sizeof(character_t) * font->num_characters);
	fseek(ifp, 0, SEEK_SET);
	while(fgets(line, sizeof(line), ifp) != NULL)
	{
		variable = strtok(line, ":");
		value = strtok(NULL, ":");
		trim(&value);

		if(i >= font->num_characters) break;

		if(is_valid_line(variable, value) && !strncasecmp(variable, "CHARACTER", 9))
		{
			char *num;
			font->characters[i].ch = variable[9] == '\0' ? ':' : variable[9];
			
			num = strtok(value, " ");
			if(num == NULL) 
			{  
				fprintf(stderr, "Invalid character in font file: %c\n", font->characters[i].ch);
				i++;
				font->num_characters = i; 
				return 1; 
			}
			font->characters[i].position[0] = atoi(num);
			
			num = strtok(NULL, " ");
			if(num == NULL) 
			{  
				fprintf(stderr, "Invalid character in font file: %c\n", font->characters[i].ch);
				i++;
				font->num_characters = i; 
				return 1; 
			}
			font->characters[i].position[1] = atoi(num);
			
			num = strtok(NULL, " ");
			if(num == NULL) 
			{  
				fprintf(stderr, "Invalid character in font file: %c\n", font->characters[i].ch);
				i++;
				font->num_characters = i; 
				return 1; 
			}
			font->characters[i].position[2] = atoi(num);
			
			num = strtok(NULL, " ");
			if(num == NULL) 
			{  
				fprintf(stderr, "Invalid character in font file: %c\n", font->characters[i].ch);
				i++;
				font->num_characters = i; 
				return 1; 
			}
			font->characters[i].position[3] = atoi(num);
			i++;
		}
	}
	font->num_characters = i;
	return 0;
}

/**
* @brief reads the fsf file and creates fsf data structure
* @param name the name of the file
* @param font the struct to store the data from the file
* @return 0 if the file was read successfully and 1 if there was an
* error while reading the file
*/
int read_fsf_file(char *name, fsf_t *font)
{
	FILE *in;

	in = fopen(name, "r");
	if(!in)
	{
		fprintf(stderr, "Could not open file: %s\n", name);
		return 1;
	}

	initialize_fsf(font);
	get_value(in, &font->name, "NAME");
	if(font->name == NULL)
	{
		fprintf(stderr, "No name specified in font file\n");
		fclose(in);
		deallocate_fsf(font);
		return 1;
	}
	get_value(in, &font->image, "IMAGE");
	if(font->image == NULL)
	{
		fprintf(stderr, "No image specified in font file\n");
		fclose(in);
		deallocate_fsf(font);
		return 1;
	}
	character_count(in, &font->num_characters);
	if(fill_characters(in, font) != 0)
	{
		fclose(in);
		deallocate_fsf(font);
		return 1;
	}

	fclose(in);
	return 0;
}

/**
* @brief finds a character based on the given character in an array of
* characters
* @param characters an array of character structs
* @param length how many items are in the array
* @param ch the character to be found
* @return a character_t struct with the data for that character
*/
character_t* get_character(character_t *characters, int length, char ch)
{
	int i;
	for(i = 0; i < length; i++)
	{
		if(characters[i].ch == ch) return &characters[i];
	}
	return NULL;
}

/**
* @brief calculates the width of a phrase
* @param characters an array of character structs
* @param how many items are in the array
* @param phrase the text phrase
* @return returns the width of the given phrase. default value is 0
*/
int get_phrase_width(character_t *characters, int length, char *phrase)
{
	character_t *character;
	size_t phrase_length;
	int width, i;

	width = 0;
	phrase_length = strlen(phrase);
	for(i = 0; i < phrase_length; i++)
	{
		character = get_character(characters, length, phrase[i]);
		if(character != NULL) width += character->position[2];
	}
	return width;
}

/**
* @brief gets the height of the characters
* @param characters an array of character stucts
* @return the height of the characters. Default is 0
*/
int get_height(character_t *characters)
{
	if(characters != NULL)
	{
		return characters[0].position[3];
	}
	else
	{
		return 0;
	}
}

/**
* @brief initializes the font struct
* @param font the struct to be initialized
*/
void initialize_fsf(fsf_t *font)
{
	font->name = NULL;
	font->image = NULL;
	font->num_characters = 0;
	font->characters = NULL;
}

/**
* @brief frees memory used by font struct
* @param font the struct to be freed
*/
void deallocate_fsf(fsf_t *font)
{
	free(font->name);
	free(font->image);
	free(font->characters);
}

/**
* @brief finds a with the given name
* @param font_names an array of font names
* @param target the name of the font to find
* @param length the number of items in the array
* @return a font struct if fount otherwise an initialized
* empty font struct
*/
fsf_t get_font(char **font_names, char *target, int length)
{
	fsf_t ret;
	int i;

	for(i = 0; i < length; i++)
	{
		if(read_fsf_file(font_names[i], &ret) == 0)
		{
			if(ret.name != NULL && !strcasecmp(ret.name, target))
			{
				return ret;
			}
			else
			{
				deallocate_fsf(&ret);
			}
		}
	}
	initialize_fsf(&ret);
	return ret;
}
