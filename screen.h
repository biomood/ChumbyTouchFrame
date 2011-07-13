#include <stdio.h>
#include <stdlib.h>

#define FRAMESIZE 320*240*2

char framestr[] = "/dev/fb0";
char * framebuffer;
FILE * frame;

// initiates the frame buffer
int init_screen();

// sets the entire frame buffer to the given colour
void set_colour(char colour[]);

// sets a given pixel at x,y tp the given colour
void draw_pixel(int x, int y, char * colour);

// returns a byte that representing rgb colour
char * rgb_to_byte(int red, int green, int blue);
