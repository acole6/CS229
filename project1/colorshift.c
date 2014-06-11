#include <stdio.h>
#include <stdlib.h>
#include "simp.h"

/**
* Program that shifts the colors of an image based on given shift pattern
* Usage: ./colorshift infile outfile pattern
* @author Alex Cole
*/
int main(int argc, char*argv[])
{
	simp_t image;
	
	if(argc != 4)
	{
		fprintf(stderr, "Usage: ./colorshift infile outfile pattern\n");
		return 1;
	}
	
	/*reads simp file info and then shifts the colors with the given pattern*/
	if(read_simp_file(argv[1], &image) != 0) return 1;
	if(simp_colorshift(argv[3], &image) != 0) return 1;
	write_simp_file(argv[2], &image);
	
	free_pixels(&image);
	return 0;
}
