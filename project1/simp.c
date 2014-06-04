#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "simp.h"

/**
* Implementation of simp prototypes in simp.h
* @author Alex Cole
*/

/**
* @brief writes a byte array to a file
* @param ofp file the byte array is to be written to
* @param bytes array of bytes
* @param size size of the byte array
*/
void write_byte_array(FILE *ofp, unsigned char bytes[], int size)
{
	int i;
	for(i = 0; i < size; i++)
	{
		fputc(bytes[i], ofp);
	}
}

/**
* @brief sets the pixel color to the given color
* @param color the color that is to be changed
* @param givencolor the new color value
*/
void set_pixel_color(unsigned char *color, unsigned char *givencolor)
{
	int i;
	for(i = 0; i < 4; i++)
	{
		color[i] = givencolor[i]; 
	}
}

/**
* @brief reads simp file and stores info into simp struct
* @param filename name of the simp file
* @param image where the file data is to be stored
* @return 0 if the file was successfully read otherwise 1 if an error occurred
*/ 
int read_simp_file(char *filename, simp_t *image)
{
	unsigned char buffer[4];
	FILE *in;
	
	in = fopen(filename, "r");
	if(!in)
	{
		fprintf(stderr, "Could not open file: %s\n", filename);
		return 1;
	}
	
	/*read the width*/
	fseek(in, 0, SEEK_SET);
	if(4 != fread(buffer, 1, 4, in))
	{
		fprintf(stderr, "Error reading simp file width. Unexpected EOF for file: %s\n", filename);
		fclose(in);
		return 1;
	}
	image->width = ((int)buffer[0]) | ((int)buffer[1] << 8) | ((int)buffer[2] << 16) | ((int)buffer[3] << 24);
	
	/*read the height*/
	if(4 != fread(buffer, 1, 4, in))
	{
		fprintf(stderr, "Error reading simp file height. Unexpected EOF for file: %s\n", filename);
		fclose(in);
		return 1;
	}
	image->height = ((int)buffer[0]) | ((int)buffer[1] << 8) | ((int)buffer[2] << 16) | ((int)buffer[3] << 24);

	allocate_pixels(image);
	if(fill_pixels(in, filename, image) != 0) { return 1; }

	fclose(in);
	return 0;
}

/**
* @brief mallocs space for the pixels
* @param image simp file data storage structure
*/
void allocate_pixels(simp_t *image)
{
	int i;
	image->pixels = (pixel_t**) malloc(image->height * sizeof(pixel_t*));
	for(i = 0; i < image->height; i++)
	{
		image->pixels[i] = (pixel_t*) malloc(image->width * sizeof(pixel_t));
	}
}

/**
* @brief fills in simp struct pixel data from the simp file
* @param ifp simp file that has pixel data
* @param filename name of the simp file
* @image image simp file data storage structure
* @return 0 if pixels successfully read and stored otherwise 1 if an error occurred
*/
int fill_pixels(FILE *ifp, char *filename, simp_t *image)
{
	int i, j;
	unsigned char buffer[4];
	
	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			if(4 != fread(buffer, 1, 4, ifp))
			{
				fprintf(stderr, "Error reading simp file pixels. Unexpected EOF for file: %s\n", filename);
				fclose(ifp);
				free_pixels(image);
				return 1;
			}
			set_pixel_color(image->pixels[i][j].color, buffer);
		}
	}
	return 0;
}

/**
* @brief writes simp struct data to a file
* @param filename name of the simp file to be written to
* @param image simp file data storage structure
*/
void write_simp_file(char *filename, simp_t *image)
{
	int i, j;
	unsigned char buffer[4];
	FILE *out;
	
	/*write width to file*/
	out = fopen(filename, "w");
	buffer[0] = image->width;
	buffer[1] = image->width >> 8;
	buffer[2] = image->width >> 16;
	buffer[3] = image->width >> 24;
	write_byte_array(out, buffer, 4);
	
	/*write height to file*/
	buffer[0] = image->height;
	buffer[1] = image->height >> 8;
	buffer[2] = image->height >> 16;
	buffer[3] = image->height >> 24;
	write_byte_array(out, buffer, 4);
	
	/*write pixels to file*/
	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			set_pixel_color(buffer, image->pixels[i][j].color);
			write_byte_array(out, buffer, 4);
		}
	}
	fclose(out);
}

