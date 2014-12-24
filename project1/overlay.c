#include <stdio.h>
#include <stdlib.h>
#include "simp.h"

/**
* Program that overlays one image on top of another image
* Usage: ./overlay bottomimage topimage outfile x y
* @author Alex Cole
*/
int main(int argc, char*argv[])
{
	simp_t imagebottom;
	simp_t imagetop;
	
	if(argc != 6)
	{
		fprintf(stderr, "Usage: ./overlay bottomfile topfile outfile x y\n");
		return 1;
	}
	
	/*read bottom image info*/
	if(read_simp_file(argv[1], &imagebottom) != 0) return 1;
			
	/*reads top image info*/
	if(read_simp_file(argv[2], &imagetop) != 0) 
	{ 
		free_pixels(&imagebottom);
		return 1; 
	}
	
	/*overlays the top image on the bottom image*/
	simp_overlay(&imagebottom, &imagetop, atoi(argv[4]), atoi(argv[5]));
	free_pixels(&imagetop);
	
	write_simp_file(argv[3], &imagebottom);
	
	free_pixels(&imagebottom);
	return 0;
}
