#ifndef SCREEN_H
#define SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FRAMESIZE 320*240*2

extern char framestr[];
extern char * framebuffer;
extern FILE * frame;

// initiates the frame buffer
int init_screen();

// sets the framebuffer
void set_screen();

// sets the entire frame buffer to the given colour
void set_colour(char colour[]);

// sets a given pixel at x,y tp the given colour
void draw_pixel(int x, int y, char * colour);

// returns a byte that representing rgb colour
char * rgb_to_byte(int red, int green, int blue);

// implementation of Bresenham's line drawing algorithm
void draw_line(int x0, int y0, int x1, int y1, char * colour);

// implementation of midpoint circle algorithm
void draw_circle(int x0, int y0, int radius, char * colour);

#endif