/**
* @brief crops a simp image
* @param width resulting cropped image width
* @param height resulting cropped image height
* @param x position to begin crop
* @param y position to begin crop
* @param image original simp image un-cropped
* @param cropimage simp image data structure to store resulting cropped image
*/
void crop_simp(int width, int height, int x, int y, simp_t *image, simp_t *cropimage)
{
	int i, j;

	cropimage->width = width;
	cropimage->height = height;
	
	allocate_pixels(cropimage);
	for(i = 0; i < cropimage->height; i++)
	{
		for(j = 0; j < cropimage->width; j++)
		{
			int ypos, xpos;
			/*ypos and xpos represent the original image's (x, y) position relative to the cropped image*/
			ypos = i + y;
			xpos = j + x;
			set_pixel_color(cropimage->pixels[i][j].color, image->pixels[ypos][xpos].color);
		}
	}
}

/**
* @brief converts a simp image to black and white
* @param image simp file data structure to be converted
*/
void simp2bw(simp_t *image)
{
	int i, j;
	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			int average;
			average = (image->pixels[i][j].color[0] + image->pixels[i][j].color[1] + image->pixels[i][j].color[2]) / 3;
			image->pixels[i][j].color[0] = average;
			image->pixels[i][j].color[1] = average;
			image->pixels[i][j].color[2] = average;
		}
	}
}

/**
* @brief swaps (or shifts) three char values
* @first char value that gets stored in third
* @second char value that gets stored in first
* @third char value that gets stored in second
*/
void swap3(unsigned char *first, unsigned char *second, unsigned char *third)
{
	unsigned char temp;
	temp = *first;
	*first = *second;
	*second = *third;
	*third = temp;
}

/**
* @brief swaps (or shifts) three color values for every pixel in simp image
* @param image simp file data storage structure
* @param first value to be shifted to third
* @param second value to be shifted to first
* @param third value to be shifted to second
*/
void swap3colors(simp_t *image, int first, int second, int third)
{
	int i, j;
	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			swap3(&(image->pixels[i][j].color[first]), &(image->pixels[i][j].color[second]), &(image->pixels[i][j].color[third])); 
		}
	}
}

/**
* @brief swaps two char values
* @param first value to be swapped
* @param second value to be swapped
*/
void swap(unsigned char *first, unsigned char *second)
{
	unsigned char temp; 
	temp = *first;
	*first = *second;
	*second = temp;
}

/**
* @brief swaps two color values for every pixel in simp image
* @param first value to be swapped
* @param second value to be swapped
*/
void swap2colors(simp_t *image, int first, int second)
{
	int i, j;
	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			swap(&(image->pixels[i][j].color[first]), &(image->pixels[i][j].color[second])); 
		}
	}
}

/**
* @brief shifts colors in a simp image with given pattern
* @param pattern pixel color shift
* @param image simp file data storage structure
* @return 0 if shift is successful and 1 if the pattern given is invalid
*/
int simp_colorshift(char *pattern, simp_t *image)
{
	if(strcmp(pattern, "RGB") == 0)
	{
		swap3colors(image, 1, 0, 2); /*first: green; second: red; third: blue*/
	}
	else if(strcmp(pattern, "GBR") == 0)
	{
		swap3colors(image, 2, 1, 0); /*first: blue; second: green; third: red*/
	}
	else if(strcmp(pattern, "BRG") == 0)
	{
		swap3colors(image, 0, 2, 1); /*first: red; second: blue; third: green*/
	}
	else if(strcmp(pattern, "RBG") == 0)
	{
		swap3colors(image, 2, 0, 1); /*first: blue; second: red; third: green*/
	}
	else if(strcmp(pattern, "BGR") == 0)
	{
		swap3colors(image, 1, 2, 0); /*first: green; second: blue; third: red*/
	}
	else if(strcmp(pattern, "GRB") == 0)
	{
		swap3colors(image, 0, 1, 2); /*first: red; second: green; third: blue*/
	}
	else if(strcmp(pattern, "RG") == 0 || strcmp(pattern, "GR") == 0)
	{
		swap2colors(image, 0, 1); /*first: red; second: green*/
	}
	else if(strcmp(pattern, "RB") == 0 || strcmp(pattern, "BR") == 0)
	{
		swap2colors(image, 0, 2); /*first: green; second: blue;*/
	}	
	else if(strcmp(pattern, "GB") == 0 || strcmp(pattern, "BG") == 0)
	{
		swap2colors(image, 1, 2); /*first: green; second: blue;*/
	}	
	else
	{
		fprintf(stderr, "Invalid pattern given: %s\n", pattern);
		free_pixels(image);
		return 1;
	}
	return 0;
}

