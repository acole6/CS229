#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "act.h"
#include "fsf.h"
#include "mem.h"
#include "simp.h"

int main(int argc, char *argv[])
{
	mem_t memes;
	act_t action;
	fsf_t font;
	meme_t meme;
	simp_t image, font_image, crop_image;
	int i, j;
	
	if(argc != 3)
	{
		fprintf(stderr, "Usage: ./meme memefile actionfile\n");
		return 1;
	}
	
	if(read_mem_file(argv[1], &memes) != 0) return 1; 
	
	if(read_act_file(argv[2], &action) != 0) 
	{ 
		deallocate_mem(&memes);
		return 1; 
	}
	
	font = get_font(memes.fonts, action.font, memes.num_fonts);
	if(font.name == NULL)
	{
		fprintf(stderr, "Could not find font specified in action file: %s\n", action.font);
		deallocate_fsf(&font);
		deallocate_act(&action);
		deallocate_mem(&memes);
		return 1;
	}

	meme = get_meme(&memes, action.meme);
	if(meme.name == NULL)
	{
		fprintf(stderr, "Count not find meme specified in action file: %s\n", action.meme);
		deallocate_fsf(&font);
		deallocate_act(&action);
		deallocate_mem(&memes);
		return 1;
	}
	
	if(read_simp_file(meme.file, &image) != 0) 
	{ 
		deallocate_fsf(&font);
		deallocate_act(&action);
		deallocate_mem(&memes);
		return 1; 
	}
	
	if(read_simp_file(font.image, &font_image) != 0) 
	{ 
		deallocate_fsf(&font);
		deallocate_act(&action);
		deallocate_mem(&memes);
		free_pixels(&image);
		return 1; 
	}
	
	/*goes through each text id and tries to overlay the text if it also exists in the meme file*/
	for(i = 0; i < action.num_ids; i++)
	{
		position_t *position;
		char *phrase;
		
		phrase = action.lines[i].value;
		position = get_position(meme.positions, meme.num_pos, action.lines[i].id);
		if(position != NULL)
		{
			size_t length;
			int phrase_width, x, y;
			character_t *character;
			
			/*align text in the center*/
			phrase_width = get_phrase_width(font.characters, font.num_characters, phrase);
			x = position->startpoint.x - (phrase_width / 2);
			y = position->startpoint.y - get_height(font.characters);
			length = strlen(phrase);
			for(j = 0; j < length; j++)
			{
				character = get_character(font.characters, font.num_characters, phrase[j]);
				if(character != NULL)
				{
					/*checks to see if x, y, height and width are in valid range*/
					if(valid_ranges(character->position[0], character->position[1], character->position[2], character->position[3], &font_image) != 0) 
					{
						fprintf(stderr, "Character is invalid: %c\n", character->ch);
						deallocate_fsf(&font);
						deallocate_act(&action);
						deallocate_mem(&memes);
						free_pixels(&image);
						return 1; 
					}
					
					crop_simp(character->position[2], character->position[3], character->position[0], character->position[1], &font_image, &crop_image);
					simp_overlay(&image, &crop_image, x, y);
					x += crop_image.width;
					free_pixels(&crop_image);
				}
				else /*character is not in font file, but does not cause program to stop, just skips character*/
				{
					fprintf(stderr, "Character not found in font file: %c\n", phrase[j]);
				}
			}
		}
		else /*position was not in meme file, but does not cause program to stop, just skips position*/
		{
			fprintf(stderr, "Action position not found in meme file: %s\n", action.lines[i].id);
		}
	}
	
	deallocate_fsf(&font);
	deallocate_mem(&memes);
	free_pixels(&font_image);
	
	write_simp_file(action.outfile, &image);
	
	deallocate_act(&action);
	free_pixels(&image);
	
	return 0;
}
