#include <stdio.h>
#include <stdlib.h>
#include "simp.h"

/**
* Program that crops an image
* Usage: infile outfile x y width height
* @author Alex Cole
*/
int main(int argc, char*argv[])
{
	simp_t image;
	simp_t cropimage;
	
	if(argc != 7)
	{
		fprintf(stderr, "Usage: ./crop infile outfile x y width height\n");
		return 1;
	}
	
	/*reads simp file info*/	
	if(read_simp_file(argv[1], &image) != 0) { return 1; }
	
	/*checks to see if x, y, height and width are in valid range*/
	if(valid_ranges(atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), &image) != 0) { return 1; }
	
	/*crop and store cropped image data*/
	crop_simp(atoi(argv[5]), atoi(argv[6]), atoi(argv[3]), atoi(argv[4]), &image, &cropimage);
	free_pixels(&image);
	
	write_simp_file(argv[2], &cropimage);
	
	free_pixels(&cropimage);
	return 0;
}