/**
* @brief overlays one simp image on top of another simp image at the given initial position
* @param imagebottom bottom image which top image is to be overlaid onto
* @param imagetop top image that is to be overlaid onto the bottom image
* @param x start position for top image to be overlaid on bottom image
* @param y start position for top image to be overlaid on bottom image
*/
void simp_overlay(simp_t *imagebottom, simp_t *imagetop, int x, int y)
{
	int topheight, topwidth, i, j;
	
	topheight = imagetop->height + y;
	topwidth = imagetop->width + x;
	for(i = 0; i < imagebottom->height; i++)
	{
		for(j = 0; j < imagebottom->width; j++)
		{
			if(i >= y && j >= x && i < topheight && j < topwidth)
			{
				int topy, topx;
				/*topy and topx represent the (x, y position for the top image relative to the bottom image*/
				topy = i - y;
				topx = j - x;
				if(255 == imagetop->pixels[topy][topx].color[3]) /*if top image alpha == 255*/
				{
					set_pixel_color(imagebottom->pixels[i][j].color, imagetop->pixels[topy][topx].color);
				}
				else /*needs to calculate new pixel color if top image alpha is not 255*/
				{
					int alpha1, alpha2;
					
					alpha1 = imagebottom->pixels[i][j].color[3];
					alpha2 = imagetop->pixels[topy][topx].color[3];
					
					imagebottom->pixels[i][j].color[0] = (int) combine_color_channels(alpha1, alpha2, imagebottom->pixels[i][j].color[0], imagetop->pixels[topy][topx].color[0]); /*red*/
					imagebottom->pixels[i][j].color[1] = (int) combine_color_channels(alpha1, alpha2, imagebottom->pixels[i][j].color[1], imagetop->pixels[topy][topx].color[1]); /*green*/
					imagebottom->pixels[i][j].color[2] = (int) combine_color_channels(alpha1, alpha2, imagebottom->pixels[i][j].color[2], imagetop->pixels[topy][topx].color[2]); /*blue*/
					imagebottom->pixels[i][j].color[3] = (int) combine_alpha_channels(alpha1, alpha2);
				}
			}
		}
	}
}

/**
* @brief combines two of the same color channels with formula ((a2/255) * c2) + ((a1 * (255 - a2)/(255^2)) * c1)
* @param alpha1 alpha channel for color1
* @param alpha2 alpha channel for color2
* @param channel1 color channel for color1
* @param channel2 color channel for color2
* @return double value representing the new channel value 
*/
double combine_color_channels(int alpha1, int alpha2, int channel1, int channel2)
{
	return ((alpha2 / 255.0) * channel2) + (((alpha1 * (255.0 - alpha2))/(255.0 * 255.0)) * channel1);
}

/**
* @brief combines two alpha channels with formula 255 * ((a2/255) + (a1 * (255 - a2)/(255^2)))
* @alpha1 alpha channel for pixel1
* @alpha2 alpha channel for pixel2
* @returns double value representing the new alpha channel value
*/
double combine_alpha_channels(int alpha1, int alpha2)
{
	return 255.0 * ((alpha2 / 255.0) + ((alpha1 * (255.0 - alpha2)) / (255.0 * 255.0)));
}

/**
* @brief frees the pixel data from the simp struct
* @param image simp data storage structure to have pixels freed
*/
void free_pixels(simp_t *image)
{
	int i;
	for(i = 0; i < image->height; i++)
	{
		free(image->pixels[i]);
	}
	free(image->pixels);
}

/**
* @brief checks to see if given value is in valid range between min (inclusive) and max (inclusive)
* @param name the name of the value being checked
* @param value the value to be checked
* @param max the max value for range
* @param the min value for range
* @return 0 if the value is in the range otherwise 1 if not
*/
int invalid_range(char *name, int value, int max, int min)
{
	if(value > max || value < min) 
	{
		fprintf(stderr, "%s value is out of range. Range is %d to %d. Value given: %d\n", name, min, max, value);
		return 1;
	}
	return 0;
}

/**
* @brief checks to see if settings are in valid simp file ranges
* @param x position that should be in range 0 to w-1
* @param y position that should be in range 0 to h-1
* @param width value that should be in range 1 to w
* @param height value that should be in range 1 to h
* @param image data structure storing simp info
* @return 0 if all values are within range otherwise 1 if at least 1 value is not in range
*/
int valid_ranges(int x, int y, int width, int height, simp_t *image)
{
	if(invalid_range("x", x, (image->width - 1), 0) != 0)
	{
		free_pixels(image);
		return 1;
	}
	
	if(invalid_range("y", y, (image->height - 1), 0) != 0)
	{
		free_pixels(image);
		return 1;
	}
	
	/*-1 value for width and height means it does not need to be checked*/
	if(width != -1 && invalid_range("Width", (width + x), image->width, 1) != 0) 
	{
		free_pixels(image);
		return 1;
	}
	
	if(height != -1 && invalid_range("Height", (height + y), image->height, 1) != 0)
	{
		free_pixels(image);
		return 1;
	}
	return 0;
}
