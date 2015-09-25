#ifndef SIMP_H
#define SIMP_H

/**
 * simp file data structures defined and function prototypes
 * associated with extracting and storing data to and from simp data structures
 * @author Alex Cole
 */

/*struct to store 32-bit pixel info. 0 - red, 1 - green, 2 - blue, 3 - alpha*/
struct pixel
{
    unsigned char color[4];
};
typedef struct pixel pixel_t;

/*struct to store simp file info*/
struct simp
{
    int width;
    int height;
    pixel_t **pixels;
};
typedef struct simp simp_t;

/**
 * @brief writes a byte array to a file
 * @param ofp file the byte array is to be written to
 * @param bytes array of bytes
 * @size size of the byte array
 */
void write_byte_array(FILE *ofp, unsigned char bytes[], int size);

/**
 * @brief sets the pixel color to the given color
 * @param color the color that is to be changed
 * @param givencolor the new color value
 */
void set_pixel_color(unsigned char *color, unsigned char *givencolor);

/**
 * @brief reads simp file and stores info into simp struct
 * @param filename name of the simp file
 * @param image where the file data is to be stored
 * @return 0 if the file was successfully read otherwise 1 if an error occurred
 */
int read_simp_file(char* filename, simp_t *image);

/**
 * @brief mallocs space for the pixels
 * @param image simp file data storage structure
 */
void allocate_pixels(simp_t *image);

/**
 * @brief fills in simp struct pixel data from the simp file
 * @param ifp simp file that has pixel data
 * @param filename name of the simp file
 * @image image simp file data storage structure
 * @return 0 if pixels successfully read and stored otherwise 1 if an error occurred
 */
int fill_pixels(FILE *ifp, char *filename, simp_t *image);

/**
 * @brief writes simp struct data to a file
 * @param filename name of the simp file to be written to
 * @param image simp file data storage structure
 */
void write_simp_file(char* filename, simp_t *image);

/**
 * @brief crops a simp image
 * @param width resulting cropped image width
 * @param height resulting cropped image height
 * @param x position to begin crop
 * @param y position to begin crop
 * @param image original simp image un-cropped
 * @param cropimage simp image data structure to store resulting cropped image
 */
void crop_simp(int width, int height, int x, int y, simp_t *image, simp_t *cropimage);

/**
 * @brief converts a simp image to black and white
 * @param image simp file data structure to be converted
 */
void simp2bw(simp_t *image);

/**
 * @brief swaps (or shifts) three char values
 * @first char value that gets stored in third
 * @second char value that gets stored in first
 * @third char value that gets stored in second
 */
void swap3(unsigned char *first, unsigned char *second, unsigned char *third);

/**
 * @brief swaps (or shifts) three color values for every pixel in simp image
 * @param image simp file data storage structure
 * @param first value to be shifted to third
 * @param second value to be shifted to first
 * @param third value to be shifted to second
 */
void swap3colors(simp_t *image, int first, int second, int third);

/**
 * @brief swaps two char values
 * @param first value to be swapped
 * @param second value to be swapped
 */
void swap(unsigned char *first, unsigned char *second);

/**
 * @brief swaps two color values for every pixel in simp image
 * @param first value to be swapped
 * @param second value to be swapped
 */
void swap2colors(simp_t *image, int first, int second);

/**
 * @brief shifts colors in a simp image with given pattern
 * @param pattern pixel color shift
 * @param image simp file data storage structure
 * @return 0 if shift is successful and 1 if the pattern given is invalid
 */
int simp_colorshift(char *pattern, simp_t *image);

/**
 * @brief overlays one simp image on top of another simp image at the given initial position
 * @param imagebottom bottom image which top image is to be overlaid onto
 * @param imagetop top image that is to be overlaid onto the bottom image
 * @param x start position for top image to be overlaid on bottom image
 * @param y start position for top image to be overlaid on bottom image
 */
void simp_overlay(simp_t *imagebottom, simp_t *imagetop, int x, int y);

/**
 * @brief combines two of the same color channels with formula ((a2/255) * c2) + ((a1 * (255 - a2)/(255^2)) * c1)
 * @param alpha1 alpha channel for pixel1
 * @param alpha2 alpha channel for pixel2
 * @param channel1 color channel for pixel1
 * @param channel2 color channel for pixel2
 * @return double value representing the new channel value
 */
double combine_color_channels(int alpha1, int alpha2, int channel1, int channel2);

/**
 * @brief combines two alpha channels with formula 255 * ((a2/255) + (a1 * (255 - a2)/(255^2)))
 * @alpha1 alpha channel for pixel1
 * @alpha2 alpha channel for pixel2
 * @returns double value representing the new alpha channel value
 */
double combine_alpha_channels(int alpha1, int alpha2);

/**
 * @brief frees the pixel data from the simp struct
 * @param image simp data storage structure to have pixels freed
 */
void free_pixels(simp_t *image);

/**
 * @brief checks to see if given value is in valid range between min (inclusive) and max (inclusive)
 * @param name the name of the value being checked
 * @param value the value to be checked
 * @param max the max value for range
 * @param the min value for range
 * @return 0 if the value is in the range otherwise 1 if not
 */
int invalid_range(char *name, int value, int max, int min);

/**
 * @brief checks to see if settings are in valid simp file ranges
 * @param x position that should be in range 0 to w-1
 * @param y position that should be in range 0 to h-1
 * @param width value that should be in range 1 to w
 * @param height value that should be in range 1 to h
 * @param image data structure storing simp info
 * @return 0 if all values are within range otherwise 1 if at least 1 value is not in range
 */
int valid_ranges(int x, int y, int width, int height, simp_t *image);

#endif
