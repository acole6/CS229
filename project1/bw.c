#include <stdio.h>
#include <stdlib.h>
#include "simp.h"

/**
 * Program that converts an image to black and white
 * Usage: ./bw infile outfile
 * @author Alex Cole
 */
int main(int argc, char*argv[])
{
    simp_t image;

    if(argc != 3)
    {
        fprintf(stderr, "Usage: ./bw infile outfile\n");
        return 1;
    }

    /*reads simp file info and then converts the image to black and white*/
    if(read_simp_file(argv[1], &image) != 0) return 1;
    simp2bw(&image);
    write_simp_file(argv[2], &image);

    free_pixels(&image);
    return 0;
}